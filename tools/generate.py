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
    """Run one back end's build.sh and collect what it produced."""
    directory = os.path.join(root, 'src', 'templates_%s' % backend)
    environment = dict(os.environ)
    if config_h:
        environment['TREXIO_CONFIG_H'] = config_h
    subprocess.run(['bash', 'build.sh'], cwd=directory, check=True,
                   env=environment)
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
