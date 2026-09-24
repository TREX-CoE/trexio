#!/usr/bin/env python3
"""Tangle the source blocks of an Org file, without Emacs.

Implements the subset of org-babel that the TREXIO templates rely on:

  * ``#+begin_src <lang> ... :tangle <file>`` blocks, written in document order,
    several blocks appending to the same file;
  * ``#+NAME:<label>`` on blocks and tables, with or without a space after the
    colon, and at any indentation;
  * noweb references, when the block carries ``:noweb yes``:
      ``<<label>>``   splices the named block's body,
      ``<<label()>>`` evaluates the named Python block and splices its value;
  * ``:var name=<table>`` on an evaluated block, binding a named Org table to a
    Python variable as a list of rows.

Everything else in the document is ignored, which is what makes this tractable:
the templates use tangling and two noweb calls, not the whole of org-babel.
"""

import argparse
import os
import re
import sys

RE_BEGIN = re.compile(r'^([ \t]*)#\+begin_src[ \t]+(\S+)[ \t]*(.*)$', re.IGNORECASE)
RE_END = re.compile(r'^[ \t]*#\+end_src[ \t]*$', re.IGNORECASE)
RE_NAME = re.compile(r'^[ \t]*#\+name:[ \t]*([^\s]+)[ \t]*$', re.IGNORECASE)
RE_TABLE_ROW = re.compile(r'^[ \t]*\|')
RE_HLINE = re.compile(r'^[ \t]*\|[-+|]*\|?[ \t]*$')
RE_NOWEB = re.compile(r'^([ \t]*)<<([A-Za-z0-9_-]+)(\(\))?>>[ \t]*$')


def parse_header_args(text):
    """Split an Org header-argument string into a dict.

    Values may contain spaces, so a key runs until the next token that starts
    with a colon: ``:tangle prefix.h :exports none`` gives two entries.
    """
    args, key, value = {}, None, []
    for token in text.split():
        if token.startswith(':'):
            if key is not None:
                args[key] = ' '.join(value)
            key, value = token[1:].lower(), []
        elif key is not None:
            value.append(token)
    if key is not None:
        args[key] = ' '.join(value)
    return args


RE_ESCAPED = re.compile(r'^([ \t]*),(\*|#\+)')


def unescape(lines):
    """Undo Org's comma escaping.

    Inside a source block, a line that would otherwise look like a headline or a
    keyword is written with a leading comma (``,*/``, ``,#+end_src``). Org strips
    that comma when tangling.
    """
    return [RE_ESCAPED.sub(r'\1\2', l) for l in lines]


TAB_WIDTH = 8


def indent_columns(line):
    """Width of a line's leading whitespace in columns, counting tabs as 8."""
    column = 0
    for char in line:
        if char == ' ':
            column += 1
        elif char == '\t':
            column += TAB_WIDTH - (column % TAB_WIDTH)
        else:
            break
    return column


def strip_columns(line, cut):
    """Remove `cut` columns of leading whitespace.

    Whitespace is consumed character by character. A tab that would take the
    count past `cut` cannot be split, so it and the rest of the line are left
    alone -- which is why a tab-indented line among space-indented ones comes
    through untouched.
    """
    column, index = 0, 0
    while index < len(line) and column < cut:
        char = line[index]
        if char == ' ':
            advance = column + 1
        elif char == '\t':
            advance = column + TAB_WIDTH - (column % TAB_WIDTH)
        else:
            break
        if advance > cut:
            break
        column, index = advance, index + 1
    return line[index:]


def remove_indentation(lines):
    """Reproduce how Org dedents a source block body.

    Established by running ``org-babel-tangle`` on test inputs: the smallest
    indentation among the non-blank lines is found in columns, that many columns
    are removed from each line, and the first line additionally loses whatever
    leading whitespace remains.

    Measuring in columns rather than characters is what makes the mixed
    indentation in trex.org come out right -- its stored blocks combine tabs and
    spaces, because Emacs re-indented them when inserting the results.
    """
    if not lines:
        return lines
    widths = [indent_columns(l) for l in lines if l.strip()]
    cut = min(widths) if widths else 0
    out = [strip_columns(l, cut) if l.strip() else l for l in lines]
    out[0] = out[0].lstrip()
    return out


