#import RPi.GPIO as IO
import wave
import fastgpio
#import cinpy

pin = 27

#IO.setmode(IO.BCM)
#IO.setup(pin, IO.OUT)


wr = wave.open('flesh_wound.wav','rb')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()

if nchannels == 1:
	frames = wr.readframes(wr.getnframes())
else:
	frames = 0

byteList = []
msg = 'sos'
# i = 0
longByte = ''

for s1 in msg: #list(frames)
	longByte += ''.join('{0:08b}'.format(ord(x), 'b') for x in s1)
	# i += 1

	# if (i%128 == 0):
	# 	byteList.append(longByte)
	# 	longByte = ''
	# print byte
if(longByte!=''):
	byteList.append(longByte)
	longByte = ''
# print byteList

f = open( 'sent_bitstream.txt', 'w' )
f.write(byteList[0])
f.close()

print len(byteList);

test=['10101010']
send = [test[0]+byteList[0]+test[0]]
fastgpio.send(send)

#for byte in byteList:
#	for i in byte:
#	##Set code to access GPIO here on RasPi. Will print Byte from MSB.
#		if i == '1':
#			IO.output(pin, IO.HIGH)
#		elif i == '0':
#			IO.output(pin, IO.LOW)

#IO.output(pin, IO.LOW)

#IO.cleanup()
