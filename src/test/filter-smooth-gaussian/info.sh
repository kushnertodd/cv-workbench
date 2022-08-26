rm info.txt
for f in key*diff*bin
do 
  echo =================>>info.txt
 echo $f >>info.txt
 ../../image-info $f | egrep "mean|standard" >>info.txt
done
