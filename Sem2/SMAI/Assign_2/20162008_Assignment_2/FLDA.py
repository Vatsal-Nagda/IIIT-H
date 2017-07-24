import numpy
import matplotlib.patches as mpatches
from numpy import matrix
import sys
import matplotlib.pyplot as plt
from LMS import process_LMS,plot_LMS_plane


data1=[]
data2=[]

def read_data_FLDA(data1,data2):
	
	f = open(c1,'r')
	for line in f:
		s=line.strip().split(' ')
		s=list(map(float, s))	
		data1.append(s)
		# print line.strip()
	f = open(c2,'r')
	for line in f:
		s=line.strip().split(' ')
		s=list(map(float, s))
		data2.append(s)
	

# def flda_train():
# 	pass


if __name__ == "__main__":

	global c1,c2
	c1 = raw_input("enter the file name to used as class1: \n")
	c2 = raw_input("enter the file name to used as class2: \n")

	read_data_FLDA(data1,data2)
	LMS1=[]
	LMS2=[]

	LMS_weight = process_LMS(0.1,c1,c2,LMS1,LMS2)
	for i in xrange(len(LMS2)):		#assumption that data of Class 2 is negated
		LMS2[i] = numpy.negative(LMS2[i])

	# print data1
	# print data2

	plt.scatter(list(zip(*data1)[0]),list(zip(*data1)[1]),color='red')
	plt.scatter(list(zip(*data2)[0]),list(zip(*data2)[1]),color='blue')

	plot_LMS_plane(LMS_weight,data1,data2)


	C1 = matrix(data1)
	C2 = matrix(data2)

	M1 = numpy.mean(C1,axis=0)		#  calculate mean of the vectors
	M2 = numpy.mean(C2,axis=0)
	M =  (M1+M2)/2
	C1 = [x-M1 for x in C1]			# calculate mean separated values
	C2 = [x-M2 for x in C2]
	# print M1,M2,M
	S1 = numpy.sum([numpy.matmul(x.T,x) for x in C1],axis=0)
	S2 = numpy.sum([numpy.matmul(x.T,x) for x in C2],axis=0)

	St = matrix(S1+S2)
	# print St
	ans = St.I * matrix(M1-M2).T
	print "Fishers Weight : ",ans

	# q=[]
	A = numpy.matrix(ans).tolist()
	A = [x[0] for x in A]
	for x in data1:
		# print x
		# print A
		temp = numpy.dot(A,x)/(numpy.linalg.norm(A) * numpy.linalg.norm(A))
		temp = numpy.dot(A,temp)
		plt.plot([x[0],temp[0]],[x[1],temp[1]],'b--')
		# q.append(temp)
		# print temp
	# plt.plot()
	for x in data2:
		# print x
		# print A
		temp = numpy.dot(A,x)/(numpy.linalg.norm(A) * numpy.linalg.norm(A))
		temp = numpy.dot(A,temp)
		plt.plot([x[0],temp[0]],[x[1],temp[1]],'g--')
		# q.append(temp)
		# print temp

	# x = [r[0]]	
	bias = -1 * numpy.dot(M,ans)
	# print bias	
	ans = numpy.array(ans)
	x = [0]
	y = [0]
	x.append(15*ans[0][0])
	y.append(15*ans[1][0])
	x.append(-15*ans[0][0])
	y.append(-15*ans[1][0])

	# print x,y

	plt.plot(x,y,label ='Fischer Discriminant')
	x = [-5,0,5]
	y = [numpy.matrix((-1*ans[0][0]*X - bias[0][0])/ans[1][0]) for X in x]
	y = [i.tolist() for i in y]
	y = [i[0][0] for i in y]
	# print x,y
	plt.plot(x,y,label = 'Fischer Classifier')
	plt.axis([-6,6,-6,6])
	plt.legend(loc='upper right')
	plt.show()