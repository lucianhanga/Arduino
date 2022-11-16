#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

const int LCD_ROWS = 4;
const int LCD_COLS = 20;

hd44780_I2Cexp lcd1(0x23);
hd44780_I2Cexp lcd2(0x27);

void setup() {
   Serial.begin(9600);
  int status;
  if(status = lcd1.begin(20, 4) != 0) {
    Serial.print("lcd1 initialization error: ");
    Serial.println(status);
    hd44780::fatalError(status); // Arduino LED error indicator
  }
  Serial.println("lcd1 initialization done.");

  if(status = lcd2.begin(20, 4) != 0) {
    Serial.print("lcd2 initialization error: ");
    Serial.println(status);
    hd44780::fatalError(status); // Arduino LED error indicator
  }
  Serial.println("lcd2 initialization done.");


}

void loop() {
}

