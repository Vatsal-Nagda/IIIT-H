awk '{ for(i=1;i<=$1;i++)printf "*" ;printf " "$NF" " ; for(i=3;i<NF;i++){printf $i" "}{printf $2"\n"}}' ../resources_assignment-2/numbers.txt
