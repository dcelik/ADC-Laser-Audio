int incomingByte = 0;
int laser = 13;
int j;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laser,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
//    Serial.print("I wrote: ");
//    Serial.println(incomingByte, DEC);
    for (int i = 7; i >= 0; i--) {
      j = bitRead(incomingByte,i);
      digitalWrite(laser,j);
//      Serial.println(j);
//      incomingByte >>= 1;  // shift the bits in lotsofbits right by one bit (equivalent to dividing by 2)
    }
    digitalWrite(laser,0);
//    Serial.println("Sent");
  }
}
