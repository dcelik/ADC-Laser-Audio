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
// Revision: 12052015
// ---------------------------------------------------------------------------

#define DEBUG;                                 // Turns on print statements that are useful for debugging
// Comment out if you want least verbose code

static const int pin_num = 5;                  // Equal to (desired pin number)-8 for 13->8 inputs
// Equal to desired pin number for 7->0 inputs

#define LASER_ON         PORTB |=   1<<pin_num;   // turn on LEDPIN
#define LASER_OFF        PORTB &=  ~(1<<pin_num); // turn off LEDPIN

static const int packetsize = 10;

byte sentbytes[packetsize]  = {0};      // Initialize and zero array
byte curbyte                = 00000000; // Byte to store current sending byte
unsigned long lastmillis    = 0;        // last time recorded (ms)
unsigned long curmillis     = 0;        // current time recorded (ms)
int readingindex            = 0;        // index for reading from serial
int sendingindex            = 0;        // index for knowing which byte we are sending
int byteindex               = 0;        // index for knowing where in the byte we are
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
  if(readingindex == sendingindex){
    memset(sentbytes, 0, sizeof sentbytes); // Sets mem of sentbytes to 0 on reset
    readingindex = 0; 
    sendingindex = 0; 
  }
  
  if (readingindex < 10 && Serial.available() > 0) { // index first to reduce computation calls
    sentbytes[readingindex] = Serial.read();     // add the bytes we need to send
    readingindex++;
#ifdef DEBUG
    Serial.print("I wrote: ");
    Serial.println(sentbytes[readingindex - 1], BIN);
#endif
  }

  curmillis = millis();
  if (readingindex == 10 && sendingindex != 10 && curmillis - lastmillis >= interval) { // check if it has been interval milliseconds since we sampled
    lastmillis = curmillis;
    if (byteindex == 0) {               // check if we have finished sending our current byte (or we haven't sent any yet);
      #ifdef DEBUG
        Serial.println();
      #endif
      byteindex = 8;                    // reset index, MSB first to make reconstructing easier
      //readingindex = 10;
      curbyte = sentbytes[sendingindex];// set our new byte to send
      //      Serial.println(curbyte);
//      sendingindex++;
    }
    //    while (byteindex != 0){
    byteindex--;
    int temp = (curbyte >> byteindex) & 1; // get the bit we want to send
    #ifdef DEBUG
      Serial.print(temp);
    #endif
    if (temp == 1) {
      LASER_ON;
    }
    else {
      LASER_OFF;
    }
    if (byteindex == 0){
      sendingindex++;
    }
    //    }
//    #ifdef DEBUG
//      Serial.println();
//      Serial.println(curbyte, BIN);
//    #endif
  }
}
