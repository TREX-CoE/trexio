(define-module (trexio)
  #:use-module (guix packages)
  #:use-module (gnu packages pkg-config)
  #:use-module (gnu packages glib)
  #:use-module (gnu packages gcc)
  #:use-module (gnu packages autotools)
  #:use-module (gnu packages maths)  ;; contains hdf5
  #:use-module (guix download)
  #:use-module (guix build-system gnu)
  #:use-module (guix licenses))

(define-public trexio-2.0
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
		;; the hash below is produced by guix download <url>
		"1d2cn4w2r9gfid5b9wrq9q290kqdnbjdmvli76s1i5r58kdg5vkf"
                ))))
    (build-system gnu-build-system)
    (arguments '(#:configure-flags '("--enable-silent-rules")))
    (inputs `(("hdf5" ,hdf5) ("gfortran", gfortran)))
    (synopsis "TREX I/O library")
    (description "The TREXIO library defines a standard format for storing wave functions, together with
		 an C-compatible API such that it can be easily used in any programming language.")
    (home-page "https://trex-coe.github.io/trexio")
    (license bsd-3)))

(define-public trexio-2.1
  (package/inherit trexio-2.0
    (version "2.1.0")
    (source (origin
              (method url-fetch)
              (uri (string-append "https://github.com/TREX-CoE/trexio/releases/download/v" version
				  "/trexio-" version
                                  ".tar.gz"))
              (sha256
               (base32
		;; the hash below is produced by guix download <url>
		"10syfw4mq3wpp9anahmxnm7660bm1ya5xd9l5njai3xr8g4nca13"
                ))))))

(define-public trexio-2.2
  (package/inherit trexio-2.0
    (version "2.2.0")
    (source (origin
              (method url-fetch)
              (uri (string-append "https://github.com/TREX-CoE/trexio/releases/download/v" version
				  "/trexio-" version
                                  ".tar.gz"))
              (sha256
               (base32
		;; the hash below is produced by guix download <url>
		"1n9n1gbk5hgvg73am991xrv7ap002rz719a3nvh8m8ff9x10qd76"
                ))))))

(define-public trexio
  ;; Default version of TREXIO.
  trexio-2.2)

trexio
