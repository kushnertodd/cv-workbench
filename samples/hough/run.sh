for f in `cat run.txt`; do
  echo cv-workbench $f
  cv-workbench $f
done
