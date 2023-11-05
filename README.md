#  Oppressor - The Feline Discomfort Bot
![Oppressor photo](https://github.com/raaymax/oppressor/blob/main/photo.jpg?raw=true)

## Description

Welcome to the Oppressor project, where whimsy meets technology! Oppressor is not your typical robot; it doesn't conquer worlds or perform grand feats. Instead, it specializes in a unique and somewhat tongue-in-cheek mission – making cats feel a little uneasy.

## Project Details

Wireless Control: Oppressor is controlled using WiFi UDP packet transmission, allowing you to manipulate its behavior from the comfort of your laptop or any computer. This wireless control adds an element of surprise and delight to the interaction with your feline friends.

- **Custom PCB**: To bring Oppressor to life, we've designed a custom-made PCB (Printed Circuit Board) to ensure efficient and reliable operation. The PCB is at the heart of this project, facilitating seamless communication between the robot's components.

- **3D Printing Models**: We understand that the Oppressor community might want to explore customization. That's why we've included 3D printing models in the repository. These models can be used to create unique, personalized exteriors for your robot. Let your creativity run wild!

- **Video Stream**: Oppressor provides an immersive experience by offering a video stream feature powered by ESP32-CAM. This allows you to see the world from the robot's perspective, making for an even more engaging and entertaining experience.

- **Python Control Code**: The code for controlling Oppressor is written in Python, making it accessible and easy to modify for those who want to tweak the robot's behavior or add new features. This open-source nature encourages collaboration and innovation within the community.

## Purpose

The Oppressor project is all about adding a touch of whimsy to the world of robotics. It's a light-hearted experiment that explores how technology can interact with our four-legged friends. While Oppressor's name might sound intimidating, rest assured, it's all in good fun. Cats won't be harmed, only a little spooked.

## Parts list

- Seeed Xiao ESP32-S3 Sense 
- ESP32 devkitc?
- DC motors with wheels https://botland.com.pl/silniki-dc-katowe-z-przekladnia/3696-kolo-silnik-65x26mm-5v-z-przekladnia-48-1-5903351248129.html

## Build instructions

1. Order or make PCB based on schematics from `PCB/`
2. Print body on 3d printer `Models/Oppressor_body.stl`
3. Program esp32 with firmware from `Firmware/`
4. For esp32 cam https://github.com/rzeldent/esp32cam-rtsp is used
4. Solder all elements on your PCB
5. Assemble robot

## Video stream

[https://github.com/rzeldent/esp32cam-rtsp/tree/feature/seeed_xiao_esp32s3](https://github.com/rzeldent/esp32cam-rtsp/tree/feature/seeed_xiao_esp32s3)

## Usage

Turn on robot and check using USB serial whats it's IP address (baud: 115200). Connect to robot using `Control/` script and use arrows to control it. 
Have fun and go chasing some cats.

## Contributions

Feel free to contribute to Oppressor by adding new control features, enhancing the video stream, creating new 3D printing models, or optimizing the Python control code. This project is a canvas for creativity, where you can experiment with the boundaries of human-robot and feline-robot interactions.

Remember, Oppressor is a project with a sense of humor, aimed at celebrating the quirky relationship between technology and our feline companions. So, join us in creating an amusing and intriguing experience for cats and their humans!

## MIT License

Copyright (c) 2023 Mateusz Russak
