// Sensor
#define irs1 A6
#define irs2 A7

// Left Motor
#define LF 9
#define LB 10

// Right Motor
#define RF 11
#define RB 12

// Global Variables
float irs1_value = 0;
float irs2_value = 0;
bool start = true;


void setup() {
  // Mode Set-up
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);

  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);

  pinMode(irs1, INPUT);
  pinMode(irs2, INPUT);
}

void loop() {
  circle_left_cycle();
}

// Measurements

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

// Patterns: Circle Left
void circle_left_cycle() {
  if (!on_black()) {
    move_backward(10,1); // fine tune
    rotate_left(10,1); // fine tune
  } else if (start) {
    circle_start_left();
    start = false;
  } else {
    circle_left();
  }
}

// Initiates pattern movement
void circle_start_left() {
  move_forward(1250,1); // fine tune
  rotate_right(250,1); // fine tune
}

void circle_left() {
  move_forward(10,1); // fine tune
  rotate_left(10,1); // fine tune
}

// Additional Method 
void rotate_random(float min_duration, float max_duration, float cutoff) { 
  // This method always turns right by convention
  // Measure times for max and min degree turn to set as min & max values accurately
  float duration = random(min_duration, max_duration);
  // Start rotation
  digitalWrite(LF,HIGH);
  digitalWrite(RF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RB,HIGH);
  delayMicroseconds(duration);
  // Stop Rotation
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  // Cutoff
  delayMicroseconds(cutoff);
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