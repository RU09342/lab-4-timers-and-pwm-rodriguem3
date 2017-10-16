//Matthew Rodriguez
#include <msp430.h>

volatile unsigned int j;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P1OUT &= ~BIT0;                         // Switch LED off
    P1DIR |=BIT1;                           //set Port 1.1 output ---LED
    P1OUT &= ~BIT1;                         //Clear P1.1
    P5DIR  &= ~BIT6;                        // Set P5.6 as input
    P5OUT |= BIT6;                          // Configure P5.6 for Pull-Up
    P5REN |= BIT6;                          // Enable Pull Up of P5.6
    TA0CTL = TASSEL_2 + MC_1 +TACLR ;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0 = 1000;
    TA0CCR1 = 500;
    P1SEL0 |= BIT0;
    P1SEL1 &= ~BIT0;

    while(1)
    {
        if(!(P5IN & BIT6))
        {
            P1OUT |= BIT1; //Sets P1.1
            if(TA0CCR1 < 1000)
            {
                TA0CCR1 += 100;
            }
            else if (TA0CCR1 >= 1000){
                TA0CCR1 = 0;
            }
        }
        if((P5IN & BIT6))
            P1OUT &= ~BIT1; //Clear P1.1
        // Debounce
        for(j=100;j>0;j--)
        {
        __delay_cycles(1000);
        }
    }
}
