#!/bin/bash
here=$PWD
echo here $here
sh test-clean-dir.sh
for f in `cat json.txt` ; do
  #echo cd ../..
  cd ../..
  echo ./cv-workbench $here/$f
  ./cv-workbench $here/$f
  #ls -ld ./cv-workbench $here/$f
  #echo cd $here
  cd $here
done
for f in `cat images.txt`; do
  #echo $f
  if [ -f $f ] ; then
    echo "$ cmp $f ../../images/$f"
    #ls ../../images/$f
    cmp $f ../../images/$f
  fi
done
