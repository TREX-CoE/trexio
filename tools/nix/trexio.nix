{ stdenv
, lib
, fetchFromGitHub
, cmake
, gfortran
, hdf5
, python3
, swig
}:

stdenv.mkDerivation rec {
  pname = "trexio";
  version = "2.6.1";

  src = lib.cleanSourceWith {
    src = ../../.;
    filter = path: type: ! (builtins.elem (builtins.baseNameOf path) [
      "haskell"
      "docker"
      "helpers-debian"
      "ocaml"
      "rust"
      "python"
    ] && type == "directory" );
  };

  postPatch = ''
    patchShebangs tools/*
  '';

  nativeBuildInputs = [
    cmake
    gfortran
    swig
    python3
  ];

  buildInputs = [
    hdf5
  ];

  preConfigure = ''
    python3 tools/generate.py --root .
  '';

  outputs = [ "out" "dev" ];

  doCheck = true;

  meta = with lib; {
    description = "File format and library for the storage of quantum chemical wave functions";
    homepage = "https://trex-coe.github.io/trexio/";
    downloadPage = "https://github.com/TREX-CoE/trexio";
    license = licenses.bsd3;
    maintainers = [ maintainers.sheepforce ];
  };
}
