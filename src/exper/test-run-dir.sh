#!/bin/bash
here=$PWD
echo here $here
if [ ! -d ../../output ] ; then
  mkdir ../../output
  touch ../../output/.gitkeep
fi
rm -f ../../output/*
for f in *.json ; do
  #echo cd ../..
  cd ../..
  echo ./cv-workbench $here/$f
  ./cv-workbench $here/$f
  #ls -ld ./cv-workbench $here/$f
  #echo cd $here
  cd $here
done
