#!/bin/bash
for f in filter* hough* hist* transform*; do
  if [ -d $f ] ; then
    cd $f
    if [ ! -e test-clean-dir.sh ] ; then
      echo ln -s $f/test-clean-dir.sh 
      ln -s ../test-clean-dir.sh 
    fi
    if [ ! -e test-run-dir.sh ] ; then
      echo ln -s $f/test-run-dir.sh 
      ln -s ../test-run-dir.sh 
    fi
    cd ..
  fi
done
