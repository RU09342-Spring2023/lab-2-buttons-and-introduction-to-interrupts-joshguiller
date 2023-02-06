/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Joshua Guillermo
 */

#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               //stop watchdog timer

    //initialize all the states
    #define ARMED_STATE 0
    #define WARNING_STATE 1
    #define ALERT_STATE 2

    P4DIR &= ~BIT1;     // Configure Pin 4.1 to an input
    P4REN |= BIT1;      // Enable the pull up/down resistor for Pin 4.1
    P4OUT |= BIT1;      // While configured as an input, P4OUT controls whether the Resistor is a pull up or pull down

    P2DIR &= ~BIT3;     // Configure Pin 2.3 to an input
    P2REN |= BIT3;      // Enable the pull up/down resistor for Pin 2.3
    P2OUT |= BIT3;      // While configured as an input, P2OUT controls whether the Resistor is a pull up or pull down

    P1OUT &= ~BIT0;     // Clears value of Pin 1.0
    P1DIR |= BIT0;      // Configure Pin 1.0 to an output (Red LED)

    P6OUT &= ~BIT6;     // Clears value of Pin 6.6
    P6DIR |= BIT6;      // Configure Pin 6.6 to an output (Green LED)

    PM5CTL0 &= ~LOCKLPM5;          // Disable the GPIO power-on default high-impedance mode
                                   // to activate previously configured port settings

    char state = ARMED_STATE;      // Makes the default state of the security system the ARMED_STATE
    char count = 0;

    while(1)
    {
        switch (state)
        {
        case ARMED_STATE:

        if(P2IN & BIT3)          // Check if the sensor detects someone
        {
            P6OUT ^= BIT6;         // Toggle the Green LED
        }
        else
        {
            state = WARNING_STATE;  // Move to the WARNING_STATE
        }

        __delay_cycles(1500000);    // Delay for 3000000*(3/MCLK) = 3s

        break;

        case WARNING_STATE:

            P6OUT &= ~BIT6;         // Turn off Green LED
            P1OUT ^= BIT0;          // Toggle the Red LED

            if((!(P2IN & BIT3)) && (count == 20))     // If the sensor still detects someone after 10 seconds
            {
                state = ALERT_STATE;                  // Move to the ALERT_STATE
                count = 0;                            // Reset the counter
            }
            else if((P2IN & BIT3) || (count == 20))   // If the sensor doesn't detect someone before 10 seconds
            {
                P1OUT &= ~BIT0;                       // Turn off the Red LED
                state = ARMED_STATE;                  // Move to the ARMED_STATE
                count = 0;                            // Reset the counter
            }

            count++;                                  // Add 1 every half second, 2 counts = 1 second

            __delay_cycles(500000);    // Delay for 500000*(0.5/MCLK) = 0.5s: 20 half seconds = 10 seconds

        break;

        case ALERT_STATE:

        P1OUT |= BIT0;                 // Completely keep the Red LED on

        if(!(P4IN & BIT1))             // If Pin 4.3 is pressed
        {
            P1OUT &= ~ BIT0;           // Turn off the Red LED
            state = ARMED_STATE;       // Move to the ARMED_STATE
        }

        break;

        }
    }
}






