for script in  \
  test-filter-edge-roberts-0-degrees.json \
  test-filter-edge-roberts-90-degrees.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #$echo "PWD $PWD"
  echo "$ ./cv-workbench test/filter-edge-roberts/$script"
  ./cv-workbench test/filter-edge-roberts/$script
  echo "$ cd test/filter-edge-roberts"
  cd test/filter-edge-roberts
  #echo "PWD $PWD"
done
for f in *.jpg; do
  echo $f
  echo "$ cmp $f ../../images/$f"
  cmp $f ../../images/$f
done
