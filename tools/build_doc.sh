#!/bin/bash
# Script to build the documentation

TREXIO_ROOT=$(dirname "${PWD}")

#   First define readonly global variables.
readonly DOCS=${TREXIO_ROOT}/docs
readonly SRC=${TREXIO_ROOT}/src
readonly TOOLS=${TREXIO_ROOT}/tools
readonly ELDIR=${TREXIO_ROOT}/tools/emacs
readonly HTMLIZE=${ELDIR}/htmlize.el
readonly CONFIG_DOC=${ELDIR}/config_doc.el  
readonly CONFIG_TANGLE=${ELDIR}/config_tangle.el


# Check that all the defined global variables correspond to files.
function check_preconditions()
{
    if [[ -z ${TREXIO_ROOT} ]]
    then
        print "TREXIO_ROOT is not defined"
        exit 1
    fi

    for dir in ${DOCS} ${SRC} ${TOOLS} ${ELDIR}
    do
        if [[ ! -d ${dir} ]]
        then
            print "${dir} not found"
            exit 2
        fi
    done
    
    for file in ${CONFIG_DOC} ${CONFIG_TANGLE}
    do
        if [[ ! -f ${file} ]]
        then
            print "${file} not found"
            exit 3
        fi
    done
}


# Download the htmlize Emacs plugin if not present
function install_htmlize()
{
    local url="https://github.com/hniksic/emacs-htmlize"
    local repo="emacs-htmlize"
    
    if [[ ! -f "${HTMLIZE}" ]]
    then
        cd ${TOOLS}
        git clone ${url} \
            && cp ${repo}/htmlize.el ${HTMLIZE} \
            && rm -rf ${repo}
        cd ..
    fi

    # Assert htmlize is installed
    [[ -f ${HTMLIZE} ]] \
        || exit 1
}


# Compile org-mode file into html
function extract_doc()
{
    local org=$1
    local dir=$2
    local local_html=${dir}/${org%.org}.html 
    local html=${DOCS}/${org%.org}.html 

    if [[ -f ${html} && ${org} -ot ${html} ]]
    then
    	return
    fi
    emacs --batch                    \
      --load ${HTMLIZE}          \
      --load ${CONFIG_DOC}       \
      ${org}                     \
      --load ${CONFIG_TANGLE}    \
      -f org-html-export-to-html  &> /dev/null
    mv -f ${local_html} ${DOCS}
    rm -f "${local_html}~" 

}


# The main function of the script.
function main() {
    
    # Check directories and files for existence
    check_preconditions
    
    # Install htmlize if needed
    install_htmlize

    # Create documentation
    cd ${SRC} 

    for dir in ${SRC}/templates_*/ ${TREXIO_ROOT}/ ${TREXIO_ROOT}/docs
    do
	dir=${dir%*/}
	echo ${dir}
        OLDPWD=$PWD
	cd ${dir}
    	for i in *.org
    	do
        	echo
        	echo "=======  ${i} ======="
        	extract_doc ${i} ${dir}
    	done
	cd $OLDPWD
    done

    echo
    echo "=======  README.org ======="
    extract_doc README.org ${SRC}


    if [[ $? -eq 0 ]]
    then
        cd ${DOCS}
        rm -f index.html
        
	ln README.html index.html
        exit 0
    else
        exit 3
    fi
}

main
