import serial

ser = serial.Serial('COM4', 250000)
data = [];
i = 0;
while i<2:
	data.append(ser.readline())
	i = i+1

for i in range(0,len(data)):
	data[i] = data[i].strip('\r\n')

merged = ''.join(data)
print len(merged)
print merged
final = [];
for i in range(0,len(merged)):
	if(i%8==0):
		final.append(int(merged[0:8],2))

print final
