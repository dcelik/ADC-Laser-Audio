import serial
import msvcrt, time

#ser = serial.Serial('COM4', 250000)
data = [];
final = [];
i = 0;
while True:
	data.append("000018as78dy1hjg3kjahsfoasfi1u0x");#ser.readline())
	if msvcrt.kbhit():
		if msvcrt.getwche() == '\r':
			break
	time.sleep(0.1)

print data

merged = ''.join(data);
print merged

stripped = ''.join(_ for _ in merged if _ in "01")
print stripped

firstbit = stripped.lstrip("0");
print firstbit

for i in range(0,(8-(len(firstbit)%8))):
	firstbit+="0"
print firstbit

for i in range(8,len(firstbit)+8):
	if(i%8==0):
		final.append(int(firstbit[i-8:i],2))

print final
print len(data)
print len(final)
print "DONE"


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


