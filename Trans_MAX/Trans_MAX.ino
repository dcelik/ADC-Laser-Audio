static const int pin_num = 5;

#define LASER_ON         PORTB |=   1<<pin_num;   // turn on LEDPIN
#define LASER_OFF        PORTB &=  ~(1<<pin_num); // turn off LEDPIN

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
  int i = 1;
  byte eight = 0;
  while (i<64){
    PORTB = (PINB <<5);
    //Serial.print(PINB&1);
    //eight = PINB & B1;
    //if (eight == 1){
    //  LASER_ON;
    //}
    //else{
    //  LASER_OFF;
    //}
  }
}
