// Sensor
#define irs 8

// Left Motor
#define LF 9 // int4
#define LB 10 // int3

// Right Motor
#define RF 11 // int2
#define RB 12 // int1



void setup() {
  // put your setup code here, to run once:
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);

  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);

  pinMode(irs, INPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 if (digitalRead(irs) == 1) {
  digitalWrite(LF,HIGH);
  digitalWrite(RF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RB,LOW);
 } else {
  digitalWrite(LB,HIGH);
  digitalWrite(RB,HIGH);
  digitalWrite(LF,LOW);
  digitalWrite(RF,LOW);
  delay(1000);
  digitalWrite(LB,HIGH);
  digitalWrite(RF,HIGH);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  delay(1000);
 }
}
