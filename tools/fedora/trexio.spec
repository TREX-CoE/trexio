%global soversion 2

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

%description
TREXIO is an open-source file format and library for storing and exchanging
wave-function parameters and matrix elements produced by quantum chemistry
calculations. It provides a C library with text and HDF5 back ends, together
with interfaces for several programming languages.

%package devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description devel
This package contains development files for TREXIO.

%prep
%autosetup -p1

%conf
%cmake \
    -DBUILD_TESTING:BOOL=ON \
    -DTREXIO_FORTRAN:BOOL=ON \
    -DTREXIO_USE_HDF5:BOOL=ON

%build
%cmake_build

%install
%cmake_install

%check
%ctest --output-on-failure

%files
%license COPYING
%{_libdir}/libtrexio.so.%{soversion}{,.*}

%files devel
%{_includedir}/trexio.h
%{_includedir}/trexio_f.f90
%{_libdir}/libtrexio.so
%{_libdir}/pkgconfig/trexio.pc
%{_libdir}/cmake/trexio/

%changelog
%autochangelog
