#!/bin/bash
set -e

# Check that script is executed from tools directory
if [[ $(basename $PWD) != "tools" ]] ; then
  echo "This script should run in the tools directory"
  exit -1
fi

TREXIO_ROOT=$(dirname "${PWD}../")

#   First define readonly global variables.
readonly SRC=${TREXIO_ROOT}/src
readonly TOOLS=${TREXIO_ROOT}/tools

# Function to produce TREXIO source files from org-mode files
function tangle()
{
  emacs --batch "$1" \
        --load=${TOOLS}/emacs/config_tangle.el \
        --eval "(progn
              (require 'ob)
              (require 'ob-python)
              (goto-char (point-min))
              (while (re-search-forward \"^[[:space:]]*#\\\\+CALL:\" nil t)
                (beginning-of-line)
                (org-babel-lob-execute-maybe)
                (let ((current-prefix-arg '(4)))
                  (call-interactively 'org-ctrl-c-ctrl-c))
                (forward-line 1))
              (org-babel-tangle))" > "${TANGLE_LOG}" 2>&1
}

# Create trex.json file
cd ${TREXIO_ROOT}
TANGLE_LOG=$(mktemp)
trap 'rm -f "${TANGLE_LOG}"' EXIT
tangle trex.org
touch trex.json

# Emacs exits successfully even when a source block fails to run, and a failed
# run leaves a trex.json holding nothing but "{", which the generator then
# reports as a JSON syntax error far from the cause. Check the result instead of
# trusting the exit status, and say what was wrong with it.
if ! "${PYTHON:-python3}" -c '
import json, sys
try:
    with open(sys.argv[1]) as f:
        data = json.load(f)
except ValueError as e:
    raise SystemExit(f"trex.json is not valid JSON: {e}")
if not data:
    raise SystemExit("trex.json describes no groups at all")
' trex.json ; then
  echo "Error: the Emacs tangling of trex.org did not produce a usable trex.json." >&2
  echo "The org-babel blocks are what fills it, so the interpreter running them" >&2
  echo "is the usual suspect: set TREXIO_BABEL_PYTHON to one that this Emacs can" >&2
  echo "drive. Emacs said:" >&2
  cat "${TANGLE_LOG}" >&2
  exit 1
fi

