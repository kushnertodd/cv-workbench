echo "$ cd ../.."
cd ../..
#echo "PWD $PWD"
echo "$ ./cv-workbench test/hough-draw-lines.json"
./cv-workbench test/hough-draw-lines/test-hough-draw-lines.json
echo "$ cd test/hough-draw-lines"
cd test/hough-draw-lines
#echo "PWD $PWD"
for f in *.jpg; do
echo $f
echo "$ cmp $f ../../images/$f"
cmp $f ../../images/$f
done
