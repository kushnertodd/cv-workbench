#!/bin/bash
file_root=$1
if [ "$file_root" == "" ] ; then
  echo usage $0 file_root
  exit
fi
if [ ! -f json.template ] ; then
  echo missing file json.template
  exit
fi
sed -e "s/template/$file_root/g" json.template >$file_root.json
