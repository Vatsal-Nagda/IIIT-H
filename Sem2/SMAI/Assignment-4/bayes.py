import pandas as pd
import numpy as np

def getCount(allData, val, colNo):
    count = 0

    for line in allData:
        if line[colNo] == val:
            count += 1
    return count

def getMostFrequent(allData, colNo, noOfRows):

    uniqueVals = {}

    for i in range(noOfRows):
        currData = allData[i][colNo]

        if currData in uniqueVals:
            x = uniqueVals[currData]
            x+=1
            uniqueVals[currData] = x
        else:
            uniqueVals[currData] = 1

    maxVal = 0
    stringData = ''

    for key in uniqueVals:
        if uniqueVals[key] > maxVal:
            maxVal = uniqueVals[key]
            stringData = key
    return key

def getAverageOfColumn(allData, colNo):
    summ = 0
    count = 0

    for row in allData:
        curr = row[colNo]
        summ = summ + float(curr)
        count +=1

    return summ/count

def adjustDataType(data):

    for i in range(len(data)):
        item = data[i]

        if item.isdigit():
            data[i] = float(data[i])

def replaceData(allData, colNo, data, noOfLines):

    for i in range(noOfLines):

        if  allData[i][colNo] == ' ?' or allData[i][colNo] == '':
            allData[i][colNo] = data






#ACLSWKR [0],ADTIND[1],ADTOCC[2],AHGA[3],AHRSPAY[4],AHSCOL[5],AMARITL[6],AMJIND[7],AMJOCC[8],ARACE[9],
# AREORGN[10],ASEX[11],AUNMEM[12],CAPLOSS[13],DIVVAL[14],FEDTAX[15],FILESTAT[16],GRINREG[17],GRINST[18],HHDFMX[19],
# HHDREL[20],MARSUPWT[21],MIGMTR1[22],MIGMTR4[23],MIGSAME[24],MIGSUN[25],NOEMP[26],PARENT[27],PEARNVAL[28],
# PEFNTVTY[29],PEMNTVTY[30],PENATVTY[31],PRCITSHP[32],PTOTVAL[33],TAXINC[34],VETQVA[35],VETYN[36],WKSWORK[37]

f = open('census-income.data')
allData = []

for line in f:
    line = line[0:len(line) - 1]
    data = line.split(',')
    adjustDataType(data)
    allData.append(data)

rowLen = len(allData[0])
colLen = len(allData)
print colLen

#print getMostFrequent(allData,0,colLen)
#print getAverageOfColumn(allData,1)

numericCols = [1,2,19,30,32,33]

for i in range(rowLen):

    if i in numericCols:
        avg = getMostFrequent(allData, i, colLen)
        replaceData(allData, i, avg, colLen)
    else:
        mostfreq = getMostFrequent(allData, i, colLen)
        replaceData(allData, i, mostfreq, colLen)

# allData = np.array(allData)
# X = allData[:, 0:rowLen - 1]  # sample inputs
# Y = allData[:, rowLen - 1]  # labels
# print Y
# print len(Y)

################################################################

def get_class_conditional_probability(i,data,df,class_label):
    p_class_label = len(df[df.iloc[:,-1] == class_label])

    if data == '?':
        return 1

    p_conditional = len(df[(df[i]==data) & (df.iloc[:,-1] == class_label)])*1.0
    print "for data: ",data
    print "class_label: ",p_class_label
    print "class_conditional: ",p_conditional
    return p_conditional*p_class_label


def predict_class(test,df,class_50k_minus,class_50k_plus):
    class_cond_prob_50_plus = 0
    class_cond_prob_50_minus = 0

    for i in xrange(len(test)-1):
        class_cond_prob_50_plus = class_cond_prob_50_plus + np.log10(get_class_conditional_probability(i,test[i],df,' 50000+.'))
        class_cond_prob_50_minus = class_cond_prob_50_minus + np.log10(get_class_conditional_probability(i,test[i],df,' - 50000.'))

    class_cond_prob_50_plus += np.log10(class_50k_plus)
    class_cond_prob_50_minus += np.log10(class_50k_minus)

    if class_cond_prob_50_minus > class_cond_prob_50_plus :
        print " predicted class is - 50000.\t actual is ",test[-1]
    else:
        print " predicted class is 50000+.\t actual is ",test[-1]



df = pd.DataFrame(allData)

class_50k_plus = len(df[df.iloc[:,-1] == ' 50000+.'])
class_50k_minus =len(df[df.iloc[:,-1] == ' - 50000.'])
print 'P1:', class_50k_plus*1.0/colLen
print 'P2:', class_50k_minus*1.0/colLen


f2 = open('test_naive.csv')
test_cases=[]


for line in f2:
    line = line[0:len(line) - 1]
    data = line.split(',')
    adjustDataType(data)
    test_cases.append(data)

for test in test_cases:
    predict_class(test,df,class_50k_minus,class_50k_plus)
