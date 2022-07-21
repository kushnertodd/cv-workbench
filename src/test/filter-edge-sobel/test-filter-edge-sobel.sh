for script in  \
  test-filter-edge-sobel-0-degrees.json \
  test-filter-edge-sobel-90-degrees.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  echo "PWD $PWD"
  echo "$ ./cv-workbench test/$script"
  ./cv-workbench test/filter-edge-sobel/$script
  echo "$ cd test/filter-edge-sobel"
  cd test/filter-edge-sobel
done
#echo "PWD $PWD"
#for f in *.jpg; do
#echo $f
#echo "$ cmp $f ../../images/$f"
#cmp $f ../../images/$f
#done
