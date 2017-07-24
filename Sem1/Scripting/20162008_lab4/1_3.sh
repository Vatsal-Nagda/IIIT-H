
BEGIN{}
{
count =0
Arr[count] = $0
count++
}
END{

for i in `seq 0 $count-1`
do
	for j in `seq 1 $count-1`
	do
		if [[ ${Arr[$j]} -ge ${Arr[$j+1]} ]]; then
			((temp = ${Arr[j]}))
			((Arr[j] = ${Arr[j+1]}))
			((Arr[j+1] = temp))
		fi
	done
done

for i in `seq 0 $count-1`
do
	print ${Arr[$i]}

}