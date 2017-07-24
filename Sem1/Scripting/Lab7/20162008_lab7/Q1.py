import sys

tot=[]

def getReportFromMarks( f_read ) :
	
	f_write = open('Grades-Final.csv','w')
	line_list = f_read.readlines()
	f_write.write(line_list[0])

	#print line_list[0]
	line_list = line_list[1:]

	all_avg =0
	tot = []
	final=[]

	for line in line_list:
		total = 0;
		line = line.split(',')
		#print line
		sum_st=0
		for i in range(1,7):
			sum_st += int(line[i])
		average = round(((sum_st+0.0)/6),3)
		#sys.stdout.write(str(average)+"\n")
		all_avg += sum_st
		tot.append(sum_st)
		name = line[0];
		line1 =[]
		line1.append(name)
		line1.append(sum_st)
		line1.append(average)
		final.append(line1)
		#print line1

	all_avg = round((all_avg+0.0)/6,3)
	#print all_avg
	tot.sort()
	#print tot
	for line in final:
		#print line
		#line = line.split(' ')
		if line[1] >= all_avg:		
			if line[1] == tot[-1] or line[1] == tot[-2]:
				line.append('A')
			else:
				line.append('B')
			
		else:
			if line[1] == tot[0] or line[1] == tot[1]:
				line.append('D')
			else:
				line.append('C')
	return final


if __name__ == "__main__" :
	f_read = open(sys.argv[1],"r")
	marks =getReportFromMarks( f_read)
	#print marks
	f_write = open('Grades-Final.csv','w')
	for line in marks:
		for inp in range(len(line)-1):
			f_write.write(str(line[inp])+',')
		f_write.write(str(line[-1])+"\n")
