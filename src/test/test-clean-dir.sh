#!/bin/bash
for f in *.jpg *.bin *.txt ; do
  if [ -f $f ] ; then
    echo rm -f ../../images/$f
    rm -f ../../images/$f
    #ls -l ../../images/$f
  fi
done