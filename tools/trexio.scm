(define-module (gnu packages trexio)
  #:use-module (guix packages)
  #:use-module (gnu packages pkg-config)
  #:use-module (gnu packages glib)
  #:use-module (gnu packages gcc)
  #:use-module (gnu packages autotools)
  #:use-module (gnu packages maths)
  #:use-module (guix download)
  #:use-module (guix build-system gnu)
  #:use-module (guix licenses))

(define-public trexio
  (package
    (name "trexio")
    (version "2.0")
    (source (origin
              (method url-fetch)
              (uri (string-append "https://github.com/TREX-CoE/trexio/releases/download/v" version
				  "/trexio-" version ".0"
                                  ".tar.gz"))
              (sha256
               (base32
		"1d2cn4w2r9gfid5b9wrq9q290kqdnbjdmvli76s1i5r58kdg5vkf"
                ))))
    (build-system gnu-build-system)
    (arguments '(#:configure-flags '("--enable-silent-rules")))
    (inputs `(("hdf5" ,hdf5-1.12) ("gfortran", gfortran)))
    (synopsis "TREX I/O lbrary: trexio package")
    (description "APIs in C and Fortran to exchange wavefunction data.
		  Supports HDF5 and TEXT back ends.")
    (home-page "https://trex-coe.github.io/trexio")
    (license bsd-3)))

trexio
