#!/bin/bash

DIR=$1

gcc ./${DIR}/*.c ../../shared_code/shared_code.o -lm -std=c99 -Wall -Werror -Wno-unused -Wno-incompatible-pointer-types -I../../ -o ./${DIR}/output.out
