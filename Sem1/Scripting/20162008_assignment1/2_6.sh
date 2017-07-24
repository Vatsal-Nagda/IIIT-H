a=$(echo `find ./ -type f -printf "%s+0"`|bc) ; echo " scale=2; $a/1024 " | bc
