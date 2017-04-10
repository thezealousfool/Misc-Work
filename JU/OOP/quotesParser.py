oldFileName = 'quotes.txt'
newFileName = 'Quotes.txt'
oldFile = open(oldFileName, 'r')
newFile = open(newFileName, 'w')
lines = [line for line in oldFile]
chunks = [lines[x:x+3] for x in xrange(0, len(lines), 3)]
for chunk in chunks:
	newFile.write(chunk[1][:-1] + " -- " + chunk[2])
