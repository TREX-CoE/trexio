#!/usr/bin/env python3
"""Generate trex.json from the tables in trex.org, without Emacs.

trex.org is the data specification: the groups are Org tables, and a Python
block named ``json`` turns one table into a fragment of trex.json. A series of
``#+CALL: json(data=nucleus, title="nucleus")`` lines invokes it once per group,
each call emitting an Org source block that is tangled into trex.json.

This reproduces that in Python. The conversion itself is not reimplemented: the
``json`` block in trex.org is executed as it stands, so the org file remains the
only place the format is defined.
"""

import argparse
import contextlib
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import org_tangle                                      # noqa: E402

RE_CALL = re.compile(r'^[ \t]*#\+call:[ \t]*([A-Za-z0-9_-]+)\((.*)\)[ \t]*$',
                     re.IGNORECASE)


def split_arguments(text):
    """Split a call's argument list on top-level commas."""
    parts, depth, current = [], 0, []
    for char in text:
        if char in '([':
            depth += 1
        elif char in ')]':
            depth -= 1
        if char == ',' and depth == 0:
            parts.append(''.join(current))
            current = []
        else:
            current.append(char)
    if current:
        parts.append(''.join(current))
    return [p.strip() for p in parts if p.strip()]


def resolve(value, tables):
    """Turn one argument's text into a Python value.

    A quoted string is a string, a number is an integer, and a bare word names
    an Org table, which is passed as a list of rows -- the same binding Org
    performs for a `:var` header argument.
    """
    if (value.startswith('"') and value.endswith('"')) or \
       (value.startswith("'") and value.endswith("'")):
        return value[1:-1]
    if re.fullmatch(r'-?\d+', value):
        return int(value)
    if value == '[]':
        return []
    if value in tables:
        return tables[value]
    return value


def bindings(block, call_arguments, tables):
    """Build the namespace for one call, defaults from the block's :var first."""
    namespace = {}
    for assignment in split_arguments(block['args'].get('var', '')
                                      .replace(' ', ',')):
        if '=' in assignment:
            name, value = assignment.split('=', 1)
            namespace[name.strip()] = resolve(value.strip(), tables)
    for assignment in call_arguments:
        if '=' in assignment:
            name, value = assignment.split('=', 1)
            namespace[name.strip()] = resolve(value.strip(), tables)
    return namespace


def run(block, namespace, workdir):
    """Execute a block and return what it printed.

    The json block reports through print, which is `:results output` in Org
    terms: the body runs at top level and its standard output is the result,
    rather than being wrapped in a function whose return value is taken.
    """
    buffer = io.StringIO()
    cwd = os.getcwd()
    try:
        os.chdir(workdir)
        with contextlib.redirect_stdout(buffer):
            exec(compile('\n'.join(block['body']), '<json>', 'exec'), namespace)
    finally:
        os.chdir(cwd)
    return buffer.getvalue()


RE_DRAWER = re.compile(r'^[ \t]*:results:[ \t]*$', re.IGNORECASE)
RE_DRAWER_END = re.compile(r'^[ \t]*:end:[ \t]*$', re.IGNORECASE)
RE_SRC_JSON = re.compile(r'^[ \t]*#\+begin_src[ \t]+json\b', re.IGNORECASE)
RE_SRC_END = re.compile(r'^[ \t]*#\+end_src[ \t]*$', re.IGNORECASE)


def build(org_path, out_path, target='trex.json'):
    """Rebuild trex.json from the tables, in document order.

    Blocks that were written by hand are taken as they stand; the results stored
    under a `#+CALL:` are ignored and the call is executed again instead, so the
    output follows the tables rather than whatever was last saved in the file.
    """
    with open(org_path, encoding='utf-8') as handle:
        text = handle.read()
    blocks, tables = org_tangle.parse_text(text)
    named = {b['name']: b for b in blocks if b['name']}
    workdir = os.path.dirname(os.path.abspath(org_path)) or '.'

    lines = text.split('\n')
    emitted, index, calls = [], 0, 0
    while index < len(lines):
        line = lines[index]

        match = RE_CALL.match(line)
        if match:
            name, arguments = match.group(1), match.group(2)
            if name not in named:
                raise SystemExit('build_json: no block named %s' % name)
            namespace = bindings(named[name], split_arguments(arguments), tables)
            emitted.append(run(named[name], namespace, workdir))
            calls += 1
            index += 1
            continue

        if RE_DRAWER.match(line):
            # A results drawer holds what a previous call left behind. Skip it:
            # the call above has just been run again. Note that a bare
            # `#+RESULTS:` without a drawer is not a skip marker, which is why
            # this keys on the drawer rather than on the results keyword.
            index += 1
            while index < len(lines) and not RE_DRAWER_END.match(lines[index]):
                index += 1
            index += 1
            continue

        if RE_SRC_JSON.match(line):       # a hand-written fragment, kept as is
            block = [line]
            index += 1
            while index < len(lines) and not RE_SRC_END.match(lines[index]):
                block.append(lines[index])
                index += 1
            block.append('#+end_src')
            emitted.append('\n'.join(block))
            index += 1
            continue

        index += 1

    tangled, _ = org_tangle.parse_text('\n'.join(emitted))
    content = []
    for block in tangled:
        if block['args'].get('tangle') != target:
            continue
        body = block['body']
        while body and not body[0].strip():
            body = body[1:]
        while body and not body[-1].strip():
            body = body[:-1]
        content.extend(body + [''])
    with open(out_path, 'w', encoding='utf-8') as handle:
        handle.write('\n'.join(content))
    return calls


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('org_file', nargs='?', default='trex.org')
    parser.add_argument('-o', '--output', default='trex.json')
    parser.add_argument('--target', default='trex.json',
                        help="the :tangle target to collect (default trex.json)")
    options = parser.parse_args()
    calls = build(options.org_file, options.output, options.target)
    print('%s: %d groups' % (options.output, calls))


if __name__ == '__main__':
    main()
