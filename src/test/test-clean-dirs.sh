#!/bin/bash
for f in filter* hough* hist* ; do
  if [ -d $f ] ; then
    echo cd $f
    cd $f
    if [ -e test-clean-dir.sh ] ; then
      echo sh $f/test-clean-dir.sh
      sh test-clean-dir.sh
    else
      echo missing test-clean-dir.sh
    fi
    cd ..
  fi
done
