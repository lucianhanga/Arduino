#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

const uint8_t charBitmap[][8] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f}, // char 0 
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f}, // char 1
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f}, // char 2
	{0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f}, // char 3
	{0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 4
	{0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 5
	{0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 6
	{0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 7
};

const uint32_t charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));

void createChars() {
for ( int i = 0; i < charBitmapSize; i++ ) {
		lcd.createChar ( i, (uint8_t *)charBitmap[i] );
	}
	// must do something like set cursor postion after defining chars
	// on most libraries (not hd44780)
	// to reset address back to display ram
	lcd.setCursor(0,0);
}


void setup() {
  Serial.begin(9600);
  int status = lcd.begin(20, 4);
  if(status != 0) {
    Serial.print("LCD initialization error: ");
    Serial.println(status);
    hd44780::fatalError(status); // Arduino LED error indicator
  }
  lcd.clear();
  // testing the display
  lcd.setCursor(0, 0);
  lcd.print("testing line 1");
  delay(1000);
  lcd.setCursor(1, 1);
  lcd.print("testing line 2");
  delay(1000);
  lcd.setCursor(2, 2);
  lcd.print("testing line 3");
  delay(1000);
  lcd.setCursor(3, 3);
  lcd.print("testing line 4");
  delay(1000);
  // end the test1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(13, 0);
  lcd.print((float) 10.40);

  createChars();
  for(int j=0; j<10; j++) {
   lcd.setCursor(1,1);
    for(int i=0; i<8;i++) {
      lcd.setCursor(1,2);
      lcd.write(char(i));
      delay(50);
   }
    for(int i=7; i>=0;i--) {
      lcd.setCursor(1,2);
      lcd.write(char(i));
      delay(50);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
