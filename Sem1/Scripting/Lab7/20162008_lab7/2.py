import sys

from Q1 import getReportFromMarks

f_read = open(sys.argv[1],"r")
tot = getReportFromMarks(f_read)
print tot