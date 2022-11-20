#include <TM1637.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

//      aaa 
//   f       b
//   f       b
//   f       b
//      ggg
//   e       c
//   e       c
//   e       c
//      ddd
//
//
//

const uint8_t SEG_DANI[] = {

  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,      // d
  SEG_E | SEG_F | SEG_A | SEG_B | SEG_C,      // A
  SEG_E | SEG_G | SEG_C,                      // n
  SEG_F | SEG_E

};

TM1637Display display(CLK, DIO);

void setup() {
    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    display.setBrightness(0x0f);
    display.setSegments(data);
    delay(2000);
    display.setSegments(SEG_DANI);
}

void loop() {
  // put your main code here, to run repeatedly:

}
