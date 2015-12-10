static const int pin_num = 5;

#define LASER_ON         PORTB |=   1<<pin_num;   // turn on LEDPIN
#define LASER_OFF        PORTB &=  ~(1<<pin_num); // turn off LEDPIN

unsigned long data1 = 0;
unsigned long data2 = 0;
byte array[512] = {0};
byte interval = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000); // Start serial
                      // setup digital pins 0-7 (makes serial work)
  DDRD = B01111110;   // digital pins 7,6,5,4,3,2,1,0
                      // sets 8-13 as input
  DDRB = B00111110;   // digital pins -,-,13,12,11,10,9,8
  LASER_OFF;          // make sure laser is turned off
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  while (i<511){
    byte x = PINB;
    PORTB = (x <<5);
    memset(array+i,x&1,1);
    //data4 = (data4<<1)+((data3&2147483648)>>31);
    //data3 = (data3<<1)+((data2&2147483648)>>31);
    //data2 = (data2<<1)+((data1&2147483648)>>31);
    //data1 = (data1<<1)+(x&1);
    //Serial.print(PINB&1);
    //eight = PINB & B1;
    //if (eight == 1){
    //  LASER_ON;
    //}
    //else{
    //  LASER_OFF;
    //}
    i++;
  }
  //LASER_OFF;
  //for(int k = 31; k>=0; k--){
  //  Serial.print((data4>>k) & 1);
  //}
  //for(int k = 31; k>=0; k--){
  //  Serial.print((data3>>k) & 1);
  //}
  //for(int k = 31; k>=0; k--){
  //  Serial.print((data2>>k) & 1);
  //}
  //for(int k = 31; k>=0; k--){
  //  Serial.print((data1>>k) & 1);
  //}
  //Serial.println();
  //LASER_OFF;
  //delay(1000);
}
