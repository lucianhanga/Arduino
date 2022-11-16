#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>


class AnimatedBar {
  public:
    typedef void(* callback_t)(uint8_t, uint8_t, uint8_t); 

  public:
    static const uint8_t charBitmap[][8];
    static const uint32_t charBitmapSize;
    static void createChars(hd44780_I2Cexp& lcd);
    static void setDefaultCallback(callback_t fdefaultCallback);
    static callback_t defaultCallback;

  private:
    uint8_t m_start_value;
    uint8_t m_end_value;
    uint8_t m_value;
    uint8_t m_col;
    uint8_t m_line;

    bool m_go_up;
  public:
    AnimatedBar(uint8_t col=0, uint8_t line=0, uint8_t value = 0, uint8_t start_value=0, uint8_t end_value = 7) :
      m_col(col),
      m_line(line),
      m_start_value(start_value),
      m_end_value(end_value),
      m_value(value),
      m_go_up(true) {
      };
    void setPosition(uint8_t col, uint8_t line) {
      m_col = col;
      m_line = line;
    };
    void show() {
      if(defaultCallback)
        defaultCallback(m_col, m_line, m_value);
    }
    void update() {
      if(m_go_up == true) { // going up
        if( m_value < m_end_value ) {
          m_value++;
        } else {
          m_value--;
          m_go_up = false;
        }
      } else { // going down
        if( m_value > m_start_value ) {
          m_value--;
        } else {
          m_value++;
          m_go_up = true;
        }
      }
      if(defaultCallback)
        defaultCallback(m_col, m_line, m_value);
    }
};

// static const uint8_t AnimatedBar::charBitmap[][8] = {
// 	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f}, // char 0 
// 	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f}, // char 1
// 	{0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f}, // char 2
// 	{0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f}, // char 3
// 	{0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 4
// 	{0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 5
// 	{0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 6
// 	{0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}, // char 7
// };
static const uint8_t AnimatedBar::charBitmap[][8] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8, 0x8}, // char 0 
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8, 0x8}, // char 1
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x8, 0x8, 0x8}, // char 2
	{0x00, 0x00, 0x00, 0x00, 0x8, 0x8, 0x8, 0x8}, // char 3
	{0x00, 0x00, 0x00, 0x8, 0x8, 0x8, 0x8, 0x8}, // char 4
	{0x00, 0x00, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8}, // char 5
	{0x00, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8}, // char 6
	{0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8}, // char 7
};
static const uint32_t AnimatedBar::charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
static AnimatedBar::callback_t AnimatedBar::defaultCallback = NULL;

static void AnimatedBar::createChars(hd44780_I2Cexp &llcd) {
for ( int i = 0; i < charBitmapSize; i++ ) {
		llcd.createChar ( i, (uint8_t *)charBitmap[i] );
	}
	// must do something like set cursor postion after defining chars
	// on most libraries (not hd44780)
	// to reset address back to display ram
	llcd.setCursor(0,0);
}

static void AnimatedBar::setDefaultCallback(callback_t fdefaultCallback) {
  // create the characters 
  AnimatedBar::defaultCallback = fdefaultCallback;
}


hd44780_I2Cexp lcd;

void DisplayIt(uint8_t col, uint8_t line, uint8_t value) {
  Serial.print("[ col = ");
  Serial.print(col);
  Serial.print("; line = ");
  Serial.print(line);
  Serial.print("; value = ");
  Serial.print(value);
  Serial.println("]");
}

void DisplayIt2(uint8_t col, uint8_t line, uint8_t value) {
  // Serial.print("[ col = ");
  // Serial.print(col);
  // Serial.print("; line = ");
  // Serial.print(line);
  // Serial.print("; value = ");
  // Serial.print(value);
  // Serial.println("]");
  lcd.setCursor(col, line);
  lcd.write(char(value));
}

  AnimatedBar* bars[32];

void setup() {
  Serial.begin(9600);
  
  int status = lcd.begin(16, 2);
  if(status != 0) {
    Serial.print("LCD initialization error: ");
    Serial.println(status);
    hd44780::fatalError(status); // Arduino LED error indicator
  }
  Serial.println("LCD initialization done.");

  AnimatedBar::createChars(lcd); // create the characters
  AnimatedBar::setDefaultCallback(DisplayIt2);

  for(int i=0;i<16;i++) {
    bars[i    ] = new AnimatedBar(i,0,i%8);
    bars[i]->show();
    bars[16+i] = new AnimatedBar(i,1,(16-i)%8);
    bars[16+i]->show();
  }
}

void loop() {
  for(int i=0;i<32;i++) {
    if(bars[i])
      bars[i]->update();
  }
  delay(100);
}
