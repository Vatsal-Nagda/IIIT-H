from __future__ import division
import csv
import pandas as pd
import numpy as np
import math
from sklearn.model_selection import KFold
from sklearn.metrics import accuracy_score

dataframe = pd.read_csv("census-income.data")
dataframe = dataframe[['ACLSWKR', 'ADTIND', 'ADTOCC', 'AHGA', 'AHSCOL', 'AMARITL', 'AMJIND', 'AMJOCC', 'ARACE',
                        'AREORGN', 'ASEX', 'AUNMEM', 'AUNTYPE', 'AWKSTAT', 'FILESTAT', 'GRINREG', 'GRINST', 'HHDFMX',
                        'HHDREL', 'MIGMTR1', 'MIGMTR3', 'MIGMTR4', 'MIGSAME', 'MIGSUN', 'PARENT', 'PEFNTVTY',
                        'PEMNTVTY', 'PENATVTY', 'PRCITSHP', 'SEOTR', 'VETQVA', 'VETYN', 'YEAR', 'INCOME']]

categorical_attributes = ['ACLSWKR', 'ADTIND', 'ADTOCC', 'AHGA', 'AHSCOL', 'AMARITL', 'AMJIND', 'AMJOCC', 'ARACE',
                        'AREORGN', 'ASEX', 'AUNMEM', 'AUNTYPE', 'AWKSTAT', 'FILESTAT', 'GRINREG', 'GRINST', 'HHDFMX',
                        'HHDREL', 'MIGMTR1', 'MIGMTR3', 'MIGMTR4', 'MIGSAME', 'MIGSUN', 'PARENT', 'PEFNTVTY',
                        'PEMNTVTY', 'PENATVTY', 'PRCITSHP', 'SEOTR', 'VETQVA', 'VETYN', 'YEAR', 'INCOME']

data_mode = dataframe[dataframe.GRINST != '?']['GRINST'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'GRINST'] = data_mode

data_mode = dataframe[dataframe.MIGMTR3 != '?']['MIGMTR3'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'MIGMTR3'] = data_mode

data_mode = dataframe[dataframe.MIGMTR4 != '?']['MIGMTR4'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'MIGMTR4'] = data_mode

data_mode = dataframe[dataframe.MIGSAME != '?']['MIGSAME'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'MIGSAME'] = data_mode

data_mode = dataframe[dataframe.PEFNTVTY != '?']['PEFNTVTY'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'PEFNTVTY'] = data_mode

data_mode = dataframe[dataframe.PEMNTVTY != '?']['PEMNTVTY'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'PEMNTVTY'] = data_mode

data_mode = dataframe[dataframe.PENATVTY != '?']['PENATVTY'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'PENATVTY'] = data_mode

dataframe['MIGMTR1'] = str(dataframe['MIGMTR1'])

kf = KFold(n_splits=10,shuffle=True)

data = np.array(dataframe)
Accuracies = np.array([],dtype=float)

acc = 0.0
for train_index,test_index in kf.split(data):
    # print train_index,test_index

    training_Data = pd.DataFrame(data[train_index],columns=categorical_attributes)
    testing_data = pd.DataFrame(data[test_index],columns=categorical_attributes)

    class_Less = training_Data.loc[training_Data.INCOME == " - 50000." ]
    class_more = training_Data.loc[training_Data.INCOME == " 50000+."]

    tot_num_data = training_Data.shape[0]
    tot_num_Less = class_Less.shape[0]
    tot_num_More = class_more.shape[0]


    prior_prob_class_Less = math.log(tot_num_Less / tot_num_data)
    prior_prob_class_More = math.log(tot_num_More / tot_num_data)

    class_Less_Dict = {}
    class_More_Dict = {}


    for attr in categorical_attributes:
        # print attr
        class_Less_Dict[attr] = dict(class_Less[attr].value_counts() / tot_num_Less)
        class_More_Dict[attr] = dict(class_more[attr].value_counts() / tot_num_More)

    # print class_More_Dict
    # print class_Less_Dict

    #TESTING DATA
    print " Cross validation test phase "

    count=0
    for i in xrange(testing_data.shape[0]):
        tst = testing_data.iloc[i:i+1]
        # print tst
        posterior_Less = prior_prob_class_Less
        posterior_More = prior_prob_class_More

        for attr in categorical_attributes[:-1]:
            temp  = tst[attr].iloc[0]
            # print attr,temp
            if temp in class_Less_Dict[attr].keys():
                posterior_Less += math.log( class_Less_Dict[attr][temp] )
            if temp in class_More_Dict[attr].keys():
                posterior_More += math.log( class_More_Dict[attr][temp] )

        if posterior_Less > posterior_More and tst['INCOME'].iloc[0] == " - 50000.":
           count +=1
        elif posterior_More > posterior_Less and tst['INCOME'].iloc[0] == " 50000+.":
            count +=1

    acc = count/testing_data.shape[0]
    print "Accuracy : ", acc
# acc = acc/10
    Accuracies = np.append(Accuracies,acc)
    
print "Mean Accuracy: ",np.mean(Accuracies)
print "Standard Deviation: ",np.std(Accuracies)


""" TESTING PHASE """
dataframe = pd.read_csv("census-income.test")
dataframe = dataframe[['ACLSWKR', 'ADTIND', 'ADTOCC', 'AHGA', 'AHSCOL', 'AMARITL', 'AMJIND', 'AMJOCC', 'ARACE',
                        'AREORGN', 'ASEX', 'AUNMEM', 'AUNTYPE', 'AWKSTAT', 'FILESTAT', 'GRINREG', 'GRINST', 'HHDFMX',
                        'HHDREL', 'MIGMTR1', 'MIGMTR3', 'MIGMTR4', 'MIGSAME', 'MIGSUN', 'PARENT', 'PEFNTVTY',
                        'PEMNTVTY', 'PENATVTY', 'PRCITSHP', 'SEOTR', 'VETQVA', 'VETYN', 'YEAR', 'INCOME']]

data_mode = dataframe[dataframe.GRINST != '?']['GRINST'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'GRINST'] = data_mode

data_mode = dataframe[dataframe.MIGMTR3 != '?']['MIGMTR3'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'MIGMTR3'] = data_mode

data_mode = dataframe[dataframe.MIGMTR4 != '?']['MIGMTR4'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'MIGMTR4'] = data_mode

data_mode = dataframe[dataframe.MIGSAME != '?']['MIGSAME'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'MIGSAME'] = data_mode

data_mode = dataframe[dataframe.PEFNTVTY != '?']['PEFNTVTY'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'PEFNTVTY'] = data_mode

data_mode = dataframe[dataframe.PEMNTVTY != '?']['PEMNTVTY'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'PEMNTVTY'] = data_mode

data_mode = dataframe[dataframe.PENATVTY != '?']['PENATVTY'].mode().iloc[0]
dataframe.loc[dataframe.GRINST == '?', 'PENATVTY'] = data_mode

dataframe['MIGMTR1'] = str(dataframe['MIGMTR1'])

count=0
testing_data = pd.DataFrame(dataframe,columns=categorical_attributes)

print " Running on test File "
for i in xrange(testing_data.shape[0]):
    tst = testing_data.iloc[i:i+1]
    # print tst
    posterior_Less = prior_prob_class_Less
    posterior_More = prior_prob_class_More

    for attr in categorical_attributes[:-1]:
        temp  = tst[attr].iloc[0]
        # print attr,temp
        if temp in class_Less_Dict[attr].keys():
            posterior_Less += math.log( class_Less_Dict[attr][temp] )
        if temp in class_More_Dict[attr].keys():
            posterior_More += math.log( class_More_Dict[attr][temp] )

    if posterior_Less > posterior_More and tst['INCOME'].iloc[0] == " - 50000.":
       count +=1
    elif posterior_More > posterior_Less and tst['INCOME'].iloc[0] == " 50000+.":
        count +=1

acc = count/testing_data.shape[0]
print "Accuracy : ", acc