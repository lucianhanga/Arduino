#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

#include <HD44780AnimatedBar.h>
#include <LCDAnimatedBar.h>

hd44780_I2Cexp lcd;
HD44780AnimatedBar bar1(0,0,0);
HD44780AnimatedBar bar2(3,0,3);
HD44780AnimatedBar bar3(4,0,7);

void setup() {
  Serial.begin(9600);
  int status;
  if(status = lcd.begin(20, 4) != 0) {
    Serial.print("lcd1 initialization error: ");
    Serial.println(status);
    hd44780::fatalError(status); // Arduino LED error indicator
  }
  Serial.println("lcd initialization done.");
  // select the type of bars -- need to find a way to do it automaticaly
  // with one value
  HD44780AnimatedBar::init(lcd);
  bar1.show();
  bar2.show();
  bar3.show();
}

void loop() {
    bar1.update();
    bar2.update();
    bar3.update();
    delay(100);
}
