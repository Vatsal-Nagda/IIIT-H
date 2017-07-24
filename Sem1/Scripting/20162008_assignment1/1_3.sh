su Harry
	ssh Hermione@localhost
	#now hermione prompt
 i=1;while [ 1 ]; do  echo $i; ((i++)); sleep 1; done |tee /dev/$(who|grep Hermione|cut -d' ' -f2)

