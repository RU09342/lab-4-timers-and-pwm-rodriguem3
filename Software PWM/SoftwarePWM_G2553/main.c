//Matthew Rodriguez
#include <msp430.h>
#include <Math.h>

volatile unsigned int j;
int taps = 10;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P1OUT &= ~BIT0;                         // Switch LED off


    P1DIR |=BIT6; //set Port 9.4 output ---LED
    P1OUT &= ~BIT6; //Clear P9.4

    P1DIR  &= ~BIT3;                        // Set P1.1 as input
    P1OUT |= BIT3;                          // Configure P1.1 for Pull-Up
    P1REN |= BIT3;                          // Enable Pull Up of P1.1
    P1IE |= BIT3; //enable the interrupt on Port 1.1
    P1IES &= ~BIT3; //set as falling edge
    P1IFG &= ~(BIT3); //clear interrupt flag


    TA0CTL = TASSEL_2 + MC_1 ;       // SMCLK / Upmode
    TA0CCTL1 = (CCIE);
    TA0CCTL0 = (CCIE);
    TA0CCR0 = 1000-1;                        // PWM Frequency 10 kHz
    TA0CCR1 = 500;                           // 50% Duty Cycle

    __bis_SR_register(GIE);
    while(1)
    {
        if((P1IN & BIT1))
            P1OUT &= ~BIT6; //Clear P9.4

    }
}

//Timer A interrupt vectors
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR (void)
{
    if(TA0CCR1 != 1000)
    {
       P1OUT &= ~(BIT0); //turns off red led
    }
    TA0CCTL1 &= ~BIT0; //clears flag
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
    if(TA0CCR1 != 0){
        P1OUT |= (BIT0); //turns on red led
    }
    TA0CCTL0 &= ~BIT0;  //clears flag
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRS(void)
{
    P1IE &= ~BIT3;
    __delay_cycles(1000);
    P1IE |= BIT3;

    P1OUT |= BIT6; //Sets P9.4
    if(TA0CCR1 < 1000)
    {
        TA0CCR0 = 0;
        TA0CCR1 += 100;
        TA0CCR0 = 1000;
    }
    else if (TA0CCR1 >= 1000){
        TA0CCR0 = 0;
        TA0CCR1 = 0;
        TA0CCR0 = 1000;
    }
    P1IFG &= ~BIT3;
}
