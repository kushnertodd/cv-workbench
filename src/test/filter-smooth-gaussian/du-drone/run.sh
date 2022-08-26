for f in `cat json.txt`; do
  #echo $f
  cd ../../..
  echo ./cv-workbench test/filter-smooth-gaussian/du-drone/$f
  ./cv-workbench test/filter-smooth-gaussian/du-drone/$f
  cd test/filter-smooth-gaussian/du-drone
done
