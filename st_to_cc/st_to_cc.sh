#! /bin/bash
#
cp st_to_cc.h /$HOME/include
#
gcc -c -Wall -I/$HOME/include st_to_cc.c
if [ $? -ne 0 ]; then
  echo "Compile error."
  exit
fi
#
mv st_to_cc.o ~/libc/st_to_cc.o
#
echo "Normal end of execution."
