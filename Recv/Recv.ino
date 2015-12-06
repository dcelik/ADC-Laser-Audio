// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Recv.ino
// Arduino code for recieving data sent as pulse bit across digital pins. 
// Designed to work with a pulsing laser. Uses a constant delay in order to 
// keep timing across the transmitter and the receiver equal. Implements port 
// and bit manipulation in order to reduce computational and temporal costs.
//
// Author: Deniz Celik, Jacob Riedel
// Revision: 12042015
// ---------------------------------------------------------------------------

#define DEBUG;               // Turns on print statements that are useful for debugging
                             // Comment out if you want least verbose code

byte wrd = 00000000;          // byte to store our currently sampling byte
unsigned long lastmillis = 0; // last time recorded (ms)
unsigned long curmillis = 0;  // current time recorded (ms)
const int interval = 5;       // interval between sampling in milliseconds
int wrdsamples = 0;           // number of bits sampled in our byte

void setup() {
  Serial.begin(9600);// Start serial
                     // setup digital pins 0-7 (makes serial work)
  DDRD = B11111110;  // digital pins 7,6,5,4,3,2,1,0
                     // sets 8-13 as input
  DDRB = B00111110;  // digital pins -,-,13,12,11,10,9,8 
}

void loop() {
  curmillis = millis();
  if(curmillis - lastmillis >=interval){ // check if it has been interval milliseconds since we sampled
    lastmillis = curmillis ;
    int readval = PINB & 00000001;       // read values of all pins from 8-13 and only take Pin 8
    if(readval!=0){                      // check if pin is 1 or 0;
      if(wrdsamples==8){
        #ifdef DEBUG
          Serial.println(wrdsamples,BIN);// for debugging
        #endif
        wrdsamples = 0;
      }
      else{                      // This assumes that the bytes are sent from most to least significant bit.
        wrd += (PINB & 00000001);// grab value of pin 8
        wrd<<=1;                 
        wrdsamples+1;            // shift value over by 1
      }
    }
    else{
      wrd<<=1;
    }
  }
}

