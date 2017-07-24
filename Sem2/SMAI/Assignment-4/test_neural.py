import csv
import sys
import numpy as np
import math

def sigmoid(x):
    return 1/(1+np.exp(-x))

def derivate_sigmoid(x):						# f'(net_k) = f(net_k)*(1-f(net_k)
    return sigmoid(x)*(1.0 - sigmoid(x))


class DigitClassify_NeuralNetwork(object):
    """ Neural Network to Classify Digits """

    def __init__(self,nw_size,eta):
        """ Parameter initialization for the number of nodesin each of the layer in network"""
        self.eta = eta
        self.nw_size = nw_size
        self.num_layers = len(nw_size)
        self.d = nw_size[0]
        self.nH = nw_size[1]
        self.c = nw_size[2]
        # self.input_layers = input_layers + 1	# for the bias
        # self.hidden_layers = hidden_layers
        # self.output_layers = output_layers

        """ Netactivations for each layers """
        self.net_j = np.ones(((self.nH),1))		#	Hidden layer net's
        self.net_k = np.ones((self.c,1))		#	Output layer net's

        """ Create random weight vectors """
        self.weight_ji = np.random.randn(self.nH,(self.d+1))			#	weights b/w input n hidden layer
        self.weight_kj = np.random.randn(self.c,(self.nH+1))		#	weights b/w hidden n output layer
        # self.weight_kj = np.array([[0.4,0.45,0.60],[0.5,0.55,0.60]])
        # self.weight_ji = np.array([[0.15,0.2,0.35],[0.25,0.3,0.35]])

        """ Outputs at each layer """
        self.y_j = np.ones(((self.nH+1),1))
        self.z_k = self.net_k

        """ sensitivities of each layer """
        self.del_j = np.zeros((self.nH,1))
        self.del_k = np.zeros((self.c,1))

    def FeedForward_step(self,input_vec):

        """ finding net_j and output y_j for hidden units """
        self.net_j = np.dot(self.weight_ji,input_vec)
        for j in xrange(self.nH):
            self.y_j[j] = sigmoid(self.net_j[j])
        #print "net_j : ",self.net_j
        """ finding net_k and output z_k for output units """
        self.net_k = np.dot(self.weight_kj,self.y_j)
        #print "\nnet_k : ",self.net_k
        for k in xrange(self.c):
            self.z_k[k] = sigmoid(self.net_k[k])
        #print "\ny_j : ",self.y_j
        #print "\nz_k : ",self.z_k

        return self.z_k


    def Sensitivity(self,input_x,target):

        self.z_k = self.FeedForward_step(input_x)
        """ finding the sensitivities of output layer nodes """
        # for k in xrange(c):
        # 	self.del_k[k] = (target[k] - self.z_k[k])*derivate_sigmoid(self.net_k[k])
        """ del_k = (t[k]-z[k])*f'(net_k[k]) """
        # self.del_k = np.multiply((target - self.z_k),derivate_sigmoid(self.net_k))
        for k in xrange(self.c):
            self.del_k[k] = (target[k] - self.z_k[k])*(derivate_sigmoid(self.net_k[k]))
        #print "\nderivate_sigmoid : ",derivate_sigmoid(self.net_k)
        #print "\ndel_k : ",self.del_k
        """ finding the sensitivities of hidden layer nodes """

        for j in xrange(self.nH):
            temp=0
            for k in xrange(self.c):
                temp += self.weight_kj[k][j]*self.del_k[k]
            self.del_j[j] = temp*derivate_sigmoid(self.net_j[j])

        # self.del_j = np.dot(self.weight_kj.T[:-1],self.del_k) * derivate_sigmoid(self.net_j)
        #print "\ndel_j : ",self.del_j

    def Online_Backprop(self,input_data):
        """ input data is in the form zip(input_x,target)
            input_data[i][0] is the ith input to the network
            input_data[i][1] is the ith expected value of o/p """
        n = len(input_data)
        i=0

        curr_error=10000
        prev_error=0
        threshold = 0.0000000001
        while(abs(curr_error - prev_error) > threshold):
            x=[]
            target=[]
            x = list(input_data[i][0])
            # #print "\ninput_x : ",x
            x.append(1)
            x = np.reshape(x,(self.d+1,1))				#Appending 1 for bias term

            target = np.zeros((self.c,1))
            # #print "d,nH,c : ",self.d,self.nH,self.c
            print "label : ",input_data[i][1]
            # #print target
            target[int(input_data[i][1])] = 1
            # target = np.reshape(target,(self.c,1))
            prev_error = curr_error
            #print "\ninput_x : ",x
            #print "\ntarget : ",target

            self.Sensitivity(x,target)
            """ Update weights b/w hidden layer and output layer """
            delta_w_kj = self.eta * np.dot(self.del_k,self.y_j.T)					#delta_w_kj = eta*del_k*y_j
            #print "\ndelta_w_kj : ",delta_w_kj
            self.weight_kj = np.add(self.weight_kj,delta_w_kj)
            #print "\nweight_kj : ",self.weight_kj

            """ Update weights b/w input layer and hidden layer """
            delta_w_ji = self.eta *  np.dot(self.del_j,x.T)
            #print "\ndelta_w_ji : ",delta_w_ji
            self.weight_ji = np.add(self.weight_ji,delta_w_ji)
            #print "\nweight_ji : ",self.weight_ji
            # self.weight_kj = np.add(self.weight_kj,(np.dot(del_k,y_j.T))
            # self.weight_ji = np.add(self.weight_ji,)

            """ Calculating Error in network """
            curr_error = 0.5* np.linalg.norm(target - self.z_k)**2
            print "Error : ",curr_error
            print "Error Diff : ",abs(curr_error - prev_error )
            #print "z_k: ", self.z_k
            # #print "\ninput_x : ",x
            # #print "\ntarget : ",target
            i = (i+1)%n

    def net_test(self,test_data):
    	count=0
    	n=len(test_data)

        print " NOW IN TESTING PHASE \
        length of the test data is : ",n

    	for raw_x,raw_target in test_data:
            x = list(raw_x)
            x.append(1)
            x = np.reshape(x,(self.d+1,1))
            target = np.zeros((self.c,1))
            target[int(raw_target)] = 1
            self.z_k = self.FeedForward_step(x)
            if np.argmax(self.z_k) == np.argmax(target):
    			count = count+1
        acc = (float(count)/n)*100
    	print "\ncount : ",count," \nAccuracy : ",acc," % ."


