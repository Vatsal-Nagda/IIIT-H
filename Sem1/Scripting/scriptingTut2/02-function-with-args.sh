	#!/bin/bash 

# a script to demo definition and calling of shell functions. 
# the function code must be placed before the call. 

# function body 

func()
{

echo "My name is $FUNCNAME. I'm called with $# parameter(s)"
echo
echo

ls -l $1

# if [ $# -eq 2 ]
# 	then
# echo "$(cat $2)"
# fi

return                             # optional

}

# call the function with/without arguments 

func  				# will it work? 


echo
echo
echo "==================================================" 
echo
echo

func IExist.txt f1       		# will it work?    


echo
echo
echo "==================================================" 

exit 0
