groupadd hogwarts
	mkdir ~/SCE/
	sudo useradd -d ~/SCE/Assignment1/ -m -g hogwarts Hermione
	sudo useradd -g hogwarts Harry 
	sudo passwd Hermione
	su Hermione
	umask 0177
