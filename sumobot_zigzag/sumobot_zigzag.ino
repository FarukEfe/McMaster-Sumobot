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
  zig_zag_cycle();
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

// Patterns: Zig-zag
void zig_zag_cycle() {
  if (!on_black()) {
    rotate_random(250,1000, 5); // Adjust min max numbers off of measurement
  } else {
    move_forward(10,1); // Low duration for more frequent sensor check
  }
}

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
