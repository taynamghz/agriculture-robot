
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Wi-Fi credentials
#define WIFI_SSID "%%"
#define WIFI_PASSWORD "lols2003"


// Firebase configuration details
#define FIREBASE_HOST "gps-esp-c2490-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyCsNaE5VSNpqgJ7UqAYVeiDiHT1QwVB9bs"

// Define GPS pins
#define GPS_SERIAL_RX D5
#define GPS_SERIAL_TX D6

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Initialize software serial for GPS
SoftwareSerial SerialGPS(GPS_SERIAL_RX, GPS_SERIAL_TX);

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void setup() 
{
  Serial.begin(115200);         
  SerialGPS.begin(9600);  // Start software serial for GPS
  
  // Connect to Wi-Fi
  //MODE FOR HOTSPOT ONLY
 // WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);           
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());

  // Set the Firebase host and authentication
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  delay(1000);
}

void loop()
{
  // Check if data is available from the GPS module
  while (SerialGPS.available() > 0) {
    char c = SerialGPS.read();
    Serial.write(c);  // Echo the raw data to the Serial Monitor for debugging
    gps.encode(c);  // Process the data using TinyGPS++
  }

  // Print and send GPS data if updated
  if (gps.location.isUpdated()) {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    
    // Send latitude to Firebase
    if (Firebase.setDouble(firebaseData, "latitude", latitude)) {
        Serial.println("Latitude sent to Firebase");
    } else {
        Serial.println("Failed to send latitude, reason: " + firebaseData.errorReason());
    }
    delay(300); 

    // Send longitude to Firebase
    if (Firebase.setDouble(firebaseData, "longitude", longitude)) {
        Serial.println("Longitude sent to Firebase");
    } else {
        Serial.println("Failed to send longitude, reason: " + firebaseData.errorReason());
    }
    delay(300); 
  } else {
    Serial.println("No data from GPS");
  }

  // Print detailed debug information about the GPS status
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());
  Serial.print("HDOP: ");
  Serial.println(gps.hdop.hdop());
}

