#!/bin/bash

for d in ./labwork_*/
do
    for d2 in $d/excercise_*/
    do
        (cd $d2; ./build.bash)
    done
done