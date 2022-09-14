for script in  \
  test-hough-image-create-0-sobel.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #echo "PWD $PWD"
  echo "$ ./cv-workbench test/hough-image-create/$script"
  ./cv-workbench test/hough-image-create/$script
  echo "$ cd test/hough-accumlator-create"
  cd test/hough-image-create
  #echo "PWD $PWD"
done
for f in *.txt *.bin; do
  echo $f
  echo "$ cmp $f ../../images/$f"
  cmp $f ../../images/$f
done
