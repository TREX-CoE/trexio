#!/bin/sh

if [ -f .devel ]; then
  RED='\033[31m'
  YELLOW='\033[1;33m'
  BLUE='\033[1;94m'
  NC='\033[0m' # No Color

  echo "${YELLOW}========================================================"
  echo "${RED}                         WARNING"
  echo "${YELLOW}========================================================"
  echo ""
  echo "  Developer mode is activated."
  echo "${NC}"
  echo "  This mode is intended for developers only."
  echo "  If you are not sure what this means, you should NOT"
  echo "  build the TREXIO library from the Git repository."
  echo ""
  echo "  Instead, please download an official release"
  echo "  (tar.gz archive) from the following address:"
  echo ""
  echo "${BLUE}  https://github.com/TREX-CoE/trexio/releases/latest"
  echo ""
  echo "${YELLOW}========================================================${NC}"
fi

autoreconf -i -Wall


