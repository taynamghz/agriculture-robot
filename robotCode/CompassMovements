#include <QMC5883LCompass.h>
#include <HCSR04.h>

QMC5883LCompass compass;
HCSR04 hc(7, 8); //initialisation class HCSR04 (trig pin , echo pin)


const int IN1 = 2; // Forward control for motors on OUT1/OUT2
const int IN2 = 3; // Forward control for motors on OUT1/OUT2
const int IN3 = 4; // Forward control for motors on OUT3/OUT4
const int IN4 = 5; // Forward control for motors on OUT3/OUT4

float wheelDiameter = 0.122; // Diameter in meters
float wheelCircumference = PI * wheelDiameter; // Circumference in meters
float rpm = 20; // Example RPM value
unsigned long startTime;
int threshold = 35; // Threshold for obstacle detection
bool top = true;
bool flag = false;
bool flag2 = false;
float distanceTraveled=0;
float remainingDistance = 0;
float spacing = 1.0;
float threshold = 35.0;
void setup() {
  // Set the motor control pins to outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  compass.init();

  Serial.begin(9600);
  compass.setCalibrationOffsets(539.00, -73.00, -476.00);
  compass.setCalibrationScales(1.03, 0.93, 1.05);
}

void loop() {
  // bool test = checkObject();
  // if (test == true) {
  //   Serial.println("Obstacle in sight");
  // }
    // moveForward(5.0);
    // stopCar(1000);
  // bool x =checkObject();
  // // moveForward(x);
  // if (x ==true) {
  // //   avoidObstacle(x);
  //  Serial.println("object detected");
  
  // }
  // else{
  //      Serial.println("NO OBJECT");

  // }
  mainPathway(3.0, 3.0);
}

float getHeading() {
  int x, y, z;
  compass.read();

  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();
  float heading = atan2((int)y, (int)x) * 180 / PI;
  return heading;
}

float angularDifference(float angle1, float angle2) {
  float difference = fmod(angle2 - angle1 + 540.0, 360.0) - 180.0;
  return difference;
}

void moveForward(float targetDistance) {
  float distanceTraveled = 0;
  startTime = millis();
  float initialHeading = getHeading();
  float distancePerSecond = (rpm * wheelCircumference) / 60.0;
  float distancePerMillisecond = distancePerSecond / 1000.0;

  // While the distance is less than set distance AND there is NO obstacle it will move forward
  // When checkObject is true it will exit the while loop
  while (distanceTraveled < targetDistance) {
    if (checkObject()) {
         Serial.println("object detected & avoiding");

      avoidObstacle(targetDistance);
      break;
    }
    float currentHeading = getHeading();
    float difference = angularDifference(initialHeading, currentHeading);

    if (abs(difference) > 4) {
      //Serial.print("CORRECTING PATH ");
      while (difference > 2) {
      //  Serial.print("TURNING LEFT");
        turnLeft();
        currentHeading = getHeading();
        difference = angularDifference(initialHeading, currentHeading);
        if (checkObject()) {
         avoidObstacle(targetDistance);
          break;
        }
      }

      while (difference < -2) {
        //Serial.print("TURNING RIGHT");
        turnRight();
        currentHeading = getHeading();
        difference = angularDifference(initialHeading, currentHeading);
        if (checkObject()) {
         avoidObstacle(targetDistance);
          break;
          Serial.println(top);
        }
      }
    }

    currentHeading = getHeading();

    // Move forward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(100);

    // Calculate the elapsed time
    unsigned long currentTime = millis();
    float elapsedTime = (currentTime - startTime) / 1000.0;
    // Check for obstacle again in case it appears after movement
    if (checkObject()) {
               Serial.println("object detected & avoiding");

               avoidObstacle(targetDistance);

      break;
    }

    // Update distance traveled
    distanceTraveled = elapsedTime * distancePerSecond;
        
      Serial.println(distanceTraveled);

  }
      Serial.print("Break out the while");
    // if (checkObject()) {
    //   //avoidObstacle(targetDistance);
    //   break;
    // }
  stopCar(500); // Stop the car once the target distance is reached
}



