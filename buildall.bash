#!/bin/bash

workdir=$(pwd)

cd ${workdir}/shared_code
./build.bash
cd ${workdir}

for d in ./labwork_*/
do
    echo "[in ${d}]"
    for d2 in $d/excercise_*/
    do
        echo "[in ${d2}]"
        (cd $d2; ./build.bash)
    done
done




