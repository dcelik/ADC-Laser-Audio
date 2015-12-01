byte wrd = 00000000;

void setup() {
  //setup digital pins 0-7 (makes serial work)
  Serial.begin(9600);
  DDRD = B11111110; // digital pins 7,6,5,4,3,2,1,0
  //sets 8-13 as input
  DDRB = B00111110; // digital pins -,-,13,12,11,10,9,8 
}

void loop() {
  // put your main code here, to run repeatedly:
  int readval = PINB & 00000001;
  if(readval!=0){
    Serial.println(PINB,BIN);
    wrd = 00000010;
    wrd += (PINB & 00000001);
    wrd<<=1;
    wrd += (PINB & 00000001);
    wrd<<=1;
    wrd += (PINB & 00000001);
    wrd<<=1;
    wrd += (PINB & 00000001);
    wrd<<=1;
    wrd += (PINB & 00000001);
    wrd<<=1;
    wrd += (PINB & 00000001);
    wrd<<=1;
    wrd += (PINB & 00000001);
    Serial.println(wrd,BIN);
  }
}

