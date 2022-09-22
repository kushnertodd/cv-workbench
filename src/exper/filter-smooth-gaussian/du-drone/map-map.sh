for d in *drone*json ; do
  echo $d
  sed -e "s/drone/map/g" $d >../du-map/`echo $d | sed -e "s/drone/map/g"`
done
