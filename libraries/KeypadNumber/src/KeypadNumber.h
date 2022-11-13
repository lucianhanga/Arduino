#ifndef __KEYPAD_NUMBER_H__
#define __KEYPAD_NUMBER_H__

#include "Arduino.h"

class KeypadNumber {

private:
  enum { MAX_FORMING_NUMBER_STRING = 11 };

  uint32_t number;             // this variable will hold the current fully formend number
  char numberInForming[MAX_FORMING_NUMBER_STRING];    // this variable will gather digits until the method of completion is called

public:
  KeypadNumber(uint32_t defaultValue = 0);

  // check out later if the C++11 The Big 5 rule should be visited
  // Destructor; Copy Constructor; Assignment Operator; Move Copy Constructor; Move Assignment Operator


  uint32_t get();

  void cleanNumber();
  const char * getNumber();
  bool addDigitASCII(char digitASCII);
  bool endNumber();

};


#endif // !DEFINED(__KEYPAD_NUMBER_H__)