import RPi.GPIO as IO
import wave

pin = 27

IO.setmode(IO.BCM)
IO.setup(pin, IO.OUT)


wr = wave.open('flesh_wound.wav','rb')

nchannels, sampwidth, framerate, nframes, comptype, compname =  wr.getparams()

if nchannels == 1:
	frames = wr.readframes(wr.getnframes())
else:
	frames = 0

byteList = []

for s1 in list(frames):
	byteList.append(' '.join('{0:08b}'.format(ord(x), 'b') for x in s1))
	# print byte
for byte in byteList:
	for i in byte:
	##Set code to access GPIO here on RasPi. Will print Byte from MSB.
		if i == '1':
			IO.output(pin, IO.HIGH)
		elif i == '0':
			IO.output(pin, IO.LOW)

IO.output(pin, IO.LOW)

IO.cleanup()