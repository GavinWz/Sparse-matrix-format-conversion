#! /bin/bash
#
octave cc_to_st_test.m > cc_to_st_test.txt
if [ $? -ne 0 ]; then
  echo "Run error."
  exit
fi
#
echo "Normal end of execution."
