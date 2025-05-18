for dir in \
edge \
histogram \
hough \
morphology \
smooth
do
  echo $dir
  echo cd $dir
  cd $dir
  echo sh clean.sh
  sh clean.sh
  cd ..
done
