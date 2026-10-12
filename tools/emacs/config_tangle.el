;; Thanks to Tobias's answer on Emacs Stack Exchange:
;; https://emacs.stackexchange.com/questions/38437/org-mode-batch-export-missing-syntax-highlighting


(package-initialize)
(add-to-list 'package-archives
             '("gnu" . "https://elpa.gnu.org/packages/"))
(add-to-list 'package-archives
             '("melpa-stable" . "https://stable.melpa.org/packages/"))
(add-to-list 'package-archives
             '("melpa" . "https://melpa.org/packages/"))
(setq package-archive-priorities '(("melpa-stable" . 100)
                                   ("melpa" . 50)
                                   ("gnu" . 10)))


(require 'font-lock)
(setq org-confirm-babel-evaluate nil)
(global-font-lock-mode t)
(setq org-src-fontify-natively t)
(require 'org)

(org-babel-do-load-languages
 'org-babel-load-languages
 '(
   (emacs-lisp . t)
   (python . t)
   (org . t)
   ))

;; The interpreter that runs the source blocks has to be one this Emacs can
;; drive, which is not always the one the library is built against: on MSYS2, a
;; MinGW python ahead of the MSYS one on PATH is spawned but cannot be talked
;; to, and the blocks then yield nothing at all. TREXIO_BABEL_PYTHON overrides
;; it for such cases.
(setq org-babel-python-command
      (or (getenv "TREXIO_BABEL_PYTHON") "python3 -q"))
(setq python-indent-guess-indent-offset-verbose nil) ;; Remove warning : Can’t guess python-indent-offset 
