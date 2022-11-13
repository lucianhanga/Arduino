#include "Arduino.h"
#include "KeypadNumber.h"


KeypadNumber::KeypadNumber(uint32_t defaultValue = 0) {
    this->number = defaultValue;
    memset(this->numberInForming, 0x00, MAX_FORMING_NUMBER_STRING);
  };

// check out later if the C++11 The Big 5 rule should be visited
// Destructor; Copy Constructor; Assignment Operator; Move Copy Constructor; Move Assignment Operator
bool KeypadNumber::addDigitASCII(char digitASCII) {
    if(digitASCII < '0' || digitASCII > '9')
      // bad ASCII code for a digit 
      return false;
    // the ASCII code is correct.
    // check if there is more space for this digit
    uint32_t strSize = strlen(numberInForming);
    if(strSize >= MAX_FORMING_NUMBER_STRING-1)
      // there are too many digits
      return false;
    this->numberInForming[strSize] = digitASCII;
    this->numberInForming[strSize+1] = 0x00; // end of string
}

bool KeypadNumber::endNumber() {
    uint32_t strSize = strlen(this->numberInForming);
    if(strSize == 0)
      return false; // no character was introduced
    uint32_t tempNumber = 0;
    for(int i=0; i< strSize; i++) {
      if(tempNumber > 0xFFFFFFFF/10) {
        // the number will overflow - see maybe here, replace the code with MAX_INT value
        return false;
      }
      tempNumber = tempNumber*10 + this->numberInForming[i]-'0';
    }
    // if you got here it means that is all good 
    // now - replace the number with the temp one 
    this->number = tempNumber;
    this->cleanNumber();
    return true;
}

void KeypadNumber::cleanNumber() {
     memset(this->numberInForming, 0x00, MAX_FORMING_NUMBER_STRING);   
}
uint32_t KeypadNumber::get() {
    return this->number;
}
const char * KeypadNumber::getNumber() {
    return this->numberInForming;
}


