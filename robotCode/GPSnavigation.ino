

#include <ArduinoJson.h>
#include <math.h>
#include <QMC5883LCompass.h>
#include <HCSR04.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// // Distance
// float wheelDiameter = 0.122; // Diameter in meters
// float wheelCircumference = PI * wheelDiameter; // Circumference in meters
// float rpm = 20; 
// float distancePerSecond = (rpm * wheelCircumference) / 60.0; 
// unsigned long startTime;
// float distanceTraveled = 0;
// float remainingDistance = 0;
// float distance;
// float threshold = 35.0; 
int pinCount =0;
int pin = 0;
// int currentStartPin;
// int currentEndPin;

float currentLatitude = 0.0;
float currentLongitude = 0.0;

// const float EARTH_RADIUS = 6371000;


#define NODEMCU_TX 0
#define NODEMCU_RX 1
SoftwareSerial nodeMcuSerial(NODEMCU_RX, NODEMCU_TX);

// QMC5883LCompass compass;
// HCSR04 hc(7, 8); // Initialize HCSR04 (trig pin, echo pin)

const int IN1 = 2; 
const int IN2 = 3; 
const int IN3 = 4; 
const int IN4 = 5; 

struct Pin {
  String name;
  float lat;
  float lng;
};

Pin pins[100]; 

void setup() { 
  // Initialize serial communication for debugging
  Serial.begin(9600);
  nodeMcuSerial.begin(9600);

}

void loop() {
  if (nodeMcuSerial.available()) {
    String data = nodeMcuSerial.readStringUntil('\n');
    processIncomingData(data);
  }
  // Print pins for debugging
  printPins();
      Serial.print("Total number of pins: ");

  delay(5000); // Wait for 5 seconds
  
  // int index = 0;
  // mainPathway(index);

}

void printPins() {
  Serial.println("Pins data:");
  Serial.print("Total number of pins: ");
  Serial.println(pinCount);
  
  for (int i = 0; i < pinCount; i++) {
    Serial.print("Index ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print("Name: ");
    Serial.print(pins[i].name);
    Serial.print(", Latitude: ");
    Serial.print(pins[i].lat, 6); // Print latitude with 6 decimal places
    Serial.print(", Longitude: ");
    Serial.println(pins[i].lng, 6); // Print longitude with 6 decimal places
  }
}

// // Calculate distance from pins
// float haversine(float lat1, float lon1, float lat2, float lon2) {
//   float dLat = radians(lat2 - lat1);
//   float dLon = radians(lon2 - lon1);
//   lat1 = radians(lat1);
//   lat2 = radians(lat2);

//   float a = sin(dLat / 2) * sin(dLat / 2) +
//             sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
//   float c = 2 * atan2(sqrt(a), sqrt(1 - a));

//   //return EARTH_RADIUS * c;
// }

// // Function to convert degrees to radians
// float degreesToRadians(float degrees) {
//   return degrees * (PI / 180.0);
// }

// // Function to calculate bearing between two points
// float calculateBearing(int startPin, int endPin) {
//   // Convert degrees to radians
//   float startLat = pins[startPin].lat;
//   float startLng = pins[startPin].lng;
//   float endLat = pins[endPin].lat;
//   float endLng = pins[endPin].lng;

//   // Calculate the difference in longitudes
//   float dLon = endLng - startLng;

//   // Calculate the bearing
//   float y = sin(dLon) * cos(endLat);
//   float x = cos(startLat) * sin(endLat) - sin(startLat) * cos(endLat) * cos(dLon);
//   float bearingRad = atan2(y, x);

//   // Convert radians to degrees
//   float bearingDeg = bearingRad * (180.0 / PI);

//   // Normalize the bearing to 0-360 degrees
//   bearingDeg = fmod((bearingDeg + 360.0), 360.0);

//   return bearingDeg;
// }

// void moveForward(int startPin, int endPin) {
//   if (startPin < 0 || endPin >= pinCount) {
//     Serial.println("Invalid pin numbers");
//     return;
//   }
//   currentStartPin = startPin;
//   currentEndPin = endPin;

//   float startLat = pins[startPin].lat;
//   float startLng = pins[startPin].lng;
//   float endLat = pins[endPin].lat;
//   float endLng = pins[endPin].lng;

//   distance = haversine(startLat, startLng, endLat, endLng);
//   Serial.print("Moving from ");
//   Serial.print(pins[startPin].name);
//   Serial.print(" to ");
//   Serial.print(pins[endPin].name);
//   Serial.print(". Distance: ");
//   Serial.print(distance);
//   Serial.println(" meters");

//   float initialHeading = getHeading(); 
//   float distanceTraveled = 0;
//   unsigned long startTime = millis(); 

//   while (distanceTraveled < distance) {
//     float currentHeading = getHeading();
//     float difference = angularDifference(initialHeading, currentHeading);
//     if (checkForObstacle()) {
//       Serial.println("Object detected & avoiding");
//       //avoidObstacle(distance);
//       break;
//     }
//     if (abs(difference) > 4) {
//       while (difference > 2) {
//         turnLeft();
//         currentHeading = getHeading();
//         difference = angularDifference(initialHeading, currentHeading);
//       }

//       while (difference < -2) {
//         turnRight();
//         currentHeading = getHeading();
//         difference = angularDifference(initialHeading, currentHeading);
//       }
//     }

//     currentHeading = getHeading();

//     digitalWrite(IN1, LOW);
//     digitalWrite(IN2, HIGH);
//     digitalWrite(IN3, LOW);
//     digitalWrite(IN4, HIGH);
//     delay(100);
//     if (checkForObstacle()) {
//       Serial.println("Object detected & avoiding");
//       //avoidObstacle(distance);
//       break;
//     }
//     unsigned long currentTime = millis();
//     float elapsedTime = (currentTime - startTime) / 1000.0;

//     distanceTraveled = elapsedTime * distancePerSecond;

//     Serial.print("Distance traveled: ");
//     Serial.println(distanceTraveled);
//   }

//   //stopCar(500); 
// }

// void turnRight() {
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }

