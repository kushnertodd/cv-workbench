for script in  \
  test-hough-accumulator-create-0-sobel.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #echo "PWD $PWD"
  echo "$ ./cv-workbench test/hough-accumulator-create/$script"
  ./cv-workbench test/hough-accumulator-create/$script
  echo "$ cd test/hough-accumlator-create"
  cd test/hough-accumulator-create
  #echo "PWD $PWD"
done
for f in *.txt *.bin; do
  echo $f
  echo "$ cmp $f ../../images/$f"
  cmp $f ../../images/$f
done
