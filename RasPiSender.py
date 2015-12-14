##import RPi.GPIO as GPIO
##from audiolazy import *
import wave

def stereo_to_mono(hex1, hex2):
	"""average two hex string samples"""
	return hex((ord(hex1) + ord(hex2))/2)

wr = wave.open('flesh_wound.wav','r')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()

ww = wave.open('flesh_wound_mono.wav','wb')
ww.setparams((1,sampwidth,framerate,nframes,comptype,compname))

frames = wr.readframes(wr.getnframes()-1)

print ww

new_frames = ''

for (s1, s2) in zip(frames[0::2],frames[1::2]):
	print ' '.join('{0:08b}'.format(ord(x), 'b') for x in s1)
	print ' '.join('{0:08b}'.format(ord(x), 'b') for x in s2)
	print ''
	new_frames += stereo_to_mono(s1,s2)[2:].zfill(2).decode('hex')


ww.writeframes((new_frames))