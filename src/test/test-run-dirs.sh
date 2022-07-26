#!/bin/bash
for f in filter* hough* hist* ; do
  if [ -d $f ] ; then
    cd $f 
    if [ -e test-run-dir.sh ] ; then
      echo sh $f/test-run-dir.sh
      sh test-run-dir.sh
    fi
    cd ..
  fi
done
