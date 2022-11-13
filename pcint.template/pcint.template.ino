/*
PCINT - Pin Change INTerrupts

 - hardware interrupts (INT) are limited to certain pins depending on the Arduino model

 - The advantages of PCINT interrupts are that you can use any pin on the Arduino to trigger them.

 - Of course it has its disadvantages, and the main one is that you cannot indicate when to trigger 
   the interrupt as you would with hardware interrupts. These will be activated whenever there is any 
   change of state on the pin, either from HIGH to LOW, or from LOW to HIGH.



Port Registers That Will Trigger Interrupts (PCICR)

- different groups of pins that there are, which are named as PB, PC and PD:
  PB port, which corresponds to the group of pins PCINT0 to PCINT5 and which are pins D8 to D13.
  PC port, which corresponds to the group of pins PCINT8 to PCINT13, corresponding to pins A0 to A5.
  PD port, which corresponds to the group of pins PCINT16 to PCINT23, corresponding to digital pins D0 to D7.

  PCICR | = B00000001; // We activate the interrupts of the PB port
  PCICR | = B00000010; // We activate the interrupts of the PC port
  PCICR | = B00000100; // We activate the interrupts of the PD port

  Once the port in which we want to generate the interrupts is activated, 
  we will also have to activate which pin of that port will generate said interrupts,


Pin registers that will trigger interrupts (PCMSK)

  Once we have activated the port (s) that we want to trigger interrupts, 
  it is time to indicate which pins of those ports will do it. 
  This is done through the PCMSK registers, of which we have one per port (PCMSK0, PCMSK1 and PCMSK2). 
  The correspondence between ports and registers is:

  PCMSK0 -> PB -> D8 to D13 pins
  PCMSK1 -> PC -> A0 to A5 pins
  PCMSK2 -> PD -> D0 to D7 pins

  e.g. 
  PCMSK0 |= B00000100; // We activate the interrupts on pin D10
  PCMSK1 |= B00001000; // We activate the interrupts on pin A3

Generate Events (ISR PCINT Vect)

  PCINT0_vect -> PB -> Pines D8 a D13
  PCINT1_vect -> PC -> Pines A0 a A5
  PCINT2_vect-> PD -> Pines D0 a D7

*/

#define BUTTON_PIN 2

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("Starting ...");
  pinMode(BUTTON_PIN, INPUT); // don't forget the pull-down resitor

  PCICR |= B00000100; // Enable interrupts on PD port
  PCMSK2 |= B00000100; // Trigger interrupts on pins D2
}


void loop() {

}

ISR(PCINT2_vect) {
  Serial.println("Button was pressed.");
  // don't forget to take care of debounceing
}

