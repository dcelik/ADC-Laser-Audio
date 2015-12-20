f = open('file.txt', 'r' )
string = f.read()
f.close()
cleanedstr = string.lstrip("0");
#cleanedstr = cleanedstr.rstrip("0");
#printstr = cleanedstr.rstrip("0")
#print printstr
pieces = []
tmp = ''
lval = cleanedstr[0];

for i in cleanedstr:
	if(i==lval):
		tmp+=lval
	else:
		lval = i
		pieces.append(tmp)
		tmp = ''
		tmp+=lval

onelen = len(pieces[0])+(len(pieces[0])/2)
zerolen = len(pieces[1])
# 	10101010 01110011 01101111 01110011 10101010	
				
#print onelen, zerolen
#print len(pieces)

final = [];

#print pieces
for i in pieces:
	if(i[0]=='1'):
		final.append(len(i)*1.0/onelen)
	else:
		final.append(len(i)*1.0/zerolen)

final.append(1) #final zero

final = [round(x) for x in final]

val = '1';
count = 0;

fstr = '';
for bit in final:
	for z in range(0,int(bit)):
		fstr+=val
		count+=1;
		if(count%8==0):
			pass#fstr+=' '
	if(val=='1'):
		val = '0';
	elif(val=='0'):
		val = '1';

#print 'Theoretical : 10101010 01110011 01101111 01110011 10101010'
print 'Theoretical : 1010101001110011011011110111001110101010'
print 'Actual      : ' + fstr

import binascii

n = int(fstr, 2)
res = binascii.unhexlify('%x' % n)
print res;

#print final;
		
