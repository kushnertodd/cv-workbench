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
  cd ../..
  if ! ./cv-workbench test/filter-edge-kirsch/$script ; then
    echo error running $script
  fi
  cd test/filter-edge-kirsch
done
for f in *.jpg; do
  if ! cmp -s $f ../../images/$f ; then
    echo no match: $f
  fi
done
