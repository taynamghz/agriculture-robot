
# 🌱 Smart Agriculture Robot 🚜  
Industry 4.0 lab, Prince Sultan University 
### A Wi-Fi Controlled Precision Farming Robot  
![My Agriculture Robot](robot.JPG)


 This robot is designed to assist farmers by autonomously navigating fields, collecting data, and providing real-time updates via a web interface. It integrates **ESP8266 for navigation**, **Wi-Fi communication for remote access**, and **sensor-based data collection** to enhance efficiency in farming.  

---

## 📌 Features  
✅ **Autonomous Navigation** – Controlled via ESP8266 for precise movement  
✅ **Real-time GPS Tracking** – Farmers can monitor the robot’s position remotely  
✅ **Wi-Fi Communication** – Sends data to a farmer’s device seamlessly  
✅ **Web Dashboard** – User-friendly interface for live monitoring  
✅ **Data Collection** – Optimizing agriculture tasks 

---

## 🛠️ Hardware & Software  
### **🔧 Hardware Components**  
- ESP8266 (Wi-Fi microcontroller)  
- Motors & Motor Drivers  
- GPS Module NEO 6M GY-NEO6MV2
- Grove 3-Axis Digital Compass HMC5883L
- Ultrasonic sensor HC-SR04 
- Power Supply (Battery & Solar option)  

### **💻 Software & Technologies**  
- Embedded C++ (for ESP8266 firmware)  
- Python (for data processing)  
- HTML, CSS, JavaScript (for web interface)  
- MQTT / HTTP (for communication)  

---
## 🗂️ RASP Folder Contents

### 1️⃣ Design Files
The **Design** folder contains 3D models and schematics that detail the physical structure of the robot. These files are based on the design inspiration from NASA's **Perseverance Rover** and adapted for agricultural applications. The 3D models can be used to create the robot’s body and components using 3D printing or CNC machining.

#### Key Features of the Design:
- **Durable Chassis**: Sturdy build to withstand field conditions.
- **Modular Components**: Easily replaceable parts to cater to different agricultural tasks.
- **Suspension System**: Allows for smooth navigation across uneven terrain, much like the Mars Rover.

---

### 2️⃣ Interface Code
The **Interface Code** folder includes all the code related to setting up the robot's user interface. The interface is a key feature for remote control and monitoring of the robot's tasks. This folder contains:

- **Web Dashboard**: Developed with HTML, CSS, and JavaScript for live monitoring.
- **Pathway Setting**: Allows the user to set waypoints and control the robot’s autonomous navigation.

#### Key Features of the Interface:
- **Real-time Tracking**: The robot’s location is tracked and updated live.
- **Waypoints & Navigation**: The user can set paths and monitor the robot's progress through the field.

---

### 3️⃣ Robot Code
This is the main folder containing all the code that drives the robot’s movements, sensors, and communication systems. It includes several important files such as:

- **CompassMovement.ino**: Manages the robot’s navigation using the compass sensor.
- **GPSnavigation.ino**: Handles GPS data collection and movement based on GPS coordinates.
- **gpsToFirebase.ino**: Sends GPS data to Firebase for real-time monitoring.
- **pin_location_updater.ino**: Updates and tracks the robot's position in the field using sensors.

#### Key Features of the Robot Code:
- **Autonomous Navigation**: The robot uses GPS and compass data for autonomous movement.
- **Data Logging**: Sends live updates of the robot’s status and location to the cloud.
- **Obstacle Avoidance**: Uses sensors to detect and avoid obstacles in the field.

---

## 📑 Documentation

Each folder contains a PDF file providing detailed documentation for the respective section. These documents explain the design, software setup, and functionality of each part in detail.

- **Design Documentation**: Explains the physical construction and components of the robot.
- **Interface Code Documentation**: Details the web interface functionality, including the design of the dashboard and pathway setting.
- **Robot Code Documentation**: Provides an overview of the robot's movement code, sensor integration, and communication system.

## 🚀 Setup & Installation  
### **1️⃣ Hardware Setup**  
All hardware assembly instructions and electrical connections are detailed in the **final documentation file** located in the [`Documentation`](./Documentation) folder.  

### **2️⃣ Software Setup**  
1. Clone this repository:  
   ```sh
   git clone https://github.com/taynamghz/Agriculture-Robot.git
   cd Agriculture-Robot
2. Programming the ESP8266:
* Use Arduino IDE or VS Code with the Arduino extension (install the "Arduino" extension by Microsoft).
* Ensure you have the ESP8266 board package installed in Arduino IDE (Boards Manager -> ESP8266).
* Install required libraries (WiFi, Firebase, MQTT, etc.) as mentioned in ESP8266_Control/requirements.txt.
* Flash the ESP8266 firmware using the code in ESP8266_Control/.
3. Web Interface & Firebase Setup:
* Use VS Code for developing the web dashboard.
The interface is built using HTML, CSS, and JavaScript.
* Firebase is used for real-time data communication between the ESP8266 and the web interface.
Follow Firebase setup instructions in Web_Interface/README.md to configure database and authentication.
