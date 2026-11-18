# Bundled yyjson

[yyjson](https://github.com/ibireme/yyjson) is the JSON parser and writer used
by the TREXIO JSON back end. It is bundled here so that the back end can be
built without any external dependency: yyjson is two files and needs no
configuration of its own.

The bundled copy is only a fallback. Both build systems look for an installed
yyjson first and use it when one is found, so a distribution package builds
against the system library and is not affected by what is in this directory.

## Provenance

| | |
|---|---|
| version | 0.13.0 |
| source  | https://github.com/ibireme/yyjson/tree/0.13.0 |
| license | MIT, see `LICENSE` |

```
d2d58ef0a3b2267862dc363832c4f3185fd375aea933d5d3419d1a940d6ece2e  yyjson.c
ef803cda5c06b8962face6dfa39c3284b3bcf3e73f4d7317664690cc779679ca  yyjson.h
45e384d3d52c73cba3a64d6e6c25d47cd738cd8a55c30629e3201046eda62947  LICENSE
```

## Updating

The files are taken verbatim from the release tag and are not patched, so an
update is a download:

```sh
V=0.13.0
for f in src/yyjson.c src/yyjson.h LICENSE ; do
    curl -sSfL -o "external/yyjson/$(basename $f)" \
        "https://raw.githubusercontent.com/ibireme/yyjson/$V/$f"
done
sha256sum external/yyjson/yyjson.c external/yyjson/yyjson.h external/yyjson/LICENSE
```

Record the new version and checksums above. The back end uses only documented
API, so an update should need no changes to `src/templates_json`.
