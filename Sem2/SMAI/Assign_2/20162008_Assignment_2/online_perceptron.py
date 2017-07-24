import numpy
import matplotlib.pyplot as plt
import sys

def read_data(data1,data2):
	c1 = raw_input("enter the file name to used as class1: \n")
	c2 = raw_input("enter the file name to used as class2: \n")

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

def online_perceptron_train_set(data,a,learning_rate):
	k=0
	flag = False

	while flag == False:
		flag = True
		# print
		for i in xrange(len(data)):
			# print i,a,data[i]
			temp = numpy.inner(a,data[i])
			#print temp,
			if temp <= 0 :
				k=k+1
				delta = numpy.dot(data[i],learning_rate)
				a = numpy.add(a,delta)
				flag = False
	print a
	print k
	return a

def online_preceptron_predict(weight,x):
	temp = numpy.add(numpy.dot(weight[:-1],x[:-1]),weight[-1])
	return numpy.sign(temp)


if __name__ == "__main__":
	a = [0,0,0]
	learning_rate = float(raw_input("Enter the learning rate:\n"))

	data1=[]
	data2=[]
	read_data(data1,data2)

	for i in xrange(len(data2)):		#assumption that data of Class 2 is negated
		data2[i] = numpy.negative(data2[i])

	#print data1
	#print data2
	data = []
	data.extend(data1)
	data.extend(data2)

	# for item in data:
	# 	print item

	a = online_perceptron_train_set(data,a,learning_rate)

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
	x = []
	xmin = min(float(s[0]) for s in data1)
	xmax = max(float(s[0]) for s in data1)
	xmin1 = min(float(s[0]) for s in data2)
	xmax1 = max(float(s[0]) for s in data2)
	xmin = min(xmin,xmin1) - 1
	xmax = max(xmax,xmax1) + 1
	x.append(xmin)
	x.append(xmax)

	y=[]

	for item in x:
		temp = (-1*a[0]*item - a[2])/a[1]
		y.append(temp)

	plt.plot(x,y,label='Online Perceptron')
	plt.legend(loc='upper right')
	plt.show()

