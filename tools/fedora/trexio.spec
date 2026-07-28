%global soversion 2

# Open MPI is unavailable on i686 in Fedora 40 and later.
%if 0%{?fedora} >= 40
%ifarch %{ix86}
%bcond openmpi 0
%else
%bcond openmpi 1
%endif
%else
%bcond openmpi 1
%endif

Name:           trexio
Version:        0.0.0
Release:        %autorelease
Summary:        TREX I/O library

License:        BSD-3-Clause
URL:            https://github.com/TREX-CoE/trexio
Source0:        https://github.com/TREX-CoE/trexio/releases/download/v%{version}/%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  emacs
BuildRequires:  gcc
BuildRequires:  gcc-gfortran
BuildRequires:  hdf5-devel

%global _description %{expand:
TREXIO is an open-source file format and library for storing and exchanging
wave-function parameters and matrix elements produced by quantum chemistry
calculations. It provides a C library with text and HDF5 back ends, together
with interfaces for several programming languages.}

%description
%{_description}

This package contains the serial build linked against the serial HDF5 library.

%package common
Summary:        Common development headers for %{name}
BuildArch:      noarch

%description common
This package contains the architecture- and MPI-independent C and Fortran
interface sources for developing applications that use TREXIO.

%package devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}
Requires:       %{name}-common = %{version}-%{release}

%description devel
This package contains the serial development library, pkg-config metadata, and
CMake package files for developing applications that use TREXIO.

%global mpi_list mpich

%package mpich
Summary:        TREXIO linked against the MPICH HDF5 stack
BuildRequires:  hdf5-mpich-devel
BuildRequires:  mpich-devel
Requires:       mpich%{?_isa}

%description mpich
%{_description}

This package contains TREXIO linked against the parallel HDF5 build for MPICH.

%package mpich-devel
Summary:        Development files for %{name}-mpich
Requires:       %{name}-common = %{version}-%{release}
Requires:       %{name}-mpich%{?_isa} = %{version}-%{release}

%description mpich-devel
This package contains the development library, pkg-config metadata, and CMake
package files for developing applications against the MPICH TREXIO build.

%if %{with openmpi}
%global mpi_list %{mpi_list} openmpi

%package openmpi
Summary:        TREXIO linked against the Open MPI HDF5 stack
BuildRequires:  hdf5-openmpi-devel
BuildRequires:  openmpi-devel
Requires:       openmpi%{?_isa}

%description openmpi
%{_description}

This package contains TREXIO linked against the parallel HDF5 build for Open MPI.

%package openmpi-devel
Summary:        Development files for %{name}-openmpi
Requires:       %{name}-common = %{version}-%{release}
Requires:       %{name}-openmpi%{?_isa} = %{version}-%{release}

%description openmpi-devel
This package contains the development library, pkg-config metadata, and CMake
package files for developing applications against the Open MPI TREXIO build.
%endif

%prep
%autosetup -p1

# Keep one independent CMake cache for each HDF5/MPI stack.
%global _vpath_builddir %{_vendor}-%{_target_os}-build-${mpi:-serial}

%conf
# Serial HDF5 build.
%cmake \
    -DBUILD_TESTING:BOOL=ON \
    -DTREXIO_FORTRAN:BOOL=ON \
    -DTREXIO_USE_HDF5:BOOL=ON \
    -DHDF5_NO_FIND_PACKAGE_CONFIG_FILE:BOOL=ON \
    -DHDF5_PREFER_PARALLEL:BOOL=OFF

# Parallel-HDF5 builds. TREXIO enables its MPI link branch automatically when
# FindHDF5 reports HDF5_IS_PARALLEL=TRUE; there is no separate TREXIO MPI option.
for mpi in %{mpi_list}; do
    module load mpi/$mpi-%{_arch}
    %cmake \
        -DBUILD_TESTING:BOOL=ON \
        -DTREXIO_FORTRAN:BOOL=ON \
        -DTREXIO_USE_HDF5:BOOL=ON \
        -DCMAKE_C_COMPILER:FILEPATH=${MPI_BIN}/mpicc \
        -DCMAKE_Fortran_COMPILER:FILEPATH=${MPI_BIN}/mpifort \
        -DCMAKE_INSTALL_PREFIX:PATH=${MPI_HOME} \
        -DCMAKE_INSTALL_LIBDIR:PATH=${MPI_LIB} \
        -DCMAKE_INSTALL_INCLUDEDIR:PATH=%{_includedir} \
        -DHDF5_NO_FIND_PACKAGE_CONFIG_FILE:BOOL=ON \
        -DHDF5_PREFER_PARALLEL:BOOL=ON \
        -DHDF5_C_COMPILER_EXECUTABLE:FILEPATH=${MPI_BIN}/h5pcc
    # Fail early if FindHDF5 silently selected the serial HDF5 installation.
    grep -q '^set(TREXIO_HDF5_IS_PARALLEL ON)$' \
        %{_vpath_builddir}/src/trexio-config.cmake
    module purge
done

%build
%cmake_build
for mpi in %{mpi_list}; do
    module load mpi/$mpi-%{_arch}
    %cmake_build
    module purge
done

%install
%cmake_install
for mpi in %{mpi_list}; do
    module load mpi/$mpi-%{_arch}
    %cmake_install
    module purge
done

%check
%ctest --output-on-failure
for mpi in %{mpi_list}; do
    module load mpi/$mpi-%{_arch}
    %ctest --output-on-failure
    module purge
done

%files
%license COPYING
%{_libdir}/libtrexio.so.%{soversion}{,.*}

%files common
%{_includedir}/trexio.h
%{_includedir}/trexio_f.f90

%files devel
%{_libdir}/libtrexio.so
%{_libdir}/pkgconfig/trexio.pc
%{_libdir}/cmake/trexio/

%files mpich
%license COPYING
%{_libdir}/mpich/lib/libtrexio.so.%{soversion}{,.*}

%files mpich-devel
%{_libdir}/mpich/lib/libtrexio.so
%{_libdir}/mpich/lib/pkgconfig/trexio.pc
%{_libdir}/mpich/lib/cmake/trexio/

%if %{with openmpi}
%files openmpi
%license COPYING
%{_libdir}/openmpi/lib/libtrexio.so.%{soversion}{,.*}

%files openmpi-devel
%{_libdir}/openmpi/lib/libtrexio.so
%{_libdir}/openmpi/lib/pkgconfig/trexio.pc
%{_libdir}/openmpi/lib/cmake/trexio/
%endif

%changelog
%autochangelog
