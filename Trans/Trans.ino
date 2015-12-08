// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Trans.ino
// Arduino code for transmitting data across digital pins. Designed to work
// with a pulsing laser. Uses a constant delay in order to keep timing across
// the transmitter and the receiver equal. Implements port and bit
// manipulation in order to reduce computational and temporal costs.
//
// Author: Deniz Celik, Jacob Riedel
// Revision: 12082015
// ---------------------------------------------------------------------------

#define DEBUG;                                 // Turns on print statements that are useful for debugging
// Comment out if you want least verbose code

static const int pin_num = 5;                  // Equal to (desired pin number)-8 for 13->8 inputs
// Equal to desired pin number for 7->0 inputs

#define LASER_ON         PORTB |=   1<<pin_num;   // turn on LEDPIN
#define LASER_OFF        PORTB &=  ~(1<<pin_num); // turn off LEDPIN

byte preamble               = B10101011;
unsigned long data          = 0;
byte ending                 = B00000001;

unsigned long lastmillis    = 0;        // last time recorded (ms)
unsigned long curmillis     = 0;        // current time recorded (ms)
const int interval          = 50;       // interval between sending in milliseconds

void setup() {
  Serial.begin(9600); // Start serial
                      // setup digital pins 0-7 (makes serial work)
  DDRD = B11111110;   // digital pins 7,6,5,4,3,2,1,0
                      // sets 8-13 as input
  DDRB = B00111111;   // digital pins -,-,13,12,11,10,9,8
  LASER_OFF;          // make sure laser is turned off
}

void loop() {
  
  for(int i = 0; i < 4; i++){
    if(Serial.available()>0){ 
      byte temp = Serial.read();
      //Serial.println(temp, BIN);
      for(int j = 7; j >= 0; j--){
         data <<= 1;
         data = (data+((temp>>j) & 1));
      }
    }
    else{
      i--;
    }
  }
  #ifdef DEBUG
    printbin(preamble);
    printdata();
    printbin(ending);
  #endif

  for( int index = 47; index >=0; index--){
    curmillis = millis();
    if(curmillis - lastmillis >= interval){
      lastmillis = curmillis;
      if(index>39){
        if(((preamble>>(index-40)) & 1) == 1){
          LASER_ON;
        }
        else{
          LASER_OFF;
        }
      }
      else if(index>7){
        if(((data>>(index-8)) & 1) == 1){
          LASER_ON;
        }
        else{
          LASER_OFF;
        }
      }
      else{
        if(((ending>>index) & 1) == 1){
          LASER_ON;
        }
        else{
          LASER_OFF;
        }
      }
    }
    else{
      index++;
    }
  }
  delay(interval);
  LASER_OFF;
}

void printbin(byte b){
  Serial.print((b>>7) & 1);
  Serial.print((b>>6) & 1);
  Serial.print((b>>5) & 1);
  Serial.print((b>>4) & 1);
  Serial.print((b>>3) & 1);
  Serial.print((b>>2) & 1);
  Serial.print((b>>1) & 1);
  Serial.print((b>>0) & 1);
  Serial.println();
}

void printdata(){
  for(int k = 31; k>=0; k--){
    Serial.print((data>>k) & 1);
  }
  Serial.println();
}
