;; Thanks to Tobias's answer on Emacs Stack Exchange:
;; https://emacs.stackexchange.com/questions/38437/org-mode-batch-export-missing-syntax-highlighting


(package-initialize)

(require 'htmlize)
(require 'font-lock)
(setq org-confirm-babel-evaluate nil)
(global-font-lock-mode t)
(setq org-src-fontify-natively t)

;(require 'ox-latex)
;(setq org-latex-listings t)
;(add-to-list 'org-latex-packages-alist '("" "listings"))
;(add-to-list 'org-latex-packages-alist '("" "color"))


(require 'subr-x) ;; for `when-let'
(unless (boundp 'maximal-integer)
  (defconst maximal-integer (lsh -1 -1)
    "Maximal integer value representable natively in emacs lisp."))

(defun face-spec-default (spec)
  "Get list containing at most the default entry of face SPEC.
Return nil if SPEC has no default entry."
  (let* ((first (car-safe spec))
     (display (car-safe first)))
    (when (eq display 'default)
      (list (car-safe spec)))))

(defun face-spec-min-color (display-atts)
  "Get min-color entry of DISPLAY-ATTS pair from face spec."
  (let* ((display (car-safe display-atts)))
    (or (car-safe (cdr (assoc 'min-colors display)))
    maximal-integer)))

(defun face-spec-highest-color (spec)
  "Search face SPEC for highest color.
That means the DISPLAY entry of SPEC
with class 'color and highest min-color value."
  (let ((color-list (cl-remove-if-not
             (lambda (display-atts)
               (when-let ((display (car-safe display-atts))
                  (class (and (listp display)
                          (assoc 'class display)))
                  (background (assoc 'background display)))
             (and (member 'light (cdr background))
                  (member 'color (cdr class)))))
             spec)))
    (cl-reduce (lambda (display-atts1 display-atts2)
         (if (> (face-spec-min-color display-atts1)
            (face-spec-min-color display-atts2))
             display-atts1
           display-atts2))
           (cdr color-list)
           :initial-value (car color-list))))

(defun face-spec-t (spec)
  "Search face SPEC for fall back."
  (cl-find-if (lambda (display-atts)
        (eq (car-safe display-atts) t))
          spec))

(defun my-face-attribute (face attribute &optional frame inherit)
  "Get FACE ATTRIBUTE from `face-user-default-spec' and not from `face-attribute'."
  (let* ((face-spec (face-user-default-spec face))
     (display-attr (or (face-spec-highest-color face-spec)
               (face-spec-t face-spec)))
     (attr (cdr display-attr))
     (val (or (plist-get attr attribute) (car-safe (cdr (assoc attribute attr))))))
    ;; (message "attribute: %S" attribute) ;; for debugging
    (when (and (null (eq attribute :inherit))
           (null val))
      (let ((inherited-face (my-face-attribute face :inherit)))
    (when (and inherited-face
           (null (eq inherited-face 'unspecified)))
      (setq val (my-face-attribute inherited-face attribute)))))
     ;;(message "face: %S attribute: %S display-attr: %S, val: %S" face attribute display-attr val) ;; for debugging
    (or val 'unspecified)))

(advice-add 'face-attribute :override #'my-face-attribute)



