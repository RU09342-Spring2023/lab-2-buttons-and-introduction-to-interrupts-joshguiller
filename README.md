Author: Joshua Guillermo
Updated: 2/6/2023

The purpose of this code is to have a TI MSP430FR2355 board function as a rudimentary occupancy alert
system with the help of a montion sensor. 

The code utilizes 2 inputs in the pins 4.1 and 2.3, and 2 outputs in the pins 1.0 and 6.6
(red and green LEDs respectively).

The system starts in the ARMED state, where the green LED will blink once every 3 seconds. If the sensor
detects any motion, it will move to the 