for script in  \
  test-filter-edge-sobel-0-degrees.json \
  test-filter-edge-sobel-90-degrees.json
do
  cd ../..
  ./cv-workbench test/filter-edge-sobel/$script
  cd test/filter-edge-sobel
done
for f in *.jpg; do
  if ! cmp -s $f ../../images/$f ; then
    echo no match: $f
  fi
done
