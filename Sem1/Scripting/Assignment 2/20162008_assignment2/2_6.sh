tar xvzf Submissions.tar.gz > /dev/null

list="$(ls Submissions | sort -r -t'_' -k2,5 | awk -F'_' '!(x[$2,$5]++)' | awk -F'_' '{if(NF == 5){print $0}}')"

mkdir Latest\ Files

cd Latest\ Files 

prob="$(echo "$list" | cut -d'_' -f2 | uniq)"

for i in $prob ;do
	echo $i;
	mkdir $i;
done 

cd ../

for i in $list; do
	#echo $i; 
	prob="$(echo "$i" | cut -d'_' -f2)"
	cp -r Submissions/$i Latest\ Files/$prob
done