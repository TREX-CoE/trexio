#!/usr/bin/env python3
"""Generate the TREXIO sources from the org files.

This is the single entry point both build systems call. It replaces
build_json.sh and build_trexio.sh, and needs no Emacs: the org files are read by
org_tangle.py and build_json.py.

The steps are the ones those scripts performed, in the same order:

  1. write trex.json from the tables in trex.org;
  2. tangle each templator org file into its own directory;
  3. populate the templates with generator.py, driven by trex.json;
  4. assemble the library sources with each back end's build.sh, and put the
     results where the build expects them.

Paths are taken as arguments rather than assumed from the working directory, so
that it can be run from anywhere.
"""

import argparse
import glob
import os
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_json                                       # noqa: E402
import org_tangle                                       # noqa: E402

BACKENDS = ('front', 'text', 'hdf5', 'memory')


# --- assembling the library sources -----------------------------------------
#
# What each back end's build.sh used to do with cat and shell globbing. The
# order matters and is preserved exactly; a glob expands in sorted order, as the
# shell did.

CONFIG_DEFAULTS = {
    'PACKAGE_VERSION': "'0.0.0'",
    'VERSION_MAJOR': '0',
    'VERSION_MINOR': '0',
    'VERSION_PATCH': '0',
    'GIT_HASH': "'0000'",
}


def config_values(config_h):
    """Read the version and the git hash out of the generated config.h.

    Mirrors `grep KEY config.h | cut -d " " -f 3`, including the placeholders
    the shell substituted when a value was missing, so that a build without a
    config.h still produces the same output it used to.
    """
    values = dict(CONFIG_DEFAULTS)
    if not config_h or not os.path.exists(config_h):
        return values
    with open(config_h, encoding='utf-8') as handle:
        lines = handle.read().split('\n')
    for key in CONFIG_DEFAULTS:
        for line in lines:
            if key in line:
                fields = line.split(' ')
                if len(fields) >= 3 and fields[2]:
                    values[key] = fields[2]
                break
    return values


def expand(directory, pattern):
    """Resolve one source name, which may be a glob."""
    if any(character in pattern for character in '*?['):
        matches = sorted(glob.glob(os.path.join(directory, pattern)))
        if not matches:
            raise SystemExit('generate: nothing matches %s in %s'
                             % (pattern, directory))
        return matches
    return [os.path.join(directory, pattern)]


def cat(directory, target, sources, truncate=False):
    """Append the sources to the target, or write it from scratch."""
    with open(os.path.join(directory, target), 'wb' if truncate else 'ab') as out:
        for source in sources:
            for path in expand(directory, source):
                with open(path, 'rb') as handle:
                    out.write(handle.read())


def append_lines(directory, target, lines):
    with open(os.path.join(directory, target), 'a', encoding='utf-8') as out:
        for line in lines:
            out.write(line + '\n')


