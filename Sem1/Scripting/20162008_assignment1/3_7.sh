tr -d [:upper:] < secret.txt  | tr [e-za-d] [a-z] | tr -d [:digit:] | tr -d [:punct:] | tr -s [:alnum:]
