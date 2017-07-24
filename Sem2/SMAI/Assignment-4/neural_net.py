import sys
import numpy as np
import math

def sigmoid(x):
	return 1/(1+np.exp(-x))

def derivate_sigmoid(x):
	return x*(1.0 - x)


class DigitClassify_NeuralNetwork(object):
	""" Neural Network to Classify Digits """

	def __init__(self,nw_size):
		""" Parameter initialization for the number of nodesin each of the layer in network"""
		self.nw_size = nw_size
		self.num_layers = len(nw_size)
		# self.input_layers = input_layers + 1	# for the bias
		# self.hidden_layers = hidden_layers
		# self.output_layers = output_layers

		# """ Netactivations for each layers """
		# self.net_i = [1.0]*self.input_layers		# 	Input layer net's
		# self.net_h = [1.0]*self.hidden_layers		#	Hidden layer net's
		# self.net_o = [1.0]*self.output_layers		#	Output layer net's

		""" Create random weight vectors """
		self.bias = [np.random.randn(y,1)for y in self.nw_size[1:]]			#	weights b/w input n hidden layer
		self.weight = [np.random.randn(y,x) for x,y in zip(self.nw_size[:-1],self.nw_size[1:])]		#	weights b/w hidden n output layer

	def FeedForward_step(self,input_vec):
		z = input_vec
		for w,b in zip(self.weights,self.bias):		
			z = np.dot(w,z)+b
			# self.net_actvs.append(z)		""" net_actvs is a list[] where each element of list corresponds to the list
			# 									of net activations at that layer """
			z = sigmoid(z)			
			""" for every pair (w,b) in zip(weights,bias) calculate the activation
			this each pair corresponds to each layer's calculation
			and the same has to given to the other layers 
			i.e. z(k) = sigmoid( W(k).z(k-1) + b(k-1) )"""	

	def Stochastic_Gradient_Descent(self,input_data,batch_size,epochs,eta):
		pass

	def backpropogation(self,input_x,expected_t):
		pass
		net_actvs = []
		z = input_x
		for w,b in zip(self.weights,self.bias):		
			z = np.dot(w,z)+b
			net_activations.append(z)					""" net_actvs is a list[] where each element of list 
													corresponds to the list	of net activations at that layer """
			z = sigmoid(z)

		one = np.ones(np.shape(net_activations[1]))
		delta_o = np.multiply((expected_t-z),np.multiply(net_activations[1],(one - net_activations[1])))	#delta k (o/p)
		
		""" Updating weights of output layer """
		for k in xrange(self.nw_size[-1]):
			for j in xrange(self.nw_size[1]):
				self.weights[1][k][j] += eta*delta_o[k]*net_activations[0][k]

		""" calculating delta for hidden layers """

		one = np.ones(np.shape(net_activations[0]))
	




def preprocess_data(data):
	data = np.array(data)
	feature_vector=[]
	for row in xrange(0,32,4):
		for cols in xrange(0,32,4):
			# print row,cols
			temp = [data[row+k][cols:cols+4] for k in xrange(4)]
			# print temp
			feature_vector.append(np.count_nonzero(temp))
	return feature_vector

def read_data(input_data,labels):
	f = open('optdigits-orig.tra','r')
	entire_file = f.readlines()	
	entire_file = entire_file [21:]
	# removing the header present at the start of the file which is just information about it

	i=0
	data=[]
	# print entire_file[32].strip()
	for line in entire_file:
		if i == 0:
			if len(data) !=0:
				input_data.append(preprocess_data(data))		#append the entire image as input to list
			data=[]
		if i != 32:
			data.append(list(map(int,line.strip())))
		else:
			labels.append(int(line.strip()))
		i = (i+1)%33

	if i == 0:
		if len(data) !=0:
			input_data.append(preprocess_data(data))


input_data=[]
labels=[]
read_data(input_data,labels)
# print input_data[0],len(input_data[0])
# print preprocess_data(input_data[0]),labels[0]

# for line,label in zip(input_data,labels):
# 	for x in line:
# 		sys.stdout.write(str(x)+",")
# 	sys.stdout.write(str(label)+"\n")
