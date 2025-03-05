#include <ArduinoJson.h>

#include <SoftwareSerial.h>
int pinCount =0;
int pin = 0;

float currentLatitude = 0.0;
float currentLongitude = 0.0;



#define NODEMCU_TX 0
#define NODEMCU_RX 1
SoftwareSerial nodeMcuSerial(NODEMCU_RX, NODEMCU_TX);

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
  // printPins();
      // Serial.print("Total number of pins: ");

  delay(5000); // Wait for 5 seconds
  


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
