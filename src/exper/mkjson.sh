#!/bin/bash
file_root=$1
if [ "$file_root" == "" ] ; then
  echo usage $0 file_root
  exit
fi
if [ ! -f template.json ] ; then
  echo missing file template.json
  exit
fi
sed -e "s/template/$file_root/g" template.json >$file_root.json
