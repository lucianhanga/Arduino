#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <LCDAnimatedBar.h>

//
// to keep the implementation of the LCDAnimatedBar independent of the LCD library
// this function has to be kept here 
//
static void createChars(hd44780_I2Cexp &llcd) {
for ( int i = 0; i < (int)LCDAnimatedBar::charBitmapSize; i++ )
		llcd.createChar ( i, (uint8_t *)LCDAnimatedBar::charBitmap[i] );
	// must do something like set cursor postion after defining chars - on most libraries (not hd44780) to reset address back to display ram
	llcd.setCursor(0,0);
}

hd44780_I2Cexp lcd(0x27);
LCDAnimatedBar bar1(0,0,0);

// the callback function which displays the characters 
// also to keep it independent from the impementation this 
// callback is required
void displayBarOnLcd(uint8_t col, uint8_t line, uint8_t value) {
  lcd.setCursor(col, line);
  lcd.write(char(value));
}

void setup() {
  Serial.begin(9600);
  int status = lcd.begin(16, 2);
  if(status != 0) {
    Serial.print("LCD initialization error: ");
    Serial.println(status);
    hd44780::fatalError(status); // Arduino LED error indicator
  }
  Serial.println("LCD initialization done.");
  // create the characters in the LCD Display
  createChars(lcd);
  LCDAnimatedBar::setCallback(displayBarOnLcd);
  bar1.show();

}

void loop() {
  bar1.update();
  delay(100);
}
