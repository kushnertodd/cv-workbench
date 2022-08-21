#!/bin/bash
for f in `cat images.txt`; do
  file=../../images/$f
  if [ -f $file ] ; then 
    echo rm -f ../../images/$f
  fi
done
