/*
   install :

   Sketch->Include Library->Manage Libraries... Then search for Keypad.
   https://playground.arduino.cc/Code/Keypad/


*/
//#include <iostream>

#include <Key.h>
#include <Keypad.h>
#include <KeypadNumber.h>

const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[rows] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[cols] = {6, 5, 4, 3 }; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols ); 

/* 
  important: 
  c++ version supported by the avg-gcc is C++ 11 
  how to determine the vesion: 
  
  Serial.println(__cplusplus); // --> 201103L

  C++ pre-C++98: __cplusplus is 1.
  C++98: __cplusplus is 199711L.
  C++98 + TR1: This reads as C++98 and there is no way to check that I know of.
  C++11: __cplusplus is 201103L.
  C++14: __cplusplus is 201402L.
  C++17: __cplusplus is 201703L.
  C++20: __cplusplus is 202002L.

*/

KeypadNumber kn(0);

void keypadFormNumbersEvent(KeypadEvent key) {
  //Serial.println("callback ...");
  // the event is called for all : PRESSED, RELEASED, HOLD - so make 
  // sure that you just get the key once
  if(keypad.getState() == PRESSED) {
    //Serial.println("callback PRESSED.");
    if(key == '#')  {
      // finalize the number
      if(!kn.endNumber())
        kn.cleanNumber();
      Serial.print("Number: ");
      Serial.println(kn.get());
    } else {
      kn.addDigitASCII(key);
      Serial.print("NumberInForming: ");
      Serial.println(kn.getNumber());
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting ...");
  delay(200);
  keypad.addEventListener(keypadFormNumbersEvent);
}


void loop() {
  keypad.getKey(); // IMPORTANT - this has to be called, because otherwise the callback is not called
}

