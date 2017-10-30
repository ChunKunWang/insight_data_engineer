#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. Below is an example of what might be found in this file if your program was written in Python
#
#python ./src/find_political_donors.py ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt

# Compile the codes in src to generate the exectuable file
cd src/
make clean
make
cd ..

# Run commend
./src/find_political_donors ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt

