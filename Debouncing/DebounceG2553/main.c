//Matthew Rodriguez
#include <msp430.h>


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop WD timer
    P1DIR |=BIT0; //P1.0 output
    P1DIR &= ~BIT1; //set P1.1 input
    P1REN |= BIT1; //enable resistor
    P1OUT |= BIT1; //the pull-up resistor
    P1IE |= BIT1;//enable the interrupt P1.1
    P1IES |= BIT1;//set as falling edge
    P1IFG &= ~BIT1;//clear interrupt flag

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P1OUT ^=0x01; // Toggle P1.1
    P1IE &= ~BIT1; // Disable interrupt
    __delay_cycles(1);

    TA0CTL = TASSEL_1 + MC_1 + ID_1; //Set up Timer A, Count up, divider 2
    TA0CCTL0 = (CCIE); // Set up compare mode for CCTL
    TA0CCR0 = 2000 - 1; // Debounce interupt

    P1IFG &= ~BIT1; // Clear interupt flag
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{

    P1IE |= BIT1; //Enable interrupt.

}
