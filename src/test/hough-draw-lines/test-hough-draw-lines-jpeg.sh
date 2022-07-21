script_jpeg=test-hough-draw-lines-jpeg.json
echo "script '$script_jpeg'"
echo "$ cd ../.."
cd ../..
#echo "PWD $PWD"
echo "$ ./cv-workbench test/$script_jpeg"
./cv-workbench test/hough-draw-lines/$script_jpeg
echo "$ cd test/hough-draw-lines"
cd test/hough-draw-lines
#echo "PWD $PWD"
for f in *.jpg; do
echo $f
echo "$ cmp $f ../../images/$f"
cmp $f ../../images/$f
done
