//Matthew Rodriguez
#include <msp430.h>

volatile unsigned int j;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P1OUT &= ~BIT0;                         // Switch LED off
    P1DIR |=BIT6;                           //set Port 1.6 output ---LED
    P1OUT &= ~BIT6;                         //Clear P1.6
    P1DIR  &= ~BIT3;                        // Set P1.3 as input
    P1OUT |= BIT3;                          // Configure P1.3 for Pull-Up
    P1REN |= BIT3;                          // Enable Pull Up of P1.3
    TA0CCTL1 = OUTMOD_7;
    TA0CTL = TASSEL_2 + MC_1 +TACLR ;
    TA0CCR0 = 1000;
    TA0CCR1 = 500;


    while(1)
    {
        if(!(P1IN & BIT3))
        {
            P1OUT |= BIT6; //Sets P1.6
            if(TA0CCR1 < 1000)
            {
                TA0CCR1 += 10;
            }
            else if (TA0CCR1 >= 1000){
                TA0CCR1 = 0; // Reset CCR1
            }
        }
        if((P1IN & BIT3)) // If button is not pressed
            P1OUT &= ~BIT6; //Clear P1.6
        // Debounce
        for(j=100;j>0;j--)
        {
        __delay_cycles(1000);
        }
    }
}
