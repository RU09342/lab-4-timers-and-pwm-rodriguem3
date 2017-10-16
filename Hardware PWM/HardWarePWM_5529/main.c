//Matthew Rodriguez
#include <msp430.h>

volatile unsigned int j;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P1OUT &= ~BIT0;                         // Switch LED off
    P4DIR |=BIT7;                           //set Port 4.7 output ---LED
    P4OUT &= ~BIT7;                         //Clear P4.7
    P2DIR  &= ~BIT1;                        // Set P2.1 as input
    P2OUT |= BIT1;                          // Configure P2.1 for Pull-Up
    P2REN |= BIT1;                          // Enable Pull Up of P2.1
    TA0CCTL1 = OUTMOD_7;                    // Reset/Set Mode
    TA0CTL = TASSEL_2 + MC_1 +TACLR ;       // SMCLK / Upmode
    TA0CCR0 = 1000;
    TA0CCR1 = 500;

    while(1)
    {
        if(!(P1IN & BIT1)) //If the button is pressed
        {
            P4OUT |= BIT7; //Sets P4.7
            if(TA0CCR1 < 1000) // If the brightness is <= than 90%
            {
                TA0CCR1 += 100; // Add 100
                TA0CCR0 = 1000;
            }
            else if (TA0CCR1 >= 1000){ // If the brightness is at 100%
                TA0CCR1 = 0; // Reset CCR1
                TA0CCR0 = 1000;
            }
        }
        if((P1IN & BIT1))
            P4OUT &= ~BIT7; //Clear P4.7
        for(j=100;j>0;j--)
        {
        __delay_cycles(1000);
        }
    }
}
