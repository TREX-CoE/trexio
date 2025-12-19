# TREXIO Copilot Instructions

## Project Overview

TREXIO is an open-source file format and library for storing and manipulating data from quantum chemistry calculations. It provides reliable and efficient storage and exchange of wave function parameters and matrix elements.

### Key Technologies
- **Core Library**: C (C99 standard)
- **Language Interfaces**: Fortran, Python, OCaml, Rust
- **Backends**: Text-based and HDF5 binary
- **Build Systems**: Autotools (primary) and CMake

## Development Approach

### Literate Programming
TREXIO uses **literate programming** with Emacs org-mode files:
- Source code is auto-generated from `.org` files in `src/templates_*` directories
- The main data specification is in `trex.org`
- **Never directly edit generated source files** - always modify the corresponding `.org` files
- Generation requires: Emacs (>= 26.0), Python3 (>= 3.8)
- The `src/` directory is initially empty in a fresh clone

### Code Generation Workflow
1. Edit `.org` files to make changes
2. Run `./autogen.sh` to generate source code from org-mode files
3. Configure and build as normal

## Building and Testing

### From Source (Developers)
```bash
./autogen.sh          # Generate source from .org files
./configure           # Or use CMake
make -j 4
make -j $(nproc) check
```

### From Release Tarball (Users)
```bash
./configure
make -j 4
make -j $(nproc) check
sudo make install
```

### CMake Alternative
```bash
cmake -S. -Bbuild
cd build
make -j 4
ctest -j $(nproc)
```

### Testing
- C tests are in `tests/` directory
- Python tests: `make python-test` (requires pytest)
- Tests are backend-specific (HDF5 vs. text)

## Coding Standards

### C Code
- **Standard**: C99 compliant
- **Style**: Follow [SEI CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard)
- **Checking**: Use `cppcheck` for compliance verification
- All data stored in **atomic units**
- Arrays are in **column-major order** (Fortran-style) in memory

### Naming Conventions
API functions follow this pattern:
- `trexio_open`
- `trexio_write_[group]_[variable]`
- `trexio_read_[group]_[variable]`
- `trexio_has_[group]_[variable]`
- `trexio_close`

Groups and variables are defined in `trex.org` (singular form always used).

### Version Management
Version numbers must be synchronized across multiple files:
- `configure.ac` - Autotools version (line with `AC_INIT`)
- `CMakeLists.txt` - CMake version
- `python/pytrexio/_version.py` - Python version
- `rust/trexio/Cargo.toml` - Rust version
- `ocaml/trexio/dune-project` - OCaml version

**Always update all version files together** when bumping version.

## Project Structure

```
trexio/
├── src/                    # Generated C source (from .org files)
│   ├── templates_front/    # Front-end API templates (org-mode)
│   ├── templates_hdf5/     # HDF5 backend templates (org-mode)
│   └── templates_text/     # Text backend templates (org-mode)
├── include/                # Header files
├── tests/                  # C test suite
├── python/                 # Python bindings (SWIG-based)
├── rust/                   # Rust bindings
├── ocaml/                  # OCaml bindings
├── docs/                   # Documentation (org-mode files)
├── trex.org               # Main data structure specification
└── .devel                 # Marker for developer mode
```

## HDF5 Integration

- HDF5 support is **optional but recommended**
- Configure without HDF5: `./configure --without-hdf5` or `cmake -DENABLE_HDF5=OFF`
- Link against **serial (non-MPI) HDF5** for simplicity
- **Library Detection**: If HDF5 detection fails during configuration:
  - The linker needs `$LIBRARY_PATH` (for finding libraries during linking)
  - This is different from `$LD_LIBRARY_PATH` (for finding libraries at runtime)
  - Workaround: `export LIBRARY_PATH=$LD_LIBRARY_PATH` before running `./configure`
  - Better solution: Contact system administrators to set both variables in HDF5 module

## Python API

- Built with SWIG (>= 4.0)
- Install: `make python-install`
- Test: `make python-test`
- Use virtual environments for development
- Package available on PyPI as `trexio`

## Language-Specific Notes

### Fortran
- Module file: `trexio_f.f90` (in `include/`)
- Do **not** include `trexio.h` in Fortran code
- Only the library and module file are needed

### Python
- Uses SWIG for bindings
- NumPy arrays are row-major by default (opposite of internal storage)

### Rust
- Available on Crates.io
- Source in `rust/trexio/`

### OCaml
- Available in OPAM
- Source in `ocaml/trexio/`

## Pre-commit Hooks

The project uses pre-commit hooks:
- Trailing whitespace removal
- End-of-file fixer
- YAML validation
- Large file checks

## Important Constraints

1. **Maintainer Mode**: Automatically enabled when `.devel` file exists
2. **Atomic Units**: All physical quantities stored in atomic units
3. **Singular Naming**: Always use singular form for groups/attributes
4. **Column-Major**: Internal arrays are column-major (Fortran convention)
5. **3-Clause BSD License**: Library is permissively licensed

## When Making Changes

- For API changes: Modify `trex.org` and regenerate
- For templates: Edit `.org` files in `src/templates_*/`
- For tests: Follow existing patterns in `tests/`
- Always run `make check` or `ctest` before committing
- Verify version consistency across all version files
- Consider both HDF5 and text backend implications
