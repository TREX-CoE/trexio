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

(setq org-babel-python-command "python3 -q")

