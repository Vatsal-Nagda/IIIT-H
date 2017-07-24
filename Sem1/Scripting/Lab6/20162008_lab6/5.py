import sys
import math

inp = sys.argv[1]
key = sys.argv[2]

count = math.ceil(len(inp)+0.0/len(key));
count = int(count)
key = key*count

final=""
for c in range(len(inp)):
	final+=chr((ord(inp[c])+ord(key[c]) -65 -65)%26 +65)

print final