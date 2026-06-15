# TREXIO Copilot instructions

Start with `/home/runner/work/trexio/trexio/TREX-CoE/trexio/AGENTS.md`. The rules below are the short Copilot-specific version.

## Change the right files

- TREXIO source code is generated from org-mode files.
- Do **not** edit generated files in `src/` or `include/`.
- Make changes in:
  - `trex.org`
  - `src/templates_front/*.org`
  - `src/templates_text/*.org`
  - `src/templates_hdf5/*.org`
- Regenerate with `./autogen.sh` when needed.

## Keep AI PRs reviewable

- Make one logical change at a time.
- Avoid unrelated refactors, mass renames, or formatting-only rewrites.
- Match existing naming, control flow, and file layout.
- Ask for clarification instead of guessing when the target file or convention is unclear.

## Respect TREXIO conventions

- Use singular names for groups and attributes.
- Keep physical quantities in atomic units.
- Remember that internal arrays follow column-major / Fortran order.
- Use the standard API naming pattern `trexio_[read|write|has]_[group]_[variable]`.

## Respect C coding conventions

The authoritative source is `src/templates_front/templator_front.org`.

- Use `stdint.h` integer types.
- Initialize pointers to `NULL`.
- Use `FREE(x)` instead of bare `free(x)`.
- Prefer `MALLOC(T)` and `CALLOC(N, T)`.
- Use lower-case variable names.
- Use upper-case `#define` names.
- Suffix struct tags with `_s`.
- Suffix typedefs with `_t`.
- Return `trexio_exit_code` from API functions except `trexio_open`.
- Use `assert` for internal consistency checks.

## Check repository-wide impact

- API or schema changes usually affect both backends, tests, and bindings.
- Version bumps must update:
  - `configure.ac`
  - `CMakeLists.txt`
  - `python/pytrexio/_version.py`
  - `rust/trexio/Cargo.toml`
  - `ocaml/trexio/dune-project`

## Validate before submitting

- Run `./autogen.sh`
- Run `./configure --enable-silent-rules`
- Run `make -j2`
- Run `make -j2 check`
- Run `pre-commit run --all-files`

If a validation command fails because of a missing local dependency, say so explicitly in the PR summary.
