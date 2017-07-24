from __future__ import division
import csv
import math
from sklearn.model_selection import KFold
from sklearn.metrics import accuracy_score
import pandas as pd
import numpy as np

def HandleMissingValues(dataframe):
	dataModeValue = dataframe[dataframe.MIGMTR4 != '?']['MIGMTR4'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'MIGMTR4'] = dataModeValue
	dataModeValue = dataframe[dataframe.PEMNTVTY != '?']['PEMNTVTY'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'PEMNTVTY'] = dataModeValue
	dataModeValue = dataframe[dataframe.GRINST != '?']['GRINST'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'GRINST'] = dataModeValue
	dataModeValue = dataframe[dataframe.PEFNTVTY != '?']['PEFNTVTY'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'PEFNTVTY'] = dataModeValue
	dataModeValue = dataframe[dataframe.PENATVTY != '?']['PENATVTY'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'PENATVTY'] = dataModeValue
	dataModeValue = dataframe[dataframe.MIGMTR3 != '?']['MIGMTR3'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'MIGMTR3'] = dataModeValue
	dataModeValue = dataframe[dataframe.MIGSAME != '?']['MIGSAME'].mode().iloc[0]
	dataframe.loc[dataframe.GRINST == '?', 'MIGSAME'] = dataModeValue
	dataframe['MIGMTR1'] = str(dataframe['MIGMTR1'])

	return dataframe,dataModeValue


def TestingCrossValidation(test_dataset,prior_class1,prior_class2,categorical_fields,class1_Dict,class2_Dict,Accuracy_array):
	total_count=0
	for i in xrange(test_dataset.shape[0]):
		test1 = test_dataset.iloc[i:i+1]
		posterior1 = prior_class1
		posterior2 = prior_class2
		for attribute in categorical_fields[:-1]:
			temp1  = test1[attribute].iloc[0]
	        # print attribute,temp
	        if temp1 in class1_Dict[attribute].keys():
	            posterior1 += math.log( class1_Dict[attribute][temp1] )
	        if temp1 in class2_Dict[attribute].keys():
	            posterior2 += math.log( class2_Dict[attribute][temp1] )
		if posterior1 > posterior2 and test1['INCOME'].iloc[0] == " - 50000.":
			total_count +=1
		elif posterior2 > posterior1 and test1['INCOME'].iloc[0] == " 50000+.":
			total_count +=1
	
	accuracy = total_count/test_dataset.shape[0]
	print "Accuracy : ", accuracy
	# acc = acc/10
	Accuracy_array = np.append(Accuracy_array,accuracy)
	return Accuracy_array



def CrossValidation(dataframe,dataModeValue,categorical_fields):
	kf = KFold(n_splits=10,shuffle=True)

	dataset = np.array(dataframe)
	Accuracy_array = np.array([],dtype=float)

	accuracy = 0.0

	for traindata_index,testdata_index in kf.split(dataset):

  		test_dataset = pd.DataFrame(dataset[testdata_index],columns=categorical_fields)
  		train_Dataset = pd.DataFrame(dataset[traindata_index],columns=categorical_fields)
  		class1 = train_Dataset.loc[train_Dataset.INCOME == " - 50000." ]
  		class2 = train_Dataset.loc[train_Dataset.INCOME == " 50000+."]
  		total_data = train_Dataset.shape[0]
  		total_class2 = class2.shape[0]
  		total_class1 = class1.shape[0]
  		prior_class1 = math.log(total_class1 / total_data)
  		prior_class2 = math.log(total_class2 / total_data)
  		class2_Dict = {}
  		class1_Dict = {}
  		for attribute in categorical_fields:
  			class1_Dict[attribute] = dict(class1[attribute].value_counts() / total_class1)
  			class2_Dict[attribute] = dict(class2[attribute].value_counts() / total_class2)

	    # print class1_Dict
	    # print class2_Dict

	    #TESTING DATASET
		print " Cross validation test phase "
		Accuracy_array=TestingCrossValidation(test_dataset,prior_class1,prior_class2,categorical_fields,class1_Dict,class2_Dict,Accuracy_array)

	print "Mean Accuracy: ",np.mean(Accuracy_array)
	print "Standard Deviation: ",np.std(Accuracy_array)
	return prior_class1,prior_class2,class1_Dict,class2_Dict


