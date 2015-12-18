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
import RPi.GPIO as GPIO
import time

pin = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.IN)


wr = wave.open('flesh_wound.wav','rb')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()
bitStream = ''
i=0
sec = 2
while(i<(nframes*12)):
	if GPIO.input(pin):
		bitStream += '1'
	else:
		bitStream += '0'
	i+=1
	time.sleep(sec/100000000.0)

#print bitStream

f = open('bits.txt','w')
f.write(bitStream)
f.close()

### 
# j = '0'
# count = 0
# new_frames = ''
# bit = ''
# f = open( 'temp.txt', 'r' )
# string = f.read()
# f.close()

# for i in string:
	
# 	if (i == j):
# 		count += 1
# 	else:
# 		if (count <= 10 and count > 3):
# 			bit += str(1-int(j))
# 			count = 0
# 		else:
# 			loop = count/8
# 			for i in range(int(loop)):
# 				bit += str(1-int(j))
# 				count = 0
# 		j = str(1-int(j))
# 		count += 1
	
# 	if len(bit) == 8:
# 		new_frames += (chr(int(bit,2)))
# 		bit = ''
# 	elif len(bit) > 8:
# 		new_frames += (chr(int(bit[0:8],2)))
# 		bit = bit[8:]
# # print string
# # print list(new_frames)

# j=8
# old_frames = ''
# f = open( 'sent_bitstream.txt', 'r' )
# string = f.read()
# for i in range(len(string)):
# 	if (j - 9 < i):
# 		old_frames += (chr(int(string[i:j],2)))
# 		j+=8
# f.close()

# #print len(old_frames)

# if len(old_frames)>len(new_frames):
# 	leng = len(new_frames)
# elif len(old_frames)<len(new_frames):
# 	leng = len(old_frames)
# else:
# 	leng = len(old_frames)

# fail = False
# for i in range(leng): 
# 	if old_frames[i] != new_frames[i]:
# 		#print 'FAILED TEST'
# 		#print old_frames[i]
# 		#print new_frames[i]
# 		#print ''
# 		fail=True
# if (fail):
# 	print 'Recieved and sent bitstreams are different. Check above for error location.'
# else:
# 	print 'ALL BITS EQUAL'
# 	print 'Be happy cause it worked...'

# print len(old_frames)
# print len(new_frames)

# ww = wave.open('mono.wav','wb')
# ww.setparams((1,sampwidth,framerate,nframes,comptype,compname))

# ww.writeframes(new_frames)
###
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


