#include <avr/io.h>
#include <avr/interrupt.h>
// This code is for the ATmega328P

// This code uses Timer1 and External Interrupt INT0
// Timer1 is used to measure the time between the two signals
// External Interrupt INT0 is used to capture the timer value when the signal is received

// Global Variables:
//
// startTime and endTime
//     store the timer values when the rising edges occur.
//     Used to calculate the time difference between the two signals.
//
// signalCount: 
//     Used to distinguish between the first and second signal.
//     0 = first signal, 1 = second signal
//
// overflowCount: Used to keep track of the number of times the timer overflows.
//     The timer overflows after 65536 clock cycles.
//     This means the timer overflows after 65536 * 1/16,000,000 seconds = 0.004096 seconds
//
// Volatile because it's used in an ISR (Interrupt Service Routine)
//
volatile uint16_t startTime = 0; 
volatile uint16_t endTime = 0;
volatile uint8_t signalCount = 0;
volatile uint16_t overflowCount = 0;

// setupTimer1() Function:
//     Initializes Timer1 in normal mode without any prescaler.
//     This means the timer will increment its value with each clock cycle.
//     The timer will overflow after 65536 clock cycles.
//     a clock cycle is 1/16,000,000 seconds. (depending on the clock speed which is 16MHz for the ATmega328P)
//     So the timer will overflow after 65536 * 1/16,000,000 seconds = 0.004096 seconds
//  
//     also enables Timer1 overflow interrupt to account for the overflow
//     when the timer overflows, the overflow interrupt will be triggered
//     and the overflowCount variable will be incremented
//
//      TCCR1B is the Timer/Counter1 Control Register B
//      TIMSK1 is the Timer/Counter1 Interrupt Mask Register
//      CS10 is bit 0 of TCCR1B  - Clock Select - Prescaler
//      TOIE1 is bit 0 of TIMSK1 - Timer/Counter1 Overflow Interrupt Enable
//
void setupTimer1() {
    // Set Timer1 to normal mode (no prescaler)
    TCCR1B |= (1 << CS10);
    
    // Enable Timer1 overflow interrupt
    TIMSK1 |= (1 << TOIE1);
}

// setupExternalInterrupt() Function:
//    Initializes External Interrupt INT0 on pin PD2
//    This interrupt is triggered when a rising edge is detected on pin PD2
// 
//    EICRA is the External Interrupt Control Register A
//    EIMSK is the External Interrupt Mask Register
//    ISC01 and ISC00 are bits 1 and 0 of EICRA
//    INT0 is bit 0 of EIMSK - External Interrupt Request 0 Enable - INT0
//
void setupExternalInterrupt() {
    // Enable external interrupt INT0 on rising edge
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
}

// Timer1 overflow interrupt service routine
// This is called when the timer overflows
// The ISR is used to increment the overflowCount variable
// 
ISR(TIMER1_OVF_vect) {
    overflowCount++;
}

// External Interrupt INT0 service routine
// This is called when a rising edge is detected on pin PD2
// meaning that a signal was received at pin PD2
// The ISR is used to capture the timer value when the rising edge occurs
// 
ISR(INT0_vect) {
    // if is the first signal
    if (signalCount == 0) {
        startTime = TCNT1;  // Capture the current timer value
        overflowCount = 0;  // Reset overflow counter on first signal
        signalCount++;
        // if is the second signal
    } else if (signalCount == 1) {
        endTime = TCNT1;  // Capture the current timer value
        signalCount = 0;  // Reset for the next pair of signals
    }
}

// Main Function:
//    Initializes Timer1 and External Interrupt INT0
//    Enables global interrupts
//    Loops forever
// 
int main(void) {
    setupTimer1();
    setupExternalInterrupt();

    // Enable global interrupts
    sei();

    while (1) {
        // You can use (endTime + (overflowCount * 65536)) - startTime 
        // to get the total time difference between the two signals

        // also plase take in mind that this works for two consecutive signals then is resets
        // and waits for another two consecutive signals to calculate the time difference

        // if you want to have it woking in a rolling fashion you need to add a flag to the ISR
        // and use it to calculate the time difference between the two signals
        // and then reset the flag and the startTime and endTime variables
        // and so on ...
    }

    return 0;
}
