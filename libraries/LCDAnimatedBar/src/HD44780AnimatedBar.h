#ifndef __HD44780_ANIMATED_BAR_H__
#define __HD44780_ANIMATED_BAR_H__

#include <Arduino.h>
#include <hd44780.h>
#include <Wire.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "LCDAnimatedBar.h"

class HD44780AnimatedBar : public LCDAnimatedBar {
    // public types
    public: 
        typedef enum {
            BAR_rowS = 0,
            BAR_NEEDELS = 1,
            BAR_BUBBLES = 2,
            BAR_MORE_BUBBLES = 3
        } bar_type_t;


    // initialize the class static variables
    public:
        static void init( hd44780_I2Cexp& llcd,  HD44780AnimatedBar::bar_type_t barType = BAR_rowS);

    // protected/private data - arrays with character definitions
    protected:
        static const uint8_t  charBarrowsBitmap[][8];
        static const uint8_t  charBarNeedlesBitmap[][8];
        static const uint8_t  charBarBubblesBitmap[][8];
        static const uint8_t  charBarMoreBubblesBitmap[][8];
        static hd44780_I2Cexp* lcd;

    public:
        HD44780AnimatedBar( uint8_t col = 0,  uint8_t row = 0, 
                            uint8_t value = 0,  uint8_t start_value = 0, uint8_t end_value = 7);

    private:
        static void displayBarOnLcd(uint8_t col, uint8_t row, uint8_t value);
        static void createChars(HD44780AnimatedBar::bar_type_t barType);


};

#endif // !#defined(__HD44780_ANIMATED_BAR_H__)