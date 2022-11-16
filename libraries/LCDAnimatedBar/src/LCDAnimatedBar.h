#ifndef __LCD_ANIMATED_BAR_H__
#define __LCD_ANIMATED_BAR_H__

#include <Arduino.h>

class LCDAnimatedBar {
// types
public:
    // they call of the callback function which prints a character
    // on the screen. The parameters are in order:
    // col, row, char
    typedef void(* callback_t)(uint8_t, uint8_t, uint8_t);

// public static functions and static variables
public:
    static void setCallback(callback_t fCallback); // this one is not needed ... should be removed
    static const uint8_t charBitmap[][8];
    static const uint32_t charBitmapSize;
    static callback_t callback;

private:
    const uint8_t m_start_value;// the start value of the bar
    const uint8_t m_end_value;  // the end value of the bar
    uint8_t m_value;            // the current value of the bar movement
    uint8_t m_col;              // position on LCD - column
    uint8_t m_row;             // position of LCD - row
    bool m_go_up;               // direction in which the bar is moving
 
public:
    LCDAnimatedBar( uint8_t col=0,
                    uint8_t row=0, 
                    uint8_t value = 0,
                    uint8_t start_value=0, 
                    uint8_t end_value = 7);
    void setPosition(uint8_t col, uint8_t row);
    void show();
    void update();
};

#endif // !#DEFINED(__LCD_ANIMATED_BAR_H__)
