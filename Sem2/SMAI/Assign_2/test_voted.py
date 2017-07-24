from __future__ import division
from sklearn.model_selection import KFold
from sklearn import model_selection
from sklearn.model_selection import cross_val_score
from sklearn.base import BaseEstimator,ClassifierMixin
import numpy as np
from numpy import matrix
import matplotlib.pyplot as plt
import sys
import csv

def read_data_breast_cancer(data):
	f = open('input.csv','rb')
	reader = csv.reader(f)
	for row in reader:
		s = row
		if s[-1] == '4':
				#s = np.negative(s)
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
	reader = csv.reader(f)
	for row in reader:
		s = row
		if s[-1] == 'b':
				#s = np.negative(s)
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
			temp = np.add(np.dot(w,s),b)	

			if yi * temp <= 0:
				temp = []
				w = np.add(np.dot(yi,s),w)
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


def voted_perceptron_predict(weights,test_data):

	voted_count=0	
	for samples in test_data:
		temp = 0
		for item in weights:
			# print item[0],x,item[1]
			w = item[0]
			b = item[1]
			c = item[2]

			temp = temp + c*np.sign(np.add(np.dot(w,samples[:-1]),b))
		temp = np.sign(temp)

		if temp == samples[-1]:
			voted_count = voted_count+1

	return voted_count


class Online_perceptron(BaseEstimator,ClassifierMixin):

	def __init__(self,Epochs):
		self.a = 0
		self.iteration = Epochs
		self.bias = 0
		#self.y = labels

	def fit(self,data,y):
		iteration=1
		self.a = [0] * len(data[0])
		while iteration <= self.iteration:
			for i in xrange(len(data)):
				# print self.a,data[i]
				temp = (np.dot(self.a,data[i]) + self.bias)*y[i]
				if temp <= 0 :
					self.a = self.a + 0.1*data[i]*y[i]
					self.bias = self.bias + y[i]
			iteration = iteration+1
		return self

	def predict(self,X):
		count=0
		y=[]
		for i in xrange(len(X)):
			# print "Inside Predict :",weight,x
			temp = (np.dot(self.a,X[i]) + self.bias)#
			temp = np.sign(temp)
			y.append(temp)
		return y


def Process_Perceptron(data):
	Epochs = [10,15, 20, 25, 30, 35,40, 45, 50]
	data_len = len(data[0])
	print data_len
	data = np.array(data)

	X = data[:,0:data_len-1]
	Y = data[:,data_len-1]

	kf = KFold(n_splits=10)
	kf.get_n_splits(data)

	online_percep = []
	voted_precep = []

	for num in Epochs:
		print 'For Epochs : ',num
		voted_count = 0
		online_count = 0
		
		for train_index,test_index in kf.split(data):
			w = [0]*(data_len-1)
			train_data = data[train_index]
			test_data = data[test_index]

			
			voted_weights = voted_perceptron_train_set(train_data,w,num)			
			voted_count = voted_count +  voted_perceptron_predict(voted_weights,test_data)
			a = [0]*(data_len-1)
			b = 0

		voted_acc = voted_count/(len(data))
		print 'Accuracy of Voted Perceptron',voted_acc
		voted_precep.append(voted_acc*100)

		vanilla = Online_perceptron(num).fit(X,Y)
		vanilla_accuracy = cross_val_score(vanilla,X,Y,cv=10)
		print "Vanilla Percep ",np.array(vanilla_accuracy).mean()
		online_percep.append(np.array(vanilla_accuracy).mean()*100)

	plt.plot(Num_Epochs,online_percep,'r--')
	plt.plot(Num_Epochs,voted_precep)
	plt.show()
		
	

if __name__ == "__main__":

	data=[]
	weights=[]
	read_data_breast_cancer(data)
	Process_Perceptron(data)
	data=[]
	weights=[]
	read_data_ionosphere(data)
	Process_Perceptron(data)