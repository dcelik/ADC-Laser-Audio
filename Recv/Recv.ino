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

byte intro = B00000000;
unsigned long data = 0;
byte ending = B00000000;

byte wrd = 00000000;          // byte to store our currently sampling byte
unsigned long lastmillis = 0; // last time recorded (ms)
unsigned long curmillis = 0;  // current time recorded (ms)
const int interval = 25;       // interval between sampling in milliseconds
int wrdsamples = 0;           // number of bits sampled in our byte

void setup() {
  Serial.begin(9600);// Start serial
                     // setup digital pins 0-7 (makes serial work)
  DDRD = B11111110;  // digital pins 7,6,5,4,3,2,1,0
                     // sets 8-13 as input
  DDRB = B00111110;  // digital pins -,-,13,12,11,10,9,8 
}

void loop() {

  int readval = PINB & 00000001;
  if(readval!=0){ // check if pin is 1 or 0;
    //intro = readval;
    for(int index = 47; index >=0; index--){
      curmillis = millis();
      if(curmillis - lastmillis > interval){
        lastmillis = curmillis;
        int readval = PINB & B00000001;
        if(index>39){
          intro = (intro<<1) + readval;
        }
        else if(index>7){
          data = (data << 1) + readval;
        }
        else{
          ending = (ending << 1) + readval;
        }
      }
      else{
        index ++;
        //Serial.print(curmillis - lastmillis >= interval);
      }
    }
  #ifdef DEBUG
  Serial.println();
    printbin(intro);
    printdata();
    printbin(ending);
  #endif
  //delay(interval);
  }
  
//    curmillis = millis();
//    if(curmillis - lastmillis >=interval){ // check if it has been interval milliseconds since we sampled
//      lastmillis = curmillis ;
//      int readval = PINB & 00000001;       // read values of all pins from 8-13 and only take Pin 8
//      if (intro != 0 && wrdsamples < 8){
//        intro = (intro<<1) + readval;
//        wrdsamples++;
//      }
//      else if (intro != 0 && wrdsamples < 40){
//        data = (data << 1) + readval;
//        wrdsamples++;
//      }
//      else if (intro != 0 && wrdsamples > 39 ){
//        ending = (ending << 1) + readval;
//        wrdsamples++;
//      }
//      else if(readval!=0 && intro == 0){ // check if pin is 1 or 0;
//        intro = readval;
//        wrdsamples++;
//      }
//    } 
//    if(wrdsamples == 47){
//      #ifdef DEBUG
//        Serial.println(intro,BIN);// for debugging
//        Serial.println(data,BIN);
//        Serial.println(ending,BIN);
//      #endif
//      wrdsamples = 0;
//      intro = 0;
//      data = 0;
//      ending = 0;
//   }
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


