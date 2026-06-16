## Summary

- Describe the single logical change in this pull request.
- Mention any affected org-mode source files and generated-code impact.

## Validation

- [ ] I ran the local checks that mirror the relevant CI jobs for this PR, or explained any gaps below
- [ ] I ran `./autogen.sh`
- [ ] I ran `./configure --enable-silent-rules --enable-debug`
- [ ] I ran `make -j2`
- [ ] I ran `make -j2 check`
- [ ] I ran `make -j2 check` a second time
- [ ] I ran `./configure --enable-silent-rules --enable-debug --enable-sanitizer`
- [ ] I rebuilt and reran the test suite after enabling sanitizers
- [ ] I ran `cmake -S. -Bbuilddir`
- [ ] I ran `cmake --build builddir -j2`
- [ ] I ran `ctest --test-dir builddir -j2`
- [ ] I ran `pre-commit run --all-files`
- [ ] If this PR touches C or headers, I ran `.github/scripts/check-coding-conventions.sh`
- [ ] If this PR affects the Python API, I ran `make python-install` and `make python-test`
- [ ] I noted any CI-equivalent validation step that was not relevant or could not run because of a missing local dependency

## Source and documentation checks

- [ ] I edited the org-mode source instead of hand-editing generated files in `src/` or `include/`
- [ ] If I changed an org-mode source, I added or updated text in that org file to explain what the new code is doing
- [ ] If I changed org-mode tables for TREXIO data fields or error codes, I manually re-executed the relevant org blocks (for example with `C-c C-c`) so the generated exports stay in sync
- [ ] The org documentation stays in sync with the resulting code and API

## Quality checklist

- [ ] The change remains small and focused
- [ ] The modified code follows TREXIO conventions, including naming, units, and column-major array semantics where relevant
- [ ] The implementation and review meet CERT-quality expectations
