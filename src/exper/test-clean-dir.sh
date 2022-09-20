#!/bin/bash
for f in *.jpg *.bin *.txt *.gp ; do
  if [ -f $f ] ; then
    echo rm -f ../../output/$f
    rm -f ../../output/$f
  fi
done
