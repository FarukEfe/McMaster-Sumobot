// Sensor
#define irs 8

// Left Motor
#define LF 9
#define LB 10

// Right Motor
#define RF 11
#define RB 12

// Global variables for lifecycle
bool start = true;

void setup() {
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(irs, INPUT);
}

void loop() {
  if (digitalRead(irs) == 1) {
    // Higher voltage on the right motor circles left. And vice versa
    if (!start) {
      move_circle(3.0, 4.0); // fine tuning
    } else {
      circle_start_left();
      start = false;
    }
  } else {
    move_backward(1000,250);
    rotate_left(200,250);
    start = true;
  }
}

// Circle Pattern

void circle_start_left() {
  // This code is called only at the start of the pattern or after rotation
  move_forward(1000,250); // fine tuning
  rotate_right(200,250); // fine tuning (for 90 degrees)
}

void move_circle(float leftSpeed, float rightSpeed) {
  analogWrite(LF, leftSpeed);
  analogWrite(RF, rightSpeed);
  analogWrite(LB, LOW);
  analogWrite(RB, LOW);
}

// Bot essentials

void stop_motors() {
  digitalWrite(LF, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(LB, HIGH);
  digitalWrite(RB, HIGH);
}

void move_forward(float duration, float cutoff) {
  digitalWrite(LF,HIGH);
  digitalWrite(RF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RB,LOW);
  delay(duration);
  stop_motors();
  delay(cutoff);
}

void move_backward(float duration, float cutoff) {
  digitalWrite(LF,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(LB,HIGH);
  digitalWrite(RB,HIGH);
  delay(duration);
  stop_motors();
  delay(cutoff);
}

void rotate_right(float duration, float cutoff) {
  digitalWrite(LF,HIGH);
  digitalWrite(RF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RB,HIGH);
  delay(duration);
  stop_motors();
  delay(cutoff);
}

void rotate_left(float duration, float cutoff) {
  digitalWrite(RF,HIGH);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LB,HIGH);
  delay(duration);
  stop_motors();
  delay(cutoff);
}
