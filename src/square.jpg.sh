 rm  square.jpg.final.sh
for f in square*jpg
do 
echo "echo '#=================='">> square.jpg.final.sh
 echo "echo '# $f'" >> square.jpg.final.sh
 echo "echo '#----------------------------'" >> square.jpg.final.sh
 echo ./djpeginfo $f \|grep components >> square.jpg.final.sh
done
