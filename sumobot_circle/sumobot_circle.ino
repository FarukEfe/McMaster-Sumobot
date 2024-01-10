// Sensor
#define irs1 A6
#define irs2 A7

// Left Motor
#define LF 9
#define LB 10

// Right Motor
#define RF 11
#define RB 12

// Global variables for lifecycle
float irs1_value = 0;
float irs2_value = 0;
float IRVoltage = 0.0;
bool start = true;

void setup() {
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(irs1, INPUT);
  pinMode(irs2, INPUT);
}

void loop() {
  if (!start) {
    // Higher voltage on the right motor circles left. And vice versa
    move_circle(3.0, 4.0); // fine tuning
  } else {
    circle_start_left();
  }
}

// Measurement

bool on_black() {
  // IRSensor.read()
  digitalWrite(irs1, HIGH);
  digitalWrite(irs2, HIGH);
  delayMicroseconds(10);
  digitalWrite(irs1, LOW);
  digitalWrite(irs2, LOW);
  delayMicroseconds(10);
  // If voltage is below threshold value, then return true, else false
  irs1_value = pulseIn(irs1, HIGH);
  irs2_value = pulseIn(irs2, HIGH);

  if (irs1_value < 80 && irs2_value < 80) {
    return true;
  } else {
    return false;
  }
}

// Circle Pattern

void circle_start_left() {
  // This code is called only at the start of the pattern or after rotation
  move_forward(1250,1); // fine tuning
  rotate_right(250,1); // fine tuning (for 90 degrees)
}

void circle_start_right() {
  // This code is called only at the start of the pattern or after rotation
  move_forward(1250,1); // fine tuning
  rotate_left(250,1); // fine tuning (for polygon)
}

void move_circle(float leftSpeed, float rightSpeed) {
  analogWrite(LF, leftSpeed);
  analogWrite(RF, rightSpeed);
  analogWrite(LB, 0);
  analogWrite(RB, 0);

  while (on_black()) {
    delayMicroseconds(10);
  }

  delayMicroseconds(10);

  if (leftSpeed > rightSpeed) {
    rotate_right(10,1); // fine tuning
  } else {
    rotate_left(10,1); // fine tuning
  }

  start = true;

}

// Bot essentials

void move_forward(float duration, float cutoff) {
  digitalWrite(LF,HIGH);
  digitalWrite(RF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RB,LOW);
  delayMicroseconds(duration);
  digitalWrite(LF,LOW);
  digitalWrite(RF,LOW);
  delayMicroseconds(cutoff);
}

void move_backward(float duration, float cutoff) {
  digitalWrite(LF,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(LB,HIGH);
  digitalWrite(RB,HIGH);
  delayMicroseconds(duration);
  digitalWrite(LB,LOW);
  digitalWrite(RB,LOW);
  delayMicroseconds(cutoff);
}

void rotate_right(float duration, float cutoff) {
  digitalWrite(LF,HIGH);
  digitalWrite(RF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RB,HIGH);
  delayMicroseconds(duration);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  delayMicroseconds(cutoff);
}

void rotate_left(float duration, float cutoff) {
  digitalWrite(RF,HIGH);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LB,HIGH);
  delayMicroseconds(duration);
  digitalWrite(RF,LOW);
  digitalWrite(LB,LOW);
}