void mainPathway(float length, float width) {

  int cycles = width / spacing;
  for (int i = 0; i < cycles; i++) {
    top = true;
        if(flag == true){
          moveForward(length - 1.0);
                flag = false;

    }
    else if(flag2 ==true){
      moveForward(length- remainingDistance);
    }
    else{
          moveForward(length);

    }
    rightAngle(90);
    moveForward(spacing);
    rightAngle(90);
    if(flag == true){
    moveForward(length - 1.0);
      flag = false;
    }
      else if(flag2 ==true){
      moveForward(length- remainingDistance);
    }
    else{
    moveForward(length);

    }
     top = false;;
    leftAngle(90);
    moveForward(spacing);
    leftAngle(90);

  }
}

void stopCar(int time) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(time);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward(float targetDistance) {
  float distancePerSecond = (rpm * wheelCircumference) / 60.0;
  float distanceBackward = 0; // Initialize distance traveled
  unsigned long startTime = millis();

  while (distanceBackward < targetDistance) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    unsigned long currentTime = millis();
    float elapsedTime = (currentTime - startTime) / 1000.0;

    // Update distance traveled
    distanceBackward = elapsedTime * distancePerSecond;
    Serial.print( "backward distance:");

    Serial.println( distanceBackward);

  }
   
  stopCar(500); // Stop the car once the target distance is reached
}

void rightAngle(float angle) {
  float initialHeading = getHeading();
  float currentHeading = getHeading();
  float difference = angularDifference(initialHeading, currentHeading);

  while (difference < angle) {
    Serial.print("TURNING RIGHT");
    turnRight();
    currentHeading = getHeading();
    difference = angularDifference(initialHeading, currentHeading);
  }

  if (difference >= angle +2) {
    while (difference >= angle) {
      Serial.print("TURNING LEFT");
      turnLeft();
      currentHeading = getHeading();
      difference = angularDifference(initialHeading, currentHeading);
    }
  }
}

void leftAngle(float angle) {
  float initialHeading = getHeading();
  float currentHeading = getHeading();
  float difference = angularDifference(initialHeading, currentHeading);

  while (difference >= -angle) {
    Serial.println("TURNING LEFT");
    turnLeft();
    currentHeading = getHeading();
    difference = angularDifference(initialHeading, currentHeading);
  }

  if (difference <= -(angle +2)) {
    while (difference < -angle) {
      Serial.println("TURNING RIGHT");
      turnRight();
      currentHeading = getHeading();
      difference = angularDifference(initialHeading, currentHeading);
    }
  }
}

// float distanceTraveled() {
//   float distancePerSecond = (rpm * wheelCircumference) / 60.0;
//   unsigned long currentTime = millis();
//   float elapsedTime = (currentTime - startTime) / 1000.0;
//   float distanceInCm = elapsedTime * distancePerSecond;
//   return distanceInCm / 100.0;
// }

bool checkObject() {
  // digitalWrite(trigPin, LOW);
  if(hc.dist() <threshold &&  hc.dist() >0){
    return true;
  }
  else{
    return false;
   }
  Serial.println(hc.dist());
  delay(500);
}

void avoidObstacle(float avoidingDistance) {
  float initialHeading = getHeading();
  delay(10);
           Serial.println("AVOIDING");

  while (checkObject()) { // Check if distance is less than 50 cm
 
    stopCar(100);
    //Serial.println("STOPPING");
    float returnDistance = 1.0;
    backward(returnDistance);
               Serial.println("AVOIDING BACKWARD");

    
    stopCar(100);
   int avoidAngle =40;
   rightAngle(avoidAngle);
    // Get difference between angles to move forward AWAY from object
    float lastHeading = getHeading();

    float returnAngle = angularDifference(initialHeading, lastHeading);
    float newAvoidDistance = (threshold/100 + returnDistance) / cos(degreesToRadians(returnAngle));
    //XSINTHETA
    
  remainingDistance = avoidingDistance - (2 * (threshold/100 + returnDistance));

  

    moveForward(newAvoidDistance);
               Serial.println("FORWARD RIGHT AVOIDING");
                              Serial.println(newAvoidDistance);

      //progress
    leftAngle(2*avoidAngle);
    moveForward(newAvoidDistance);
               Serial.println("RETURNING");

    delay(10);
    // Back on original path and correcting heading
    float currentHeading = getHeading();
    returnAngle = angularDifference(initialHeading, currentHeading);

    while (returnAngle < -2) {
      turnRight();
      currentHeading = getHeading();
      returnAngle = angularDifference(initialHeading, currentHeading);
    }
    // Move forward for the rest of the remaining distance
    moveForward(remainingDistance);
    delay(10);
    stopCar(100);
      }

  
}
}

float degreesToRadians(float degrees) {
  return degrees * PI / 180.0;
}


