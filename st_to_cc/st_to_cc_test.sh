#! /bin/bash
#
gcc -c -Wall -I/$HOME/include st_to_cc_test.c
if [ $? -ne 0 ]; then
  echo "Compile error."
  exit
fi
#
gcc -o st_to_cc_test st_to_cc_test.o /$HOME/libc/st_to_cc.o -lm
if [ $? -ne 0 ]; then
  echo "Load error."
  exit
fi
#
rm st_to_cc_test.o
#
./st_to_cc_test > st_to_cc_test.txt
if [ $? -ne 0 ]; then
  echo "Run error."
  exit
fi
rm st_to_cc_test
#
echo "Normal end of execution."
