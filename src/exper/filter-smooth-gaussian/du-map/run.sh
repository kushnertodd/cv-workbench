for f in `cat json.txt`; do
  #echo $f
  cd ../../..
  echo ./cv-workbench test/filter-smooth-gaussian/du-map/$f
  ./cv-workbench test/filter-smooth-gaussian/du-map/$f
  cd test/filter-smooth-gaussian/du-map
done