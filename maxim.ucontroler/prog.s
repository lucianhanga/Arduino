.include "m328pdef.inc" ; Include the ATmega328P definitions file

.def startTime = r16 ; Define the start time register
.def endTime = r17 ; Define the end time register
.def signalCount = r18 ; Define the signal count register
.def overflowCount = r19 ; Define the overflow count register

.cseg ; Code segment

; Initialize Timer1 in normal mode without any prescaler
; Enable Timer1 overflow interrupt
setupTimer1:
    ldi r20, (1 << CS10) ; Set Timer1 to normal mode (no prescaler)
    out TCCR1B, r20 ; Write to Timer/Counter1 Control Register B
    ldi r20, (1 << TOIE1) ; Enable Timer1 overflow interrupt
    out TIMSK1, r20 ; Write to Timer/Counter1 Interrupt Mask Register
    ret ; Return from function

; Initialize External Interrupt INT0 on pin PD2
; Enable external interrupt INT0 on rising edge
setupExternalInterrupt:
    ldi r20, (1 << ISC01) | (1 << ISC00) ; Enable external interrupt INT0 on rising edge
    out EICRA, r20 ; Write to External Interrupt Control Register A
    ldi r20, (1 << INT0) ; Enable External Interrupt Request 0 Enable - INT0
    out EIMSK, r20 ; Write to External Interrupt Mask Register
    ret ; Return from function

; Timer1 overflow interrupt service routine
; Increment the overflowCount variable
TIMER1_OVF_vect:
    inc overflowCount ; Increment the overflow count
    reti ; Return from interrupt

; External Interrupt INT0 service routine
; Capture the timer value when a rising edge is detected on pin PD2
INT0_vect:
    ; If it's the first signal
    cpi signalCount, 0
    breq firstSignal
    ; If it's the second signal
    cpi signalCount, 1
    breq secondSignal
    reti ; Return from interrupt

firstSignal:
    in startTime, TCNT1 ; Capture the current timer value
    clr overflowCount ; Reset overflow counter on first signal
    inc signalCount ; Increment signal count
    reti ; Return from interrupt

secondSignal:
    in endTime, TCNT1 ; Capture the current timer value
    clr signalCount ; Reset for the next pair of signals
    reti ; Return from interrupt

; Main function
; Initialize Timer1 and External Interrupt INT0
; Enable global interrupts
; Loop forever
main:
    call setupTimer1 ; Initialize Timer1
    call setupExternalInterrupt ; Initialize External Interrupt INT0
    sei ; Enable global interrupts
loop:
    ; You can use (endTime + (overflowCount * 65536)) - startTime 
    ; to get the total time difference between the two signals
    ; Also, note that this works for two consecutive signals then it resets
    ; and waits for another two consecutive signals to calculate the time difference
    ; If you want to have it working in a rolling fashion, you need to add a flag to the ISR
    ; and use it to calculate the time difference between the two signals
    ; and then reset the flag and the startTime and endTime variables
    ; and so on ...
    rjmp loop ; Jump to loop forever
    