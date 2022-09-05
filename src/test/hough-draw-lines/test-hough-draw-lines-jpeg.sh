for script in  \
  test-hough-draw-lines-0-degrees-jpeg.json \
  test-hough-draw-lines-90-degrees-jpeg.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #echo "PWD $PWD"
  echo "$ ./cv-workbench test/hough-draw-lines/$script"
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
