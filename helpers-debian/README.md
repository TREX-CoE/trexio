
# Debian packages from Autotools project

Following the [debian guide](https://www.debian.org/doc/manuals/debmake-doc/ch08.en.html#autotools-single).

## Requirements

- debmake
- debuild
- debhelper
- dh-autoreconf

## First release

1. Download and extract the Autotools-produced distribution tarball (e.g. `trexio-2.1.0.tar.gz`)
2. `cp trexio-2.1.0.tar.gz libtrexio_2.1.0.orig.tar.gz` --> important for step 4
3. `cd trexio-2.1.0`
4. `debmake`

This will create `debian` folder with some pre-filled templates, which have to be checked and modified
according to your project (e.g. prepend `lib` for library packages).

## Release updates

This relies on the previously created and modified templates in the `debian` directory.

1. `debuild` --> this creates the debian packages in the parent directory, i.e. one level higher than `trexio-2.1.0/` directory
2. `dpkg -f libtrexio_2.1.0-1_amd64.deb pre-depends depends recommends conflicts break`

**Note for maintainers:** to battle-test your build process, it can be a good idea to run `debuild` in a `chroot` environment
as opposed to the host. For example, `pbuilder` can be used to create an isolated `chroot`
and to build a debian package within it (see `pdebuild` wrapper command).

## Make

There used to be a `make debian_from_dist` rule for this; it no longer exists.
Build the package with `debuild` as described above, from the source
distribution extracted from a release tarball and **not** from a GitHub repo
clone, with the tarball itself present in the **parent** directory. The
specifications in the `debian/` folder are what it relies on.
