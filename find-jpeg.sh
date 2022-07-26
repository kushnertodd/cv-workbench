out=${NAME}-jpeg.txt
echo jpeg list >$out
echo ==================================== >>$out
echo apt list
echo apt list >>$out
apt list | grep -i jpeg >>$out
echo ==================================== >>$out
echo /usr/include
echo /usr/include >>$out
find /usr/include -name \*jpeg\* >>$out
echo ==================================== >>$out
echo /usr/local
echo /usr/local >>$out
find /usr/local -name \*jpeg\* >>$out
echo ==================================== >>$out
echo /usr/lib
echo /usr/lib >>$out
find /usr/lib -name \*jpeg\* >>$out
echo ==================================== >>$out
echo /lib
echo /lib >>$out
find /lib -name \*jpeg\* >>$out
