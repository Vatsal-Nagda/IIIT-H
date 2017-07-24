from __future__ import division
from sklearn import model_selection
from sklearn.model_selection import cross_val_score
from sklearn.base import BaseEstimator,ClassifierMixin
import numpy
from numpy import matrix
import matplotlib.pyplot as plt
import sys
import csv

class Voted_Perceptron(BaseEstimator,ClassifierMixin):
	def __init__(self,Num_Epochs):
		self.weights = []
		self.Num_Epochs = Num_Epochs

	def fit(self,data,labels):
	#print data	
		b = 0
		w = [0] * len(data[0])
		c=1
		temp=[]
		temp.append(w)
		temp.append(b)
		temp.append(c)
		iteration=1
		while iteration <= self.Num_Epochs:

			#print w
			for i in xrange(len(data)):
				s = data[i]
				yi = labels[i]
				temp = numpy.add(numpy.dot(w,s),b)	

				if yi * temp <= 0:
					temp = []
					w = numpy.add(numpy.dot(yi,s),w)
					#print "W : ",w
					b = b + yi
					temp.append(w)
					temp.append(b)
					temp.append(c)
					self.weights.append(temp)
					c=1
					
				else:
					c = c+1
			#print iteration
			iteration = iteration+1

		temp = []
		temp.append(w)
		temp.append(b)
		temp.append(c)
		self.weights.append(temp)

		return self


	def predict(self,X):
		y = []
		for x in X:
			voted_count=0	
			temp = 0
			for item in self.weights:
				# print item[0],x,item[1]
				temp = temp + item[2]*numpy.sign(numpy.add(numpy.dot(item[0],x),item[1]))
			y.append(numpy.sign(temp))
		return y

class Online_perceptron(BaseEstimator,ClassifierMixin):

	def __init__(self,Num_Epochs):
		self.weights = [0]
		self.Num_Epochs = Num_Epochs
		self.b = 0
		#self.labels = labels

	def fit(self,data,labels):
		iteration=1
		self.weights = [0] * len(data[0])
		while iteration <= self.Num_Epochs:
			for i in xrange(len(data)):
				# print self.weights,data[i]
				temp = (numpy.dot(self.weights,data[i]) + self.b)*labels[i]
				if temp <= 0 :
					self.weights = self.weights + 0.1*data[i]*labels[i]
					self.b = self.b + labels[i]
			iteration = iteration+1
		return self

	def predict(self,X):
		count=0
		y=[]
		for i in xrange(len(X)):
			# print "Inside Predict :",weight,x
			temp = (numpy.dot(self.weights,X[i]) + self.b)#
			temp = numpy.sign(temp)
			y.append(temp)
		return y

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
		    s = list(map(float,row[1:]))
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
		    s = list(map(float,row))
		except ValueError:
		    pass
		else:
			#s=matrix(s),
			data.append(s)


def run_Algo(data):
	#learning_rate = float(raw_input("Enter the learning rate:\n"))
	Num_Epochs = [10,15, 20, 25, 30, 35,40, 45, 50,55,60,65,70,75,80,85,90,95,100]
	data_len = len(data[0])
	print data_len

	data = numpy.array(data)

	X = data[:,0:data_len-1]
	Y = data[:,data_len-1]

	voted_percep=[]
	online_percep=[]

	print "-------------Voted Perceptron----------------------"
	for num in Num_Epochs:
		voted = Voted_Perceptron(num).fit(X,Y)
		voted_accuracy = cross_val_score(voted,X,Y,cv=10)
		print num," --- ",numpy.array(voted_accuracy).mean()
		voted_percep.append(numpy.array(voted_accuracy).mean())

	print "-------------Vanilla Perceptron----------------------"
	for num in Num_Epochs:
		vanilla = Online_perceptron(num).fit(X,Y)
		vanilla_accuracy = cross_val_score(vanilla,X,Y,cv=10)
		print num," --- ",numpy.array(vanilla_accuracy).mean()
		online_percep.append(numpy.array(vanilla_accuracy).mean())

	plt.plot(Num_Epochs,online_percep,'r--',label='Vanilla ')
	plt.plot(Num_Epochs,voted_percep,label='Voted')
	plt.legend(loc='upper right')
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