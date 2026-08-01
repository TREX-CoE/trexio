# TREXIO instructions for AI coding agents

This repository uses literate programming and has a few project rules that AI-generated pull requests must respect.

## 1. Keep pull requests easy to review

- Make one logical change per pull request.
- Keep diffs small and local; avoid unrelated refactors, formatting churn, or drive-by cleanups.
- Reuse existing names, patterns, and file organization instead of inventing new abstractions.
- When a change is generated from a template, edit the template and explain that in the PR summary.
- If you are not sure where a change belongs, stop and ask instead of guessing.

## 2. Edit the real sources, not generated files

- Do **not** hand-edit generated C sources or headers in `src/` or `include/`.
- Change the corresponding org-mode source instead:
  - `trex.org` for the data specification
  - `src/templates_front/*.org` for the front end
  - `src/templates_text/*.org` for the text backend
  - `src/templates_hdf5/*.org` for the HDF5 backend
- When you modify an org-mode source, add or update nearby prose so the org file explains what the new code is doing.
- Keep the org documentation synchronized with the generated behavior and API changes.
- Regenerate from org-mode sources with `./autogen.sh`.
- Commit only the minimal tracked source changes; do not add generated files just because they appeared locally.

## 3. Preserve TREXIO data conventions

- Use the singular form for group and attribute names.
- Store physical quantities in atomic units.
- Remember that internal array semantics are column-major / Fortran-style.
- Keep the public API naming scheme:
  - `trexio_open`
  - `trexio_read_[group]_[variable]`
  - `trexio_write_[group]_[variable]`
  - `trexio_has_[group]_[variable]`
  - `trexio_close`

## 4. Follow the C coding conventions from `src/templates_front/templator_front.org`

- Use integer types from `stdint.h`.
- Initialize pointers to `NULL`.
- When freeing memory, use `FREE(x)` so the pointer is reset to `NULL`.
- Prefer the project allocation helpers `MALLOC(T)` and `CALLOC(N, T)`.
- Use `assert.h` extensively for internal consistency checks.
- Use lower-case variable names.
- Use upper-case names for `#define` constants.
- Suffix struct tags with `_s`.
- Suffix typedef names with `_t`.
- Return `trexio_exit_code` from API functions, except for `trexio_open`.
- Aim for CERT-quality code and review changes with the same level of defensive programming and input validation.

## 5. Respect cross-language and cross-backend consistency

- A TREXIO API or schema change usually affects the front end, text backend, HDF5 backend, tests, and language bindings.
- If you add or rename data in `trex.org`, check the generated API surface and both backends.
- If you bump the project version, update all version files together:
  - `configure.ac`
  - `CMakeLists.txt`
  - `python/pytrexio/_version.py`
  - `rust/trexio/Cargo.toml`
  - `ocaml/trexio/dune-project`

## 6. Validate changes the same way maintainers do

- Preferred developer flow:
  1. `./autogen.sh`
  2. `./configure --enable-silent-rules --enable-debug`
  3. `make -j2`
  4. `make -j2 check`
  5. `make -j2 check`
- Also run `pre-commit run --all-files` for Markdown, YAML, and whitespace checks.
- If you touch C code, run `tools/check-coding-conventions.sh` as well.
- Treat failures caused by missing local tooling separately from real code failures, and report them clearly.

## 7. Reviewability checklist

Before opening a PR, verify that:

- the edited files are the correct org-mode sources;
- org-mode source updates include matching explanatory text when code changes were added there;
- the change is minimal and focused;
- CERT-quality expectations were met for the modified code paths;
- naming, units, and array-order conventions still hold;
- tests relevant to the change were run, including `make -j2 check` twice when using the Autotools flow;
- the PR description explains the intent and any generated-code impact.
