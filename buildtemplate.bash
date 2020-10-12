#!/bin/bash

DIR=$1

gcc ./${DIR}/*.c -lm -std=c99 -o ./${DIR}/output.out