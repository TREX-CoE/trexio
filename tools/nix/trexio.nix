{ stdenv
, lib
, fetchFromGitHub
, cmake
, gfortran
, hdf5
, python3
, emacs
, swig
}:

stdenv.mkDerivation rec {
  pname = "trexio";
  version = "2.5.0";

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
    emacs
    swig
    python3
  ];

  buildInputs = [
    hdf5
  ];

  preConfigure = ''
    cd ./tools
    ./build_json.sh
    ./build_trexio.sh
    cd ..
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