def preprocess_data(data):
    data = np.array(data)
    feature_vector=[]
    for row in xrange(0,32,4):
        for cols in xrange(0,32,4):
            # #print row,cols
            temp = [data[row+k][cols:cols+4] for k in xrange(4)]
            # #print temp
            feature_vector.append(np.count_nonzero(temp))
    return feature_vector

def read_data(input_data,labels):
    f = open('optdigits-orig.tra','r')
    entire_file = f.readlines()
    entire_file = entire_file [21:]
    # removing the header present at the start of the file which is just information about it
    i=0
    data=[]
    # #print entire_file[32].strip()
    for line in entire_file:
        if i == 0:
            if len(data) !=0:
                input_data.append(preprocess_data(data))		#append the entire image as input to list
            data=[]
        if i != 32:
            data.append(list(map(float,line.strip())))
        else:
            labels.append(int(line.strip()))
        i = (i+1)%33

    if i == 0:
        if len(data) !=0:
            input_data.append(preprocess_data(data))
    f.close()


def read_test_data(test_data,test_labels):
	pass
	f=open('optdigits.tes','rb')
	reader = csv.reader(f)

	for row in reader:
		temp = list(map(float,row))
		lbl = row[-1]
		temp.pop()
		test_data.append(temp)
		test_labels.append(lbl)



def read_preprocessed_data(input_data,labels):
    pass
    f=open('optdigits.tra','rb')
    reader = csv.reader(f)

    for row in reader:
        temp = list(map(float,row))
        lbl = row[-1]
        temp.pop()
        input_data.append(temp)
        labels.append(lbl)

    f.close()


input_data=[]
labels=[]
read_data(input_data,labels)
# read_preprocessed_data(input_data,labels)

Digit_net = DigitClassify_NeuralNetwork([64,30,10],0.5)
train_data = zip(input_data,labels)
Digit_net.Online_Backprop(train_data)

test_data=[]
test_labels=[]
read_test_data(test_data,test_labels)
Digit_net.net_test(zip(test_data,test_labels))

# #print DigitClassify_NeuralNetwork.weight_ji
# #print DigitClassify_NeuralNetwork.weight_kj
# #print input_data[0],len(input_data[0])
# #print preprocess_data(input_data[0]),labels[0]

# for line,label in zip(input_data,labels):
# 	for x in line:
# 		sys.stdout.write(str(x)+",")
# 	sys.stdout.write(str(label)+"\n")
#
