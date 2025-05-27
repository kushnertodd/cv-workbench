for dir in \
edge \
histogram \
hough \
morphology \
smooth
do
  echo $dir
  cd $dir
  sh run.sh
  cd ..
done
