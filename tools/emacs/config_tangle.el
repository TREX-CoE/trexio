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

(org-babel-do-load-languages
 'org-babel-load-languages
 '(
   (emacs-lisp . t)
   (shell . t)
   (python . t)
   (fortran . t)
   (C . t)
   (org . t)
   (makefile . t)
   ))


; The following is required to compute the file names
(setq pwd (file-name-directory buffer-file-name))
(setq name (file-name-nondirectory (substring buffer-file-name 0 -4)))
(setq f  (concat pwd name "_f.f90"))
(setq fh (concat pwd name "_fh.f90"))
(setq c  (concat pwd name ".c"))
(setq h  (concat name ".h"))
(setq h_private  (concat name "_private.h"))
(setq c_test  (concat pwd "test_" name ".c"))
(setq f_test  (concat pwd "test_" name "_f.f90"))
(org-babel-lob-ingest "../tools/lib.org")

