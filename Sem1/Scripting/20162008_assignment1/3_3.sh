touch myname
	gedit myname
	tr [a-z] [k-z1-9] < myname > secretagent.txt
	tr [k-z0-9] [a-z] < secretagent.txt
