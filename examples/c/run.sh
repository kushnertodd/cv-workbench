echo ./conv 4 6 3 3
./conv 4 6 3 3 > run.txt
diff run.txt conv.4-6-3-3.txt

echo ./conv 4 7 3 3
./conv 4 7 3 3 > run.txt
diff run.txt conv.4-7-3-3.txt

echo ./conv 5 6 3 3
./conv 5 6 3 3 > run.txt
#diff run.txt conv.5-6-3-3.txt

echo ./conv 5 6 4 3
./conv 5 6 4 3 > run.txt
diff run.txt conv.5-6-4-3.txt

echo ./conv 5 7 3 3
./conv 5 7 3 3 > run.txt
diff run.txt conv.5-7-3-3.txt

echo ./conv 5 7 4 3
./conv 5 7 4 3 > run.txt
diff run.txt conv.5-7-4-3.txt