def assemble_front(directory, version):
    cat(directory, 'trexio.c', ['prefix_front.c'], truncate=True)
    cat(directory, 'trexio.h', ['prefix_front.h'], truncate=True)
    append_lines(directory, 'trexio.h', [
        '',
        '#define TREXIO_PACKAGE_VERSION %s' % version['PACKAGE_VERSION'],
        '#define TREXIO_VERSION_MAJOR %s' % version['VERSION_MAJOR'],
        '#define TREXIO_VERSION_MINOR %s' % version['VERSION_MINOR'],
        '#define TREXIO_VERSION_PATCH %s' % version['VERSION_PATCH'],
        '#define TREXIO_GIT_HASH %s' % version['GIT_HASH'],
        '',
    ])
    cat(directory, 'trexio_s.h', ['prefix_s_front.h'], truncate=True)
    cat(directory, 'trexio_f.f90', ['prefix_fortran.f90'], truncate=True)
    cat(directory, 'trexio.py', ['prefix_python.py'], truncate=True)
    append_lines(directory, 'trexio_f.f90', [
        '',
        'character(len = 12) :: TREXIO_PACKAGE_VERSION = %s'
        % version['PACKAGE_VERSION'],
        'integer :: TREXIO_VERSION_MAJOR = %s' % version['VERSION_MAJOR'],
        'integer :: TREXIO_VERSION_MINOR = %s' % version['VERSION_MINOR'],
        'integer :: TREXIO_VERSION_PATCH = %s' % version['VERSION_PATCH'],
        'character(len = 64) :: TREXIO_GIT_HASH = %s' % version['GIT_HASH'],
        '',
    ])
    cat(directory, 'trexio.c', ['populated/pop_*.c'])
    cat(directory, 'trexio.h', ['populated/pop_*.h'])
    cat(directory, 'trexio.h', ['hrw_determinant_front.h'])
    cat(directory, 'trexio.c', ['*_determinant_front.c'])
    cat(directory, 'trexio_private.h', ['populated/private_pop_front.h'])
    append_lines(directory, 'trexio_private.h', ['#endif'])
    cat(directory, 'trexio_f.f90', ['populated/pop_*.f90'])
    cat(directory, 'trexio_f.f90', ['*_determinant_front_fortran.f90'])
    cat(directory, 'trexio_f.f90', ['helper_fortran.f90'])
    cat(directory, 'trexio_f.f90', ['populated/pop_*.fh_90'])
    cat(directory, 'trexio.py', ['basic_python.py'])
    cat(directory, 'trexio.py', ['populated/pop_*.py'])
    cat(directory, 'trexio.py', ['*_determinant_front.py'])
    cat(directory, 'trexio_s.h', ['suffix_s_front.h'])
    cat(directory, 'trexio.h', ['suffix_front.h'])
    cat(directory, 'trexio_f.f90', ['suffix_fortran.f90'])


def assemble_hdf5(directory):
    cat(directory, 'trexio_hdf5.c', ['prefix_hdf5.c'], truncate=True)
    cat(directory, 'trexio_hdf5.h', ['prefix_hdf5.h'], truncate=True)
    cat(directory, 'trexio_hdf5.c', ['populated/pop_def_hdf5.c'])
    cat(directory, 'trexio_hdf5.h', ['populated/pop_struct_hdf5.h'])
    cat(directory, 'trexio_hdf5.c', ['populated/pop_basic_hdf5.c'])
    cat(directory, 'trexio_hdf5.c', ['populated/pop_has_*.c'])
    cat(directory, 'trexio_hdf5.c', ['populated/pop_read_*.c'])
    cat(directory, 'trexio_hdf5.c', ['populated/pop_write_*.c'])
    cat(directory, 'trexio_hdf5.c', ['populated/pop_delete_group_hdf5.c'])
    cat(directory, 'trexio_hdf5.h', ['populated/pop_hrw_*.h'])
    cat(directory, 'trexio_hdf5.h', ['populated/pop_delete_group_hdf5.h'])
    cat(directory, 'trexio_hdf5.h', ['hrw_determinant_hdf5.h'])
    cat(directory, 'trexio_hdf5.c', ['*_determinant_hdf5.c'])
    cat(directory, 'trexio_hdf5.c', ['helpers_hdf5.c'])
    cat(directory, 'trexio_hdf5.c', ['suffix_hdf5.c'])
    cat(directory, 'trexio_hdf5.h', ['suffix_hdf5.h'])