// void turnLeft() {
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }

// void backward(float targetDistance) {
//   float distancePerSecond = (rpm * wheelCircumference) / 60.0;
//   float distanceBackward = 0; 
//   unsigned long startTime = millis();

//   while (distanceBackward < targetDistance) {
//     digitalWrite(IN1, HIGH);
//     digitalWrite(IN2, LOW);
//     digitalWrite(IN3, HIGH);
//     digitalWrite(IN4, LOW);

//     unsigned long currentTime = millis();
//     float elapsedTime = (currentTime - startTime) / 1000.0;

//     distanceBackward = elapsedTime * distancePerSecond;
//     Serial.print("Backward distance: ");
//     Serial.println(distanceBackward);
//   }

//   //stopCar(500); 
// }

// void rightAngle(float angle) {
//   float initialHeading = getHeading();
//   float currentHeading = getHeading();
//   float difference = angularDifference(initialHeading, currentHeading);

//   while (difference < angle) {
//     Serial.print("TURNING RIGHT");
//     turnRight();
//     currentHeading = getHeading();
//     difference = angularDifference(initialHeading, currentHeading);
//   }

//   if (difference >= angle + 2) {
//     while (difference >= angle) {
//       Serial.print("TURNING LEFT");
//       turnLeft();
//       currentHeading = getHeading();
//       difference = angularDifference(initialHeading, currentHeading);
//     }
//   }
// }

// void leftAngle(float angle) {
//   float initialHeading = getHeading();
//   float currentHeading = getHeading();
//   float difference = angularDifference(initialHeading, currentHeading);

//   while (difference >= -angle) {
//     Serial.println("TURNING LEFT");
//     turnLeft();
//     currentHeading = getHeading();
//     difference = angularDifference(initialHeading, currentHeading);
//   }

