f = open('temp.txt', 'r' )
string = f.read()
f.close()
pieces = []
tmp = ''
lval = string[0];

for i in string:
	if(i==lval):
		tmp+=lval
	else:
		lval = i
		pieces.append(tmp)
		tmp = ''
		tmp+=lval

print pieces[min(pieces, key=len)]
		
print pieces[0:8]
		