def assemble_flat(directory, backend):
    """The text and memory back ends, whose recipes differ only in the name."""
    source = 'trexio_%s.c' % backend
    header = 'trexio_%s.h' % backend
    cat(directory, source, ['prefix_%s.c' % backend], truncate=True)
    cat(directory, header, ['prefix_%s.h' % backend], truncate=True)
    cat(directory, source, ['basic_%s.c' % backend])
    cat(directory, source, ['populated/pop_basic_%s_group.c' % backend])
    cat(directory, header, ['populated/pop_struct_%s_group_dset.h' % backend])
    cat(directory, header, ['populated/pop_struct_%s_group.h' % backend])
    cat(directory, header, ['basic_%s.h' % backend])
    cat(directory, header, ['hrw_determinant_%s.h' % backend])
    cat(directory, source, ['*_determinant_%s.c' % backend])
    cat(directory, source, ['populated/pop_has_group_%s.c' % backend])
    cat(directory, header, ['populated/pop_hrw_group_%s.h' % backend])
    for kind in ('free', 'read', 'flush', 'delete'):
        cat(directory, source, ['populated/pop_%s_group_%s.c' % (kind, backend)])
    for kind in ('free', 'read', 'flush', 'delete'):
        cat(directory, header, ['populated/pop_%s_group_%s.h' % (kind, backend)])
    # The order is not the same for every action: `has` takes attr_num before
    # attr_str, while `read` and `write` take them the other way round. It looks
    # accidental, but it decides the order of the generated functions, so it is
    # kept exactly as build.sh had it.
    has_shapes = ('dset_data', 'dset_str', 'dset_sparse', 'attr_num',
                  'attr_str', 'buffered')
    rw_shapes = ('dset_data', 'dset_str', 'dset_sparse', 'attr_str',
                 'attr_num', 'buffered')
    for action, shapes in (('has', has_shapes), ('read', rw_shapes),
                           ('write', rw_shapes)):
        for shape in shapes:
            cat(directory, source,
                ['populated/pop_%s_%s_%s.c' % (action, shape, backend)])
    for shape in has_shapes:
        cat(directory, header,
            ['populated/pop_hrw_%s_%s.h' % (shape, backend)])
    cat(directory, header, ['suffix_%s.h' % backend])


def log(message):
    print('generate: %s' % message, flush=True)


def clean_templates(directory):
    """Remove the files a previous run tangled and populated."""
    for pattern in ('*.c', '*.h', '*.f90'):
        for path in glob.glob(os.path.join(directory, pattern)):
            os.remove(path)
    populated = os.path.join(directory, 'populated')
    os.makedirs(populated, exist_ok=True)
    for path in glob.glob(os.path.join(populated, '*')):
        os.remove(path)


def run_generator(root):
    """Populate the templates with generator.py.

    The generator resolves trex.json relative to the parent of its own
    directory, so it is copied into src/ and run there, exactly as
    build_trexio.sh did. Teaching it to take a path would be a better fix and is
    left for later.
    """
    src = os.path.join(root, 'src')
    tools = os.path.join(root, 'tools')
    copied = []
    for name in ('generator.py', 'generator_tools.py'):
        destination = os.path.join(src, name)
        shutil.copy(os.path.join(tools, name), destination)
        copied.append(destination)
    try:
        subprocess.run([sys.executable, 'generator.py'], cwd=src, check=True)
    finally:
        for path in copied:
            os.remove(path)
        shutil.rmtree(os.path.join(src, '__pycache__'), ignore_errors=True)


def assemble(root, backend, config_h):
    """Put one back end's sources together and collect the result."""
    directory = os.path.join(root, 'src', 'templates_%s' % backend)
    if backend == 'front':
        assemble_front(directory, config_values(config_h))
    elif backend == 'hdf5':
        assemble_hdf5(directory)
    else:
        assemble_flat(directory, backend)
    for path in sorted(glob.glob(os.path.join(directory, 'trexio*'))):
        shutil.copy(path, os.path.join(root, 'src'))


def generate(root, config_h):
    root = os.path.abspath(root)

    log('writing trex.json from trex.org')
    build_json.build(os.path.join(root, 'trex.org'),
                     os.path.join(root, 'trex.json'))

    for backend in BACKENDS:
        directory = os.path.join(root, 'src', 'templates_%s' % backend)
        log('tangling templator_%s.org' % backend)
        clean_templates(directory)
        org_tangle.tangle(os.path.join(directory,
                                       'templator_%s.org' % backend), directory)

    log('populating the templates')
    run_generator(root)

    for backend in BACKENDS:
        log('assembling the %s back end' % backend)
        assemble(root, backend, config_h)
        if backend == 'front':
            # The public header and the Fortran module belong in include/.
            for name in ('trexio.h', 'trexio_f.f90'):
                shutil.move(os.path.join(root, 'src', name),
                            os.path.join(root, 'include', name))

    log('done')


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', default=os.path.dirname(here),
                        help='top of the source tree (default: the parent of tools/)')
    parser.add_argument('--config-h', default=None,
                        help='path to the generated config.h, for the version and git hash')
    options = parser.parse_args()
    generate(options.root, options.config_h)


if __name__ == '__main__':
    main()
