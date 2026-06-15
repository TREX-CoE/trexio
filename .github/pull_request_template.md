## Summary

- Describe the single logical change in this pull request.
- Mention any affected org-mode source files and generated-code impact.

## Validation

- [ ] I ran `./autogen.sh`
- [ ] I ran `./configure --enable-silent-rules --enable-debug`
- [ ] I ran `make -j2`
- [ ] I ran `make -j2 check`
- [ ] I ran `make -j2 check` a second time
- [ ] I ran `pre-commit run --all-files`
- [ ] I noted any validation step that could not run because of a missing local dependency

## Source and documentation checks

- [ ] I edited the org-mode source instead of hand-editing generated files in `src/` or `include/`
- [ ] If I changed an org-mode source, I added or updated text in that org file to explain what the new code is doing
- [ ] The org documentation stays in sync with the resulting code and API

## Quality checklist

- [ ] The change remains small and focused
- [ ] The modified code follows TREXIO conventions, including naming, units, and column-major array semantics where relevant
- [ ] The implementation and review meet CERT-quality expectations
