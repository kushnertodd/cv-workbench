#!/bin/bash
here=$PWD
echo here $here
sh test-clean-dir.sh
for f in *.json ; do
  #echo cd ../..
  cd ../..
  echo ./cv-workbench $here/$f
  ./cv-workbench $here/$f
  #ls -ld ./cv-workbench $here/$f
  #echo cd $here
  cd $here
done
for f in *.jpg *.bin *.txt *.gp; do
  #echo $f
  if [ -f $f ] ; then
    echo "$ cmp $f ../../images/$f"
    cmp $f ../../images/$f
  fi
done
