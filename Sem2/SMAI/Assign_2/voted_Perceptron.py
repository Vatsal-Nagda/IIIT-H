from __future__ import division
import numpy
from numpy import matrix
import matplotlib.pyplot as plt
import sys
import csv

def read_data_breast_cancer(data):
	print "--------FOR BREAST CANCER DATA---------------------------"
	f = open('input.csv','rb')
	reader = csv.reader(f)
	for row in reader:
		s = row
		if s[-1] == '4':
				#s = numpy.negative(s)
			s[-1] = -1
		else:
			s[-1] = 1		
		try:
		    s = list(map(int,row[1:]))
		except ValueError:
		    pass
		else:
			#s=matrix(s)
			data.append(s)


def read_data_ionosphere(data):
	f = open('iono.csv','rb')
	print "--------FOR IONOSPHERE DATA---------------------------"
	reader = csv.reader(f)
	for row in reader:
		s = row
		if s[-1] == 'b':
				#s = numpy.negative(s)
			s[-1] = -1
		else:
			s[-1] = 1		
		try:
		    s = list(map(float,row[1:]))
		except ValueError:
		    pass
		else:
			#s=matrix(s)
			data.append(s)


def voted_perceptron_train_set(data,w,Num_Epochs):
	#print data	
	b = 0
	c=1
	temp=[]
	temp.append(w)
	temp.append(b)
	temp.append(c)
	iteration=1
	while iteration <= Num_Epochs:

		#print w
		for i in xrange(len(data)):
			s = data[i]
			s = s[:-1]
			yi = data[i][-1]
			temp = numpy.add(numpy.dot(w,s),b)
			# print "O.G.",data[i]
			# print "Modified",s
			#print data[i][-1],	

			if yi * temp <= 0:
				temp = []
				w = numpy.add(numpy.dot(yi,s),w)
				#print "W : ",w
				b = b + data[i][-1]
				temp.append(w)
				temp.append(b)
				temp.append(c)
				weights.append(temp)
				c=1
				
			else:
				c = c+1
		#print iteration
		iteration = iteration+1

	temp = []
	temp.append(w)
	temp.append(b)
	temp.append(c)
	weights.append(temp)

	return weights


def voted_perceptron_predict(weights,x):
	temp = 0
	for item in weights:
		# print item[0],x,item[1]
		temp = temp + item[2]*numpy.sign(numpy.add(numpy.dot(item[0],x),item[1]))
	return numpy.sign(temp)


def distribute_data(data):
	# print len(data)
	local=[]
	segment = len(data)//10
	i=0
	for y in xrange(len(data)//segment - 1):
		temp = data[i:i+segment]
		local.append(temp)
		i = i+segment
	#	print i
	temp = data[i:]
	local.append(temp)	
	return local


def training_data(final,i):
	local = []
	for y in xrange(5):
		if y != i :
			for item in final[y]:
				local.append(item)
	# print local
	# print len(local)
	return local

def process(data):
	local = []
	for i in xrange(len(data)):
		temp = data[i]
		if data[i][-1] == -1:
			temp = numpy.negative(data[i])
			temp[-1] = -1
		# print temp
		local.append(temp)
	return local


def online_perceptron_train_set(data,a,Epoch):
	k=0
	flag = False
	iteration=1
	while iteration <= Epoch and flag != True:
		flag = True
		# ``print
		for i in xrange(len(data)):
			# print i,a,data[i]
			temp = numpy.inner(a,data[i])
			#print temp,
			if temp <= 0 :
				k=k+1
				delta = numpy.dot(data[i],1)
				a = numpy.add(a,delta)
				flag = False
		iteration = iteration+1
	# print a
	# print k
	return a

def online_preceptron_predict(weight,x):
	# print "Inside Predict :",weight,x
	temp = numpy.add(numpy.dot(weight[:-1],x[:-1]),weight[-1])
	return numpy.sign(temp)


def run_Algo(data):
	#learning_rate = float(raw_input("Enter the learning rate:\n"))
	Num_Epochs = [10,15, 20, 25, 30, 35,40, 45, 50]
	data_len = len(data[0])
	print data_len
	final = distribute_data(data)
	final_online = process(data)
	final_online = distribute_data(final_online)

	# for item in final_online:
	# 	for i in item:
	# 		print i

	# a = [0,0,0,0,0,0,0,0,0,0]
	# online_weight = online_perceptron_train_set(final_online,a,1)
	# print online_weight	
	online_percep = []
	voted_precep = []

	for num in Num_Epochs:
		print 'For Epochs : ',num
		voted_count = 0
		online_count = 0
		for i in range(10):
			w = [0]*(data_len-1)
			train_data = training_data(final,i)
			test_data = final[i]
			online_train_data = training_data(final_online,i)
			# for q in online_train_data:
			# 	print q
			online_test_data = final_online[i]
			# print online_test_data
			
			voted_weights = voted_perceptron_train_set(train_data,w,num)			
			a = [0]*(data_len)
			online_weight = online_perceptron_train_set(online_train_data,a,1)
			# print online_weight
			for item in test_data:
				yi = voted_perceptron_predict(voted_weights,item[:-1])
				if yi == item[-1]:
					voted_count = voted_count+1
				# data_for_online_perceptron
			for item in online_test_data:
				yi = online_preceptron_predict(online_weight,item)
				if yi == item[-1]:
					online_count = online_count+1	

		voted_acc = voted_count/(len(data))
		online_acc = online_count/(len(data))
		print 'Accuracy of Voted Perceptron',voted_acc
		voted_precep.append(voted_acc*100)
		print 'Accuracy of Online Perceptron',online_acc
		online_percep.append(online_acc*100)

	plt.plot(Num_Epochs,online_percep,'r--')
	plt.plot(Num_Epochs,voted_precep)
	plt.show()
		
	

if __name__ == "__main__":

	data=[]
	weights=[]
	read_data_breast_cancer(data)
	run_Algo(data)
	data=[]
	weights=[]
	read_data_ionosphere(data)
	run_Algo(data)