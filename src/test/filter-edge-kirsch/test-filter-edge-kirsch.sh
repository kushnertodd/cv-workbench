for script in  \
  test-filter-edge-kirsch-n.json \
  test-filter-edge-kirsch-nw.json \
  test-filter-edge-kirsch-w.json \
  test-filter-edge-kirsch-sw.json \
  test-filter-edge-kirsch-s.json \
  test-filter-edge-kirsch-se.json \
  test-filter-edge-kirsch-e.json \
  test-filter-edge-kirsch-ne.json 
do
  echo "script '$script'"
  echo "$ cd ../.."
  cd ../..
  #$echo "PWD $PWD"
  echo "$ ./cv-workbench test/$script"
  ./cv-workbench test/filter-edge-kirsch/$script
  echo "$ cd test/filter-edge-kirsch"
  cd test/filter-edge-kirsch
  #echo "PWD $PWD"
done
for f in *.jpg; do
  echo $f
  echo "$ cmp $f ../../images/$f"
  cmp $f ../../images/$f
done