//   if (difference <= -(angle + 2)) {
//     while (difference < -angle) {
//       Serial.println("TURNING RIGHT");
//       turnRight();
//       currentHeading = getHeading();
//       difference = angularDifference(initialHeading, currentHeading);
//     }
//   }
// }

// float getHeading() {
//   int x, y, z;
//   compass.read();

//   x = compass.getX();
//   y = compass.getY();
//   z = compass.getZ();

//   float heading = atan2(y, x);
//   float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
//   heading += declinationAngle;

//   if (heading < 0) {
//     heading += 2 * PI;
//   }
//   if (heading > 2 * PI) {
//     heading -= 2 * PI;
//   }

//   float headingDegrees = heading * 180 / PI;

//   Serial.print("Heading: ");
//   Serial.print(headingDegrees);
//   Serial.println(" degrees");

//   return headingDegrees;
// }

// float angularDifference(float targetAngle, float currentAngle) {
//   float difference = targetAngle - currentAngle;

//   while (difference > 180.0) {
//     difference -= 360.0;
//   }

//   while (difference < -180.0) {
//     difference += 360.0;
//   }

//   return difference;
// }

void processIncomingData(String data) {
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, data);
  
  if (error) {
    Serial.print("JSON deserialization failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  if (doc.containsKey("pinCount")) {
    // Process pin count and pin data
    JsonArray dataArray = doc["pins"].as<JsonArray>();
    pinCount = dataArray.size();

    for (int i = 0; i < pinCount; i++) {
      JsonObject dataObject = dataArray[i];
      pins[i].name = dataObject["name"].as<String>();
      pins[i].lat = dataObject["lat"].as<float>();
      pins[i].lng = dataObject["lng"].as<float>();

      Serial.print("Pin Received: ");
      Serial.print(pins[i].name);
      Serial.print(", Latitude: ");
      Serial.print(pins[i].lat, 6);
      Serial.print(", Longitude: ");
      Serial.println(pins[i].lng, 6);
    }
  }
  
  if (doc.containsKey("currentLatitude") && doc.containsKey("currentLongitude")) {
    // Process current location data
    currentLatitude = doc["currentLatitude"].as<float>();
    currentLongitude = doc["currentLongitude"].as<float>();
    Serial.print("Current Location Updated: Latitude = ");
    Serial.print(currentLatitude, 6);
    Serial.print(", Longitude = ");
    Serial.println(currentLongitude, 6);
  }
}

// void updateCurrentLocation() {
//   if (nodeMcuSerial.available()) {
//     String gpsData = nodeMcuSerial.readStringUntil('\n');
//     int commaIndex = gpsData.indexOf(',');

//     if (commaIndex > 0) {
//       currentLatitude = gpsData.substring(0, commaIndex).toFloat();
//       currentLongitude = gpsData.substring(commaIndex + 1).toFloat();
//       Serial.print("Current Latitude: ");
//       Serial.println(currentLatitude, 6);
//       Serial.print("Current Longitude: ");
//       Serial.println(currentLongitude, 6);
//     }
//   }
// }

// void mainPathway(int startPin) {
//   for (int i = startPin; i < pinCount - 1; i++) {
//     currentStartPin = i;
//     currentEndPin = i + 1;
//     Serial.print("Moving from pin ");
//     Serial.print(currentStartPin);
//     Serial.print(" to pin ");
//     Serial.println(currentEndPin);
//     moveForward(currentStartPin, currentEndPin);
//   }
//   Serial.println("Pathway traversal complete.");
// }

// bool checkForObstacle() {
//   long distance = hc.dist();
//   Serial.print("Obstacle distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");
//    if(distance <= threshold){
// return true;
//    } else {
// return 
//     false;
//    }  
// }

// void avoidObstacle(float totalDistance) {
//   if(checkForObstacle()){
// stopCar(500);

//   backward(0.2 * totalDistance);

//   rightAngle(90);
//   delay(500);
//   moveForward(currentStartPin, currentEndPin);
//   }
  
// }

// void stopCar(int duration) {
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
//   delay(duration);
// }



