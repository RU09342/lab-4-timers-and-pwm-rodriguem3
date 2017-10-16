//Matthew Rodriguez
#include <msp430.h>

volatile unsigned int j;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P1OUT &= ~BIT0;                         // Switch LED off
    P9DIR |=BIT7;                           //set Port 9.7 output ---LED
    P9OUT &= ~BIT7;                         //Clear P9.7
    P1DIR  &= ~BIT1;                        // Set P1.1 as input
    P1OUT |= BIT1;                          // Configure P1.1 for Pull-Up
    P1REN |= BIT1;                          // Enable Pull Up of P1.1
    TA0CCTL1 = OUTMOD_7;
    TA0CTL = TASSEL_2 + MC_1 +TACLR ;
    TA0CCR0 = 100-1;
    TA0CCR1 = 50;
    P1SEL0 |= BIT0;                         // PWM output to LED P1.0
    P1SEL1 &= ~BIT0;

    while(1)
    {
        if(!(P1IN & BIT1))
        {
            P9OUT |= BIT7; //Sets P9.7
            if(TA0CCR1 < 1000) // If the brightness is <= than 90%
            {
                TA0CCR1 += 100; // Add 100
                TA0CCR0 = 1000;
            }
            else if (TA0CCR1 >= 1000){
                TA0CCR1 = 0; // Reset CCR1
                TA0CCR0 = 1000;
            }
        }
        if((P1IN & BIT1))
            P9OUT &= ~BIT7; //Clear P9.7
        // Debounce
        for(j=100;j>0;j--)
        {
        __delay_cycles(1000);
        }
    }
}