def parse(path):
    """Return (blocks, tables) for one Org file."""
    with open(path, encoding='utf-8') as handle:
        return parse_text(handle.read())


def parse_text(text):
    """Return (blocks, tables) for Org markup held in a string."""
    blocks, tables = [], {}
    lines = text.split('\n')

    pending_name = None
    index = 0
    while index < len(lines):
        line = lines[index]

        match = RE_NAME.match(line)
        if match:
            pending_name = match.group(1)
            index += 1
            continue

        match = RE_BEGIN.match(line)
        if match:
            body = []
            index += 1
            while index < len(lines) and not RE_END.match(lines[index]):
                body.append(lines[index])
                index += 1
            blocks.append({
                'name': pending_name,
                'lang': match.group(2).lower(),
                'args': parse_header_args(match.group(3)),
                'body': unescape(remove_indentation(body)),
            })
            pending_name = None
            index += 1
            continue

        if RE_TABLE_ROW.match(line):
            rows, hlines = [], []
            while index < len(lines) and RE_TABLE_ROW.match(lines[index]):
                if RE_HLINE.match(lines[index]):
                    hlines.append(len(rows))
                else:
                    cells = lines[index].strip().strip('|').split('|')
                    rows.append([c.strip() for c in cells])
                index += 1
            if pending_name:
                # A header row separated by a horizontal line is not data; org
                # strips it before binding the table to a variable.
                tables[pending_name] = rows[1:] if hlines and hlines[0] == 1 else rows
            pending_name = None
            continue

        if line.strip() and not line.lstrip().startswith('#+'):
            pending_name = None
        index += 1

    return blocks, tables


def evaluate(block, tables, workdir):
    """Run a Python block with :results value semantics and return its value."""
    namespace = {}
    if 'var' in block['args']:
        for assignment in block['args']['var'].split(','):
            if '=' not in assignment:
                continue
            name, reference = assignment.split('=', 1)
            name, reference = name.strip(), reference.strip()
            if reference in tables:
                namespace[name] = tables[reference]
    source = 'def __org_block():\n'
    source += ''.join('    %s\n' % l for l in block['body'])
    source += '__org_result = __org_block()\n'
    cwd = os.getcwd()
    try:
        os.chdir(workdir)          # org evaluates with the file's directory current
        exec(compile(source, '<%s>' % (block['name'] or '?'), 'exec'), namespace)
    finally:
        os.chdir(cwd)
    result = namespace.get('__org_result')
    return '' if result is None else str(result)


def expand(body, named, tables, workdir, seen=()):
    """Expand noweb references in a block body."""
    out = []
    for line in body:
        match = RE_NOWEB.match(line)
        if not match:
            out.append(line)
            continue
        indent, label, call = match.group(1), match.group(2), match.group(3)
        if label not in named:
            continue                   # org drops a reference it cannot resolve
        if label in seen:
            raise SystemExit('org_tangle: noweb reference <<%s>> is recursive' % label)
        target = named[label]
        if call:
            text = evaluate(target, tables, workdir).split('\n')
        else:
            text = expand(target['body'], named, tables, workdir, seen + (label,))
        out.extend(indent + l if l.strip() else l for l in text)
    return out


def tangle(path, outdir):
    blocks, tables = parse(path)
    named = {b['name']: b for b in blocks if b['name']}
    workdir = os.path.dirname(os.path.abspath(path)) or '.'
    written = {}
    for block in blocks:
        target = block['args'].get('tangle')
        if not target or target in ('no', 'nil'):
            continue
        body = block['body']
        if block['args'].get('noweb') == 'yes':
            body = expand(body, named, tables, workdir)
        # org trims the blank lines around a block body before writing it, and
        # separates consecutive blocks of the same file with a single blank line.
        while body and not body[0].strip():
            body = body[1:]
        while body and not body[-1].strip():
            body = body[:-1]
        written.setdefault(target, []).extend(body + [''])
    for target, content in written.items():
        destination = os.path.join(outdir, target)
        os.makedirs(os.path.dirname(destination) or '.', exist_ok=True)
        with open(destination, 'w', encoding='utf-8') as handle:
            handle.write('\n'.join(content))
    return sorted(written)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('org_file')
    parser.add_argument('-o', '--outdir', default='.')
    options = parser.parse_args()
    for name in tangle(options.org_file, options.outdir):
        print(name)


if __name__ == '__main__':
    main()
