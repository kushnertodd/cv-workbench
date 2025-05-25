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
  echo sh run.sh
  sh run.sh
  cd ..
done
