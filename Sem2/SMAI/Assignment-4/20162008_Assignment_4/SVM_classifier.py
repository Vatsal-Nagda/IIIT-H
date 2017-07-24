from __future__ import division
import csv
import numpy as np
from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import train_test_split

def read_data(input_data,labels):
	pass
	f = open('Data_SVM.csv','rb')
	reader = csv.reader(f)
	for row in reader:
		try:
			temp = list(map(float,row))
		except ValueError:
			pass
		else:
			input_data.append(temp[:-1])
			labels.append(temp[-1])

def class_separate(input_data,c1,c2,labels):
	for i in xrange(len(input_data)):
		if labels[i] == 1:
			c1.append(input_data[i])
		else:
			c2.append(input_data[i])

input_data=[]
labels=[]
read_data(input_data,labels)
c1=[]
c2=[]
class_separate(input_data,c1,c2,labels)
train_data,test_data,train_label,test_label = train_test_split(input_data,labels,test_size=0.15,random_state=0)

# parameters = { 'C' :[1,10,100,1000,10000],'degree':[3,5,7,11]}

max_c,max_d,max_acc = 0,0,0.0
for c in [2**i for i in xrange(-5,15,2)]:
    for d in xrange(1,4):
        acc = 0.0
        md = 0.0
        clf = SVC(kernel='poly',C=c,degree=d)
        for i in xrange(30):
            scores=cross_val_score(clf,train_data,train_label,cv=10)
            # print scores.mean()
            acc += scores.mean()
            md += scores.std()
        print "C : %f \tdegree : %f\t Accuracy : %f\t Deviation : %f " %(c,d,(acc+0.0)/30,(md+0.0)/30)
        if ((acc+0.0)/30) >= max_acc:
            max_acc = ((acc+0.0)/30)
            max_c=c
            max_d=d

print "Max accuracy is at ",max_c,max_d
svc = SVC(kernel='poly',C=max_c,degree=max_d).fit(train_data,train_label)

h = .02  # step size in the mesh
# create a mesh to plot in
x_min, x_max = np.array(train_data).min(axis=0)[0] - 1, np.array(train_data).max(axis=0)[0] + 1
y_min, y_max = np.array(train_data).min(axis=0)[1] - 1, np.array(train_data).max(axis=0)[1] + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),np.arange(y_min, y_max, h))

plt.subplots_adjust(wspace=0.4, hspace=0.4)
Z = svc.predict(np.c_[xx.ravel(), yy.ravel()])

# Put the result into a color plot
Z = Z.reshape(xx.shape)
plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm, alpha=0.8)

plt.xlim(xx.min(), xx.max())
plt.ylim(yy.min(), yy.max())
plt.xticks(())
plt.yticks(())


plt.scatter([x[0] for x in c1],[y[1] for y in c1],color='r')
plt.scatter([x[0] for x in c2],[y[1] for y in c2],color='b')
plt.show()


""" GAUSSIAN SVM """

Gamma = [2**i for i in xrange(-15,3,2)]

max_c,max_g,max_acc = 0,0,0.0

for c in [2**i for i in xrange(-5,15,2)]:
    for g in Gamma:
        acc = 0.0
        md = 0.0
        clf = SVC(kernel='rbf',C=c,gamma=g)
        for i in xrange(30):
            scores=cross_val_score(clf,train_data,train_label,cv=10)
            # print scores.mean()
            acc += scores.mean()
            md += scores.std()
        print "C : %f \tgamma : %f\t Accuracy : %f\t Deviation : %f" %(c,g,(acc+0.0)/30,(md+0.0)/30)
        if ((acc+0.0)/30) >= max_acc:
            max_acc = ((acc+0.0)/30)
            max_c=c
            max_g=g

print "Max accuracy is at ",max_c,max_g
svc = SVC(kernel='rbf',C=max_c,gamma=max_g).fit(train_data,train_label)

h = .02  # step size in the mesh
# create a mesh to plot in
x_min, x_max = np.array(train_data).min(axis=0)[0] - 1, np.array(train_data).max(axis=0)[0] + 1
y_min, y_max = np.array(train_data).min(axis=0)[1] - 1, np.array(train_data).max(axis=0)[1] + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),np.arange(y_min, y_max, h))

plt.subplots_adjust(wspace=0.4, hspace=0.4)
Z = svc.predict(np.c_[xx.ravel(), yy.ravel()])

# Put the result into a color plot
Z = Z.reshape(xx.shape)
plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm, alpha=0.8)

plt.xlim(xx.min(), xx.max())
plt.ylim(yy.min(), yy.max())
plt.xticks(())
plt.yticks(())


plt.scatter([x[0] for x in c1],[y[1] for y in c1],color='r')
plt.scatter([x[0] for x in c2],[y[1] for y in c2],color='b')
plt.show()

