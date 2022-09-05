echo ./conv-wb 4 6 3 3
./conv-wb 4 6 3 3 > run-wb.txt
 diff  run-wb.txt conv.4-6-3-3-wb.txt

echo ./conv-wb 4 7 3 3
./conv-wb 4 7 3 3 > run-wb.txt
 diff  run-wb.txt conv.4-7-3-3-wb.txt

echo ./conv-wb 5 6 3 3
./conv-wb 5 6 3 3 > run-wb.txt
diff run-wb.txt conv.5-6-3-3-wb.txt

echo ./conv-wb 5 6 4 3
./conv-wb 5 6 4 3 > run-wb.txt
 diff  run-wb.txt conv.5-6-4-3-wb.txt

echo ./conv-wb 5 7 3 3
./conv-wb 5 7 3 3 > run-wb.txt
 diff  run-wb.txt conv.5-7-3-3-wb.txt

echo ./conv-wb 5 7 4 3
./conv-wb 5 7 4 3 > run-wb.txt
 diff  run-wb.txt conv.5-7-4-3-wb.txt
