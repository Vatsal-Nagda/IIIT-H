#!/usr/bin/python

f_read= open('speed.txt','r');

for lines in f_read:
	min_speed = 1000000000000000000
	max_speed = 0
	longest = 1
	sum_sp=0
	prev = int(lines[0])
	for i in lines.split():
		speed = int(i)
		speeds = int(speed)
		sum_sp+=speeds
		if speeds < min_speed:
			min_speed = speeds
		if speeds > max_speed:
			max_speed = speeds
		if speeds > prev:
			longest+=1
		prev = speeds

	average = (sum_sp+0.0)/len(lines.split())
	print 'Minimum speed - ',min_speed
	print 'Maximum speed - ',max_speed
	print 'Average speed - ',average
	print 'Longest Interval - ',longest