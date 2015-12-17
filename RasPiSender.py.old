##import RPi.GPIO as GPIO
##from audiolazy import *
import wave
import pyaudio

def stereo_to_mono(hex1, hex2):
	"""average two hex string samples"""
	return hex((ord(hex1) + ord(hex2))/2)

wr = wave.open('flesh_wound.wav','rb')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()

#print nframes

if nchannels == 1:
	frames = wr.readframes(wr.getnframes())
else:
	frames = 0
#for i in range(len(frames)):
#print (frames[0::],0)
# print list(frames)

new_frames = ''
print wr.getnframes()
print len(frames)
for s1 in list(frames):
	byte = ' '.join('{0:08b}'.format(ord(x), 'b') for x in s1)
	# print byte
	for i in byte:
	##Set code to access GPIO here on RasPi. Will print Byte from MSB.
		# print i
		pass
	new_frames+=((chr(int(byte,2))))
for i in range(len(list(frames))): 
	if frames[i] != new_frames[i]:
		print 'FAILED TEST'
		print ord(frames[i])
		print new_frames[i]
		print ''

ww = wave.open('mono.wav','wb')
ww.setparams((1,sampwidth,framerate,nframes,comptype,compname))

ww.writeframes(new_frames)