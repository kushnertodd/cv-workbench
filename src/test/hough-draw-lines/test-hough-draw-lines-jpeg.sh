for script in  \
  test-hough-draw-lines-bin.json \
  test-hough-draw-lines-jpeg.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #echo "PWD $PWD"
  echo "$ ./cv-workbench test/$script"
  ./cv-workbench test/hough-draw-lines/$script
  echo "$ cd test/hough-draw-lines"
  cd test/hough-draw-lines
  #echo "PWD $PWD"
done
for f in *.jpg; do
  echo $f
  echo "$ cmp $f ../../images/$f"
  cmp $f ../../images/$f
done
