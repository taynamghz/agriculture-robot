# Robot Navigation Interface

This repository contains the web interface for the **Robot Navigation System**, designed to manage the robot’s path and track its real-time movement on a map.

## Files Included:

- **homePage.html**: The main interface where the user selects whether to set a robot path or track its real-time position.
- **pinweb.html**: The page for setting the robot's pathway. Users can input coordinates and other relevant data to define the path.
- **pinweb.css**: The accompanying CSS file for styling the **pinweb.html** page.
- **map.html**: The page displaying the real-time GPS tracking of the robot on a map.
- **map.css**: The CSS file used to style the **map.html** page and map container.
- **robot_navigation_documentation.pdf**: The detailed documentation of the system, explaining how the interface works and the technologies used.
- **background_image.jpg**: The background image used on the **homePage.html** to enhance the user interface.

## Features:
- **Home Page**: Allows the user to choose between setting a robot path or tracking its real-time location.
- **Pathway Setting**: Users can define the robot's path by inputting specific coordinates.
- **Real-Time Tracking**: Displays the robot's position on a Google Map as it moves, updated in real-time using Firebase.

## Technologies Used:
- **HTML5**, **CSS3**: Structure and styling of the web pages.
- **Bootstrap**: Used for layout and responsiveness.
- **JavaScript**: Handles dynamic content, Firebase integration for real-time updates, and Google Maps for visualization.
- **Firebase**: Real-time data synchronization.
- **Google Maps API**: Used for displaying the robot's location on a map.

## Setup:
1. Ensure that you have **Firebase** and **Google Maps API** configured correctly.
2. Open the `homePage.html` to get started with the interface.
3. For further instructions, refer to the included **robot_navigation_documentation.pdf**.

