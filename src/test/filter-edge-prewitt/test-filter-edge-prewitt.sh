for script in  \
  test-filter-edge-prewitt-0-degrees.json \
  test-filter-edge-prewitt-90-degrees.json
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #$echo "PWD $PWD"
  echo "$ ./cv-workbench test/$script"
  ./cv-workbench test/filter-edge-prewitt/$script
  echo "$ cd test/filter-edge-prewitt"
  cd test/filter-edge-prewitt
  #echo "PWD $PWD"
done
for f in *.jpg; do
  echo $f
  echo "$ cmp $f ../../images/$f"
  cmp $f ../../images/$f
done
