#!/bin/bash 

# circle_area="NOT POSSIBLE"
# square_area="NOT POSSIBLE"
# rectangle_area="NOT POSSIBLE"
# r_triangle_area="NOT POSSIBLE"
# a_triangle_area="NOT POSSIBLE"
# trapezium_area="NOT POSSIBLE"

circle(){
	if [ $# -eq 1 ]
		then
		circle_area=$(echo "scale=2; 22/7*$1*$1"|bc| awk '{printf("%d\n",$1 + 0.5)}')
		#((circle_area = pi*$1*$1))
		#((area = $1*$1))
		#echo $area*3.14 | bc
		return $circle_area
	fi
	return 255
}	

square(){
	if [ $# -eq 1 ]
		then	
		((square_area = $1*$1))
		return $square_area
	fi
	return 255
}

rectangle(){
	if [ $# -eq 2 ]
		then
		((rectangle_area = $1*$2))
		return $rectangle_area
	fi
	return 255
}

r_triangle(){
	if [ $# -eq 2 ]
		then
		r_triangle_area=$(echo "scale=2; 0.5*$1*$2"|bc | awk '{printf("%d\n",$1 + 0.5)}')
		#echo "In r_triangle"
		return $r_triangle_area
		##return 0
	fi
	return 255
}

a_triangle(){
	if [ $# -eq 3 ]
		then 
		((semi = ($1+$2+$3)/2))
		((area = $semi *($semi - $1)*($semi - $2)*($semi - $3)))
		area=$(echo "scale=2; sqrt($area)"|bc|awk '{printf("%d\n",$1 + 0.5)}')
		return $area
	fi
		return 255;
}

trapezium(){
	if [ $# -eq 3 ]
		then 
		trapezium_area=$(echo "scale=2; (0.5*($1+$2))*$3"|bc | awk '{printf("%d\n",$1 + 0.5)}')
		#echo "In trapezium"
		return $trapezium_area;
		#return 0;
	fi	
		return 255;
}	