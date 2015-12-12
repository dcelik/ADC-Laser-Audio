static const int pin_num = 5;

#define LASER_ON         PORTD |=   1<<pin_num;   // turn on LEDPIN
#define LASER_OFF        PORTD &=  ~(1<<pin_num); // turn off LEDPIN
#define DATASIZE         1024
#define HALFDATA         512

unsigned long data1 = 0;
unsigned long data2 = 0;
byte array[DATASIZE] = {0};
byte temp = 0;
byte interval = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000); // Start serial
                      // setup digital pins 0-7 (makes serial work)
  DDRD = B01111110;   // digital pins 7,6,5,4,3,2,1,0
                      // sets 8-13 as input
  DDRB = B00110000;   // digital pins -,-,13,12,11,10,9,8
  LASER_OFF;          // make sure laser is turned off
}

void loop() {
  unsigned long curmillis = millis();
  // put your main code here, to run repeatedly:
  int i = 0;
  int j = 0;
  while (i<DATASIZE){
    byte x = PINB;
    PORTD = x<<2;
    temp = (temp<<4)+(x&B1111);
    
    x = PINB;
    PORTD = x<<2;
    temp = (temp<<4)+(x&B1111);
    
    memset(array+i,temp,1);
    i++;
  }
  //Serial.println(millis()-curmillis);
  PORTD = B0000<<2;
  for(int k = 0; k<DATASIZE; k++){
    byte t = array[k];
    Serial.print((t>>7)&1);
    Serial.print((t>>6)&1);
    Serial.print((t>>5)&1);
    Serial.print((t>>4)&1);
    Serial.print((t>>3)&1);
    Serial.print((t>>2)&1);
    Serial.print((t>>1)&1);
    Serial.print((t   )&1);
    //Serial.print(" ");
  }
  Serial.println();
  //Serial.print(millis()-curmillis);
  //LASER_OFF;
  delay(1000-(millis()-curmillis));
}
