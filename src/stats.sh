#!/bin/bash
file=$1
if [ -z "$file" ] ; then
  echo usage: $0 file
else
  echo stats for $file
  echo " " 
  echo values:
  ./image-info  $file
  echo " "
  echo stats:
  ./image-stats  $file
fi
