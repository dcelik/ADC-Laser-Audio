void setup() {DDRB = B00111110;} // sets 8-13 as input // digital pins -,-,13,12,11,10,9,8
void loop() {while (1){PORTB = (PINB <<5);}}
