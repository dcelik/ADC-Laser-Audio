##import RPi.GPIO as GPIO
##from audiolazy import *
import wave

def stereo_to_mono(hex1, hex2):
    """average two hex string samples"""
    return hex((ord(hex1) + ord(hex2))/2)

wr = wave.open('piano2.wav','r')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()

ww = wave.open('piano_mono.wav','wb')
ww.setparams((1,sampwidth,framerate,nframes,comptype,compname))

frames = wr.readframes(wr.getnframes()-1)

new_frames = ''

for (s1, s2) in zip(frames[0::2],frames[1::2]):
    new_frames += stereo_to_mono(s1,s2)[2:].zfill(2).decode('hex')

ww.writeframes(bytes(new_frames))