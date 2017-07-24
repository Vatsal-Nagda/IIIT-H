#!/bin/usr/python

print 'Welcome to IIIT authentication system'
print 'Choose:'
print '1-Register New User\n2-Log In\nAny other-Exit program'
choice=raw_input()
choice = int(choice)

names={}
auth={}

def new_usr_reg():
	str1 = raw_input()
	str1 = [s for s in str1.split(",")]
	global names
	global auth
	chck=str(str1).split('@')
	qew=chck[0].split('.')
	id='@students.iiit.ac.in'
	if len(str1[3]) < 8 or (id not in str1[2]) or str1[1].isdigit() == False:
		print 'Registr1ation Failed'
	elif str1[2].find(id) < 1:
		print 'Registr1ation Failed'
	elif len(qew) < 2 :	
		print 'Registr1ation Failed'
	else:
		names[str1[1]] = str1[0]
		auth[str1[1]] = str1[3]
		auth[str1[2]] = str1[3]
		print 'Success'

	return

def log_in():
	str1 = raw_input()
	str1 = [s for s in str1.split(",")]

	if str1[0] not in auth or auth[str1[0]] != str1[1]:
		print 'No'
	else:
		print 'Yes'

	return



while choice==1 or choice==2:
	if choice==1:
		new_usr_reg()
	elif choice==2 :
		log_in()
	choice=raw_input()
	choice = int(choice)

print 'OK Bye'