def Testing_Phase(categorical_fields):
	dataframe = pd.read_csv("census-income.test")
	dataframe = dataframe[['ACLSWKR', 'ADTIND', 'ADTOCC', 'AHGA', 'AHSCOL', 'AMARITL', 'AMJIND', 'AMJOCC', 'ARACE',
	                        'AREORGN', 'ASEX', 'AUNMEM', 'AUNTYPE', 'AWKSTAT', 'FILESTAT', 'GRINREG', 'GRINST', 'HHDFMX',
	                        'HHDREL', 'MIGMTR1', 'MIGMTR3', 'MIGMTR4', 'MIGSAME', 'MIGSUN', 'PARENT', 'PEFNTVTY',
	                        'PEMNTVTY', 'PENATVTY', 'PRCITSHP', 'SEOTR', 'VETQVA', 'VETYN', 'YEAR', 'INCOME']]

	dataframe,dataModeValue=HandleMissingValues(dataframe)
	totalcount=0
	test_dataset = pd.DataFrame(dataframe,columns=categorical_fields)

	print " Running on test File "
	for i in xrange(test_dataset.shape[0]):
	    test1 = test_dataset.iloc[i:i+1]
	    # print tst
	    posterior1 = prior_class1
	    posterior2 = prior_class2

	    for attribute in categorical_fields[:-1]:
	        temp  = test1[attribute].iloc[0]
	        # print attr,temp
	        if temp1 in class1_Dict[attribute].keys():
	            posterior1 += math.log( class1_Dict[attribute][temp1] )
	        if temp1 in class2_Dict[attribute].keys():
	            posterior2 += math.log( class2_Dict[attribute][temp1] )

	    if posterior1 > posterior2 and test1['INCOME'].iloc[0] == " - 50000.":
	       totalcount +=1
	    elif posterior2 > posterior1 and test1['INCOME'].iloc[0] == " 50000+.":
	        totalcount +=1

	accuracy = totalcount/test_dataset.shape[0]
	print "Accuracy : ", Accuracy




if __name__ == '__main__':
	dataframe = pd.read_csv("census-income.data")
	categorical_fields = ['ACLSWKR', 'ADTIND', 'ADTOCC', 'AHGA', 'AHSCOL', 'AMARITL', 'AMJIND', 'AMJOCC', 'ARACE',
	                        'AREORGN', 'ASEX', 'AUNMEM', 'AUNTYPE', 'AWKSTAT', 'FILESTAT', 'GRINREG', 'GRINST', 'HHDFMX',
	                        'HHDREL', 'MIGMTR1', 'MIGMTR3', 'MIGMTR4', 'MIGSAME', 'MIGSUN', 'PARENT', 'PEFNTVTY',
	                        'PEMNTVTY', 'PENATVTY', 'PRCITSHP', 'SEOTR', 'VETQVA', 'VETYN', 'YEAR', 'INCOME']

	dataframe = dataframe[['ACLSWKR', 'ADTIND', 'ADTOCC', 'AHGA', 'AHSCOL', 'AMARITL', 'AMJIND', 'AMJOCC', 'ARACE',
	                        'AREORGN', 'ASEX', 'AUNMEM', 'AUNTYPE', 'AWKSTAT', 'FILESTAT', 'GRINREG', 'GRINST', 'HHDFMX',
	                        'HHDREL', 'MIGMTR1', 'MIGMTR3', 'MIGMTR4', 'MIGSAME', 'MIGSUN', 'PARENT', 'PEFNTVTY',
	                        'PEMNTVTY', 'PENATVTY', 'PRCITSHP', 'SEOTR', 'VETQVA', 'VETYN', 'YEAR', 'INCOME']]


	#Handled Missing Values
	dataframe,dataModeValue=HandleMissingValues(dataframe)

	prior_class1,prior_class2,class1_Dict,class2_Dict=CrossValidation(dataframe,dataModeValue,categorical_fields)



	""" TESTING PHASE """

	Testing_Phase(categorical_fields)

