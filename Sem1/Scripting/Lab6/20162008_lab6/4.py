#!/usr/bin/python
import sys

f_read= open('speed.txt','r');
min_speed = 1000000000000000000
max_speed = 0
longest = 1
max_long=1
sum_sp=0
length=0
prev =0
for lines in f_read:
	for i in lines.split():
		length+=1
		speed = int(i)
		speeds = int(speed)
		sum_sp+=speeds
		if speeds < min_speed:
			min_speed = speeds
		if speeds > max_speed:
			max_speed = speeds
		if speeds > prev:
			longest+=1
		#	sys.stdout.write(' prev '+str(prev)+' curr '+str(speeds))
			if longest > max_long:
				max_long=longest
			#	sys.stdout.write(str(speeds)+" "+str(max_long)+" ")
		else:
			longest=1
		prev = speeds

average = (sum_sp+0.0)/length
print 'Minimum speed - ',min_speed
print 'Maximum speed - ',max_speed
print 'Average speed - ',average
print 'Longest Interval - ',max_long