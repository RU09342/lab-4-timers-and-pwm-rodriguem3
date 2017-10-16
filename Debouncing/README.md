# Debounce
## Author: Matthew Rodriguez, Seamus Plunkett, Austin Huang
## Summary
Most buttons have a spring constant and when pressed may cause the buttons signal to jump from high to low repetedly for a very short time. 
This code will minimize this effect by disableing the buttons ability to cause an interupt for a very short amount of time.

## Notes
The first thing this program does is stop the watch dog timer, this is done to ensure that the processor will not reset. This is done with the following statement:
```c
	WDTCTL = WDTPW + WDTHOLD or WDTCTL = WDTPW | WDTHOLD
```

Pins are initialized to determine if its an input or output and configures interupts on the pin.
```c
	P1DIR |=BIT0; //P1.0 output
    P1DIR &= ~BIT1; //set P1.1 input
    P1REN |= BIT1; //enable resistor
    P1OUT |= BIT1; //the pull-up resistor
    P1IE |= BIT1;//enable the interrupt P1.1
    P1IES |= BIT1;//set as falling edge
    P1IFG &= ~BIT1;//clear interrupt flag
```
Low power mode enabled
```c
	_BIS_SR(LPM4_bits + GIE);
```
## How it works
An interupt is set on a button. When that button is pressed it causes that interupt to occur and a block of code is executed.
This block of code configures a timer that will cause an interupt after 2000-1 clock cycles divided by 2 and the interupt for the button is disabled.
When the interupt for the timer is called the interupt for the button is enabled allowing it to recive an input from the user again.

## Differences between boards
Some boards with FR require high impedence on a pin to be disabled.

## Implementing
Run the code using a C compiler and put into an MSP430. Press the button and it will recive a debounced input! If you want to use this
on your own code you may paste the buttons functionality inside of the buttons interuptunderneath all the existing code.
