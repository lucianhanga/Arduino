// I2C_hello_world_20x4_LCD_basic
// public domain
// hd44780 library by Bill Perry

#include <Wire.h>

#include <hd44780.h> // include hd44780 library header file
#include <hd44780ioClass/hd44780_I2Cexp.h> // i/o expander/backpack class

hd44780_I2Cexp lcd; // auto detect backpack and pin mappings

void setup() {

lcd.begin(20,4); //initialize the lcd
lcd.clear();

}

void loop () {

lcd.setCursor(2,1); // start on third position of the second line of the display
lcd.print("Hello");
lcd.setCursor(10,2); // start on the eleventh position of the third line of the display
lcd.print("World!");
delay (1000);

for (int j=0; j<4; j++){
lcd.setCursor(00,j);
lcd.clear(); // clears the line where the cursor is positioned
}

delay(500);

}