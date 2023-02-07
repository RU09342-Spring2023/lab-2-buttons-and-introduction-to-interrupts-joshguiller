Author: Joshua Guillermo
Updated: 2/6/2023

The purpose of this code is to have a TI MSP430FR2355 board function as a rudimentary occupancy alert system with the help of a montion sensor. 

The code utilizes 2 inputs in the pins 4.1 and 2.3, and 2 outputs in the pins 1.0 and 6.6 (red and green LEDs respectively).

The system starts in the ARMED state, where the green LED will blink once every 3 seconds. If the sensor detects any motion, it will move to the WARNING state.

In the WARNING state, the Green LED will turn off while the red LED will blink once per second, or 500ms on and 500 ms off. If the sensor still detects someone there after 10 seconds, the system will move to the ALERT state. If no one is detected before the 10 seconds, the system should move back to the ARMED state.

In the ALERT state, the red will stop blinking and instead constantly stay on. When in this state, the only way for the system to return back to the ARMED state is to press the Pin 4.1 button.

In order to count the amount of seconds used in the WARNING state, a counter is instantiated where 1 is added to the counter value every half a second. Therefore, 20 half seconds = 10 second. 