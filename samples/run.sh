for dir in \
edge \
histogram \
hough \
morphology \
smooth \
transform
do
  echo $dir
  cd $dir
  sh run.sh
  cd ..
done
