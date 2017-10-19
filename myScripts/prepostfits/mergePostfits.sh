#!/bin/bash

if [ $# -lt 1 ] ; then
    echo "  "
    echo "  ./merge.sh ../rootfiles/<systematic>/<analysis>"
    echo "  ./merge.sh ../minitrees/<systematic>/<analysis>"
    echo "  "
    exit -1
fi

FOLDER="$1"

pushd $FOLDER

rm -rf 17_VV.root
 hadd -f -k 17_VV.root         02_WZTo3LNu.root 03_VZ.root 06_WW.root

popd
