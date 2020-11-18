#!/bin/bash

DIR=$1

gcc ./${DIR}/*.c -lm -std=c99 -Wall -Werror -o ./${DIR}/output.out