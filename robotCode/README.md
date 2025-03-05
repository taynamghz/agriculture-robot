# Robot Navigation Code 

This folder contains code to control robot in order to navigate autonomously using GPS coordinates and compass heading data. It communicates with Firebase to store and retrieve GPS coordinates and target waypoints, while adjusting its movement direction using compass data.

---

## Files and Their Functions

### **1. `GPSnavigation.ino`**
This file controls the robot's movement based on GPS coordinates. It calculates the distance and heading to the target location and moves the robot toward it.

**Main Functions:**
- Retrieves GPS coordinates from the robot's GPS module.
- Calculates the distance and heading to the target waypoint.
- Moves the robot towards the target based on the calculated heading.

### **2. `CompassMovement.ino`**
This file adjusts the robot's direction using compass (IMU) data. It ensures the robot moves in the correct heading towards the target waypoint. Incorprate it in the main movement file

**Main Functions:**
- Retrieves compass heading data.
- Adjusts the robot's direction based on the heading towards the target.

### **3. `gpsToFirebase.ino`**
This file collects the GPS coordinates from the GPS module and sends them to Firebase. It allows the robot's position to be tracked in real-time on Firebase.

**Main Functions:**
- Collects latitude and longitude data from the GPS module.
- Sends the GPS coordinates to Firebase for cloud storage.

### **4. `pin_location_updater.ino`**
This file interacts with Firebase to retrieve and update location pins (waypoints) that the robot needs to navigate to.

**Main Functions:**
- Fetches waypoints (latitude and longitude) from Firebase.
- Updates the robot’s path with the retrieved waypoint data.

### **5. `RobotMovement.pdf`**
This is the documentation file that explains the mathematical concepts and code behind the robot’s movement. It provides a detailed understanding of how the robot navigates using GPS and compass data.

**Main Functions:**
- Explains the robot’s movement mechanics.
- Describes the algorithms used for GPS distance calculation, heading adjustments, and movement.

---

## How to Use

1. **Firebase Setup**: 
   - Set up a Firebase account and create a database.
   - Enter your Firebase credentials into `gpsToFirebase.ino` to enable communication with Firebase.
   
2. **Upload Code**:
   - Upload the `.ino` files to your robot using the Arduino IDE.

3. **GPS Data Collection**:
   - The `gpsToFirebase.ino` will collect GPS data and send it to Firebase.

4. **Navigation**:
   - Use `pin_location_updater.ino` to store and update waypoints in Firebase.
   - The robot will navigate towards each waypoint using `GPSnavigation.ino` and adjust its heading using `CompassMovement.ino`.

---


