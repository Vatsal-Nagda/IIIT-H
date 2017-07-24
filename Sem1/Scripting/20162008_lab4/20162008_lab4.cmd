1_!	#!/bin/bash

	read n

	second_last=1
	last=1

	if [[ $n -ge 2 ]]; then
		echo -n "1 "
		echo -n "1 "
		for i in `seq 3 $n` ; do
			((curr = second_last+last))
			echo -n "$curr "
			((second_last = last))
			((last= curr))
		done
	elif [ $n -eq 1 ]; then
		echo -n 1
	fi

	exit 0

2


2_1	awk -f ../20162008_lab4/2_1_awkfile  grades.txt
	
	2_1_awkfile

		BEGIN{sum = 0 
			tot =0
	}

	{	
		if($2 == "A")
			sum = sum + ($3*10)
		if($2 == "A-")
			sum = sum + ($3*9)
		if($2 == "B")
			sum = sum + ($3*8)
		if($2 == "B-")
			sum = sum + ($3*7)
		if($2 == "C")
			sum = sum + ($3*6)
		if($2 == "C-")
			sum = sum + ($3*5)

		tot = tot+ $3*10

	}
	END{

		printf" %.2f",(sum/tot)*10
	}
	

2_2	awk 'BEGIN{ for(i=1;i<=10;i++) {printf"2*%d=%d\n",i,(2*i)}}'

2_3	awk -f ../20162008_lab4/2_3_awkfile R2D2.txt
	
	2_3_awkfile :
	BEGIN{ }
	{
		if(/r1/)
			{print "=>"$0}
		if(/r2/)
			{print "*"$0}
		else
			{print $0}
	}
	END {}


3
	<!DOCTYPE html>

	<html>
	<title>
		Vatsal Nagda's Home Page
	</title>

	<body>


		<h2>Vatsal Nagda</h2>
		<br><a href="tel:+918879064833">Phone : 8879064833<br><br>
		 <img src="me.jpeg" style="width:160px;height:160px;"><br>
		 Email :<a href="mailto:vatsalnagda@gmail.com" target="blanck">vatsalnagda@gmail.com </a><br>
		
		<br><a href="https://www.facebook.com/vatsaln94" target="blanck">
			<img src = "fb.jpeg" style="width:36px;height=36px" >
	</div>	
	</body>

	</html>