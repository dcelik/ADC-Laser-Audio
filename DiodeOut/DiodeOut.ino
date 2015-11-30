int reciever = 8;
int val;
int t;
float TotF = 0;
int Ones = 0;
float Freq;
int next;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(reciever,INPUT);
  next = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  t = millis();
  val = digitalRead(reciever);
  if (val == 0){
    Ones++;
  }
  TotF++;
  if (t == (next+1000)){
    Freq = TotF/Ones*1.0;
    TotF = 0;
    Ones = 0;
    Serial.println(Freq);
    next = millis();
  }
  //Serial.print("I recieved: ");
  //Serial.println(abs(val-1));
}
