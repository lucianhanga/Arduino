/*
HARDWARE INTERRUPTS

- You cannot overlap interruptions on Arduino, 
  so if there is an interruption in process all others will be ignored.
- You cannot use functions such as Serial, delay, millis … 
  or others that depend on interruptions or timers.
 
- It is always advisable to define the global variables that we are going to use as volatile, 
  since otherwise strange problems could occur.

 - It is important to end the interruption as soon as possible.

- You can only configure one type of interruption per pin, 
  or at least when I put two together I ignored the first one.

*/
#define BUTTON_PIN 2

void buttonInterrupServiceRoutineGeneric(){
  // If no wardware debounce do the software debounce 
  Serial.println("Button state changed.");
}
void buttonInterrupServiceRoutineOnPress() {
  // If no wardware debounce do the software debounce 
  Serial.println("Button pressed.");
}
void buttonInterrupServiceRoutineOnRelease() {
  // If no wardware debounce do the software debounce 
  Serial.println("Button released.");
}

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("Starting ...");

  pinMode(BUTTON_PIN, INPUT); // don't forget the pull-down resitor
  //
  // digitalPinToInterrupt(BUTTON_PIN)
  //  pin 2 - INT0 - value 0
  //  pin 3 - INT1 - value 1
  //
  //attachInterrupt( digitalPinToInterrupt(BUTTON_PIN), buttonInterrupServiceRoutineGeneric, CHANGE); // when the button is pressed or released
  attachInterrupt( digitalPinToInterrupt(BUTTON_PIN), buttonInterrupServiceRoutineOnPress, RISING); // when the button is pressed 
  //attachInterrupt( digitalPinToInterrupt(BUTTON_PIN), buttonInterrupServiceRoutineOnRelease, FALLING); // when the button released

}

void loop() {

}
