from __future__ import division
import numpy
import matplotlib.pyplot as plt
import sys
		

def read_data_LMS(data1,data2,c1,c2):
	
	f = open(c1,'r')
	for line in f:
		s=line.strip().split(' ')
		s.append('1')
		s=list(map(float, s))	
		data1.append(s)
		# print line.strip()
	f = open(c2,'r')
	for line in f:
		s=line.strip().split(' ')
		s.append('1')
		s=list(map(float, s))
		data2.append(s)
		#print line.strip()	

	for i in xrange(len(data2)):		#assumption that data of Class 2 is negated
		data2[i] = numpy.negative(data2[i])	


def LMS_train_set(data,a,learning_rate,threshold):
	k=0
	b=[1]*len(data)
	delta = threshold
	while delta >= threshold:
		# flag = True
		# print
		for i in xrange(len(data)):
			# print i,a,data[i]
			temp = numpy.dot(b[i]-numpy.inner(a,data[i]),data[i])
			k=k+1
			# print "temp : ",temp
			error = learning_rate * temp
			# delta = numpy.dot(data[i],learning_rate)
			learning_rate = 1/k;
			a = numpy.add(a,error)
			delta = numpy.linalg.norm(error)
			# print 'Delta : ',delta
			# flag = False
	print 'weight vector : ',a
	print 'iterations : ',k
	return a

# def online_preceptron_predict(weight,x):
# 	temp = numpy.add(numpy.dot(weight[:-1],x[:-1]),weight[-1])
# 	return numpy.sign(temp)

def process_LMS(learning_rate,c1,c2,data1,data2):
	a = [0,0,0]

	read_data_LMS(data1,data2,c1,c2)

	data = []
	data.extend(data1)
	data.extend(data2)

	# for item in data:
	# 	print item

	a = LMS_train_set(data,a,learning_rate,1)
	return a


def plot_LMS_points(data1,data2):
	xs = [x[0] for x in data1]
	ys = [x[1] for x in data1]
	#xs.extend(xs1)
	for i in xrange(len(data2)):		#assumption that data of Class 2 is negated
		data2[i] = numpy.negative(data2[i])

	xs1 = [x[0] for x in data2]
	ys1 = [x[1] for x in data2]
	#ys.extend(ys1)
	#print data2

	plt.scatter(xs,ys,color='red')
	plt.scatter(xs1,ys1,color='blue')
	
def plot_LMS_plane(a,data1,data2):
	x = []
	xmin = min(float(s[0]) for s in data1)
	xmax = max(float(s[0]) for s in data1)
	xmin1 = min(float(s[0]) for s in data2)
	xmax1 = max(float(s[0]) for s in data2)
	xmin = min(xmin,xmin1) #- 1
	xmax = max(xmax,xmax1) #+ 1
	x.append(xmin)
	x.append(xmax)
	y=[]
	for item in x:
		temp = (-1*a[0]*item - a[2])/a[1]
		y.append(temp)
	plt.plot(x,y,'y--',label = 'LMS')

if __name__ == "__main__":	
	learning_rate = float(raw_input("Enter the learning rate:\n"))

	c1 = raw_input("enter the file name to used as class1: \n")
	c2 = raw_input("enter the file name to used as class2: \n")
	data1=[]
	data2=[]
	a = process_LMS(learning_rate,c1,c2,data1,data2)
	plot_LMS_points(data1,data2)
	plot_LMS_plane(a,data1,data2)
	plt.legend(loc='upper left')
	plt.show()

