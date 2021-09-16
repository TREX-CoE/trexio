# ===========================================================================
#   Script from the hdf5-manylinux repo: 
#     https://github.com/h5py/hdf5-manylinux/blob/master/install_libaec.sh
# ===========================================================================


# libaec implements szip compression, so the optional szip filter can be built
# in HDF5.
set -euo pipefail

pushd /tmp

aec_version="1.0.4"

echo "Downloading libaec"
# The URL includes a hash, so it needs to change if the version does
curl -fsSLO https://gitlab.dkrz.de/k202009/libaec/uploads/ea0b7d197a950b0c110da8dfdecbb71f/libaec-${aec_version}.tar.gz
tar zxf libaec-$aec_version.tar.gz

echo "Building & installing libaec"
pushd libaec-$aec_version
./configure
make
make install

# Clean up the files from the build
popd
rm -r libaec-$aec_version libaec-$aec_version.tar.gz
