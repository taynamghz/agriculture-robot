// Define pins for motor control
const int leftMotorPin1 = 2;  // Left motor H-bridge input 1
const int leftMotorPin2 = 3;  // Left motor H-bridge input 2
const int rightMotorPin1 = 4; // Right motor H-bridge input 1
const int rightMotorPin2 = 5; // Right motor H-bridge input 2

void setup() {
  // Set motor control pins as output
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Move forward for 1 meter
  moveForward();
  delay(10000); // Adjust this delay according to your robot's speed

  // Turn right
  turnRight();
  delay(10000); // Adjust this delay for turning duration

  // Move forward a bit
  moveForward();
  delay(2000); // Adjust this delay according to your robot's speed and distance

  // Turn right again
  turnRight();
  delay(10000); // Adjust this delay for turning duration

  // Move forward
  moveForward();
  delay(10000); // Adjust this delay according to your robot's speed

  // Turn left
  turnLeft();
  delay(10000); // Adjust this delay for turning duration

  // Move forward a bit
  moveForward();
  delay(2000); // Adjust this delay according to your robot's speed and distance

  // Turn left again
  turnLeft();
  delay(10000); // Adjust this delay for turning duration
}

// Function to move the robot forward
void moveForward() {
  // Left motors
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  // Right motors
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to turn the robot right
void turnRight() {
  // Left motors
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  // Right motors
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

// Function to turn the robot left
void turnLeft() {
  // Left motors
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);

  // Right motors
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}
