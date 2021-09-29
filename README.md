# FP-Swarm
This project is part of study-project at TU Dortmund. 
## About
This project is a prototype of distributed machine learning deployed on a drone swarm.
Each node of the swarm runs an instance of random forest and supplies the classifications via Bluetooth to the central node.
The central node controls the swarm and communication by following the Host-Client-Pattern.

## The Hardware 
For this project we used the STM32 F407 Discovery Board as MCU for the nodes of the swarm.
For the communication between the host and clients we used the HC-05 Bluetoothmodule.
As host we used a Windows 10 Laptop with in build Bluetooth.

## The Implementation
The firmware for the swarm nodes is written in C by using the STM32CubeIDE which proviedes some useful features for the STM32.
The host is written in Java by unsing the Intellij IDEA.

## Deployment
Host:
The host is quite easy to deploy, just ad a suitable runconfiguration to Intellij and pair your host with the HC-05 via your systems Bluetooth configuration.

Client:
The fist stepp in deployment is the wiring between the HC-05 and the STM:

- PA3 connected to TXD
- PA2 connected to RXD
- 5V connected to VCC
- GND connected to GND

For the client IDE we recommend the "STM32 CubeIDE". After you import the Repo it should work fine. Connect each STM32 boards after another and flash the firmware. Connect the STM32 boards with power and press the black "Reset" buttons, after that start the Host.  

There are some test data in "MCU Firmware/Core/Src/TestData/". Until now the data is hardcoded, so you must substitute the main file with the test-main file and then flash each board again. 
