# import serial
# import msvcrt, time

# #ser = serial.Serial('COM4', 250000)
# data = [];
# final = [];
# i = 0;
# while True:
# 	data.append("000018as78dy1hjg3kjahsfoasfi1u0x");#ser.readline())
# 	if msvcrt.kbhit():
# 		if msvcrt.getwche() == '\r':
# 			break
# 	time.sleep(0.1)

# print data

# merged = ''.join(data);
# print merged

# stripped = ''.join(_ for _ in merged if _ in "01")
# print stripped

# firstbit = stripped.lstrip("0");
# print firstbit

# for i in range(0,(8-(len(firstbit)%8))):
# 	firstbit+="0"
# print firstbit

# for i in range(8,len(firstbit)+8):
# 	if(i%8==0):
# 		final.append(int(firstbit[i-8:i],2))

# print final
# print len(data)
# print len(final)
# print "DONE"


import wave

wr = wave.open('flesh_wound.wav','rb')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()
temp = 0
j = '0'
count = 0
new_frames = ''
bit = ''
f = open( 'temp.txt', 'r' )
string = f.read()
f.close()
byte = '' 
offset = 7
for i in string:
	byte += i
	count += 1
	if count == 52:
		x = 0
		while(x < 52):
			y = x+offset
			b = byte[x:y]
			x+=7
			for z in b:
				temp+=int(z)
			if temp>=3:
				bit+='1'
				temp = 0
			elif temp<3:
				bit+='0'
				temp = 0
		new_frames += (chr(int(bit,2)))
		bit = ''
		temp = 0
		count = 0
		byte = ''

	# if (i == j):
	# 	count += 1

	# else:
	# 	if (count>=4 and count<10):
	# 		bit += j
	# 		count = 0
	# 	elif (count >= 100):
	# 		loop = count/6.5
	# 	elif(count >= 42):
	# 		loop = count/6.2
	# 	else:
	# 		loop = count/5.9
	# 	for i in range(int(loop)):
	# 		bit += j
	# 		count = 0
	# 	j = str(1-int(j))
	# 	count += 1

	
	
# print string
# print list(new_frames)

j=8
old_frames = ''
f = open( 'sent_bitstream.txt', 'r' )
string = f.read()
for i in range(len(string)):
	if (j - 9 < i):
		old_frames += (chr(int(string[i:j],2)))
		j+=8
f.close()


if len(old_frames)>len(new_frames):
	leng = len(new_frames)
elif len(old_frames)<len(new_frames):
	leng = len(old_frames)
else:
	leng = len(old_frames)

fail = False
for i in range(leng):
 	print ''.join('{0:08b}'.format(ord(old_frames[i]), 'b'))
	print ''.join('{0:08b}'.format(ord(new_frames[i]), 'b'))
	print ''
	# if old_frames[i] != new_frames[i]:
	# 	print 'FAILED TEST at '+str(i)
	# 	print ''.join('{0:08b}'.format(ord(old_frames[i]), 'b'))
	# 	print ''.join('{0:08b}'.format(ord(new_frames[i]), 'b'))
	# 	print ''
	# 	fail=True
# if (fail):
# 	print 'Recieved and sent bitstreams are different. Check above for error location.'
# else:
# 	print 'ALL BITS EQUAL'
# 	print 'Be happy cause it worked...'

print len(old_frames)
print len(new_frames)

ww = wave.open('mono.wav','wb')
ww.setparams((1,sampwidth,framerate,nframes,comptype,compname))

ww.writeframes(new_frames)

# for i in range(0,len(data)):
# 	data[i] = data[i].strip('\r\n')

# merged = ''.join(data)

# print len(merged)
# print merged
# final = [];
# for i in range(0,len(merged)):
# 	if(i%8==0):
# 		final.append(int(merged[0:8],2))

# print final

# print "".join(_ for _ in data if _ in "01")


