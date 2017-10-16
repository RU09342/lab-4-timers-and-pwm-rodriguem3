//Matthew Rodriguez
#include <msp430.h>

volatile unsigned int j;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P1OUT &= ~BIT0;                         // Switch LED off
    P2DIR |=BIT0;                           //set Port 2.0 output ---LED
    P2OUT &= ~BIT0;                         //Clear P2.0
    P1DIR  &= ~BIT1;                        // Set P1.1 as input
    P1OUT |= BIT1;                          // Configure P1.1 for Pull-Up
    P1REN |= BIT1;                          // Enable Pull Up of P1.1
    TB0CCTL1 = OUTMOD_7;
    TB0CTL = TBSSEL_2 + MC_1 +TBCLR ;
    TB0CCR0 = 1000;
    TB0CCR1 = 500;


    while(1)
    {
        if(!(P1IN & BIT1))
        {
            P2OUT |= BIT0; //Sets P2.0
            if(TB0CCR1 < 1000)
            {
                TB0CCR1 += 100;
            }
            else if (TB0CCR1 >= 1000){
                TB0CCR1 = 0;
            }
        }
        if((P1IN & BIT1))
            P2OUT &= ~BIT0; //Clear P2.0
        // Debounce
        for(j=100;j>0;j--)
        {
        __delay_cycles(1000);
        }
    }
}
