/*!
 * @file TFTSevenSegmentClockDisplay.h
 *
 * This is part of for TFTSevenSegment library
 *
 *
 * Written by Enrique Albertos, with
 * contributions from the open source community.
 *
 * Public Domain
 *
 */

#ifndef _TFTSevenSegmentClockDisplay_H_
#define _TFTSevenSegmentClockDisplay_H_

#include "arduino.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "TFTSevenSegmentModule.h"

#define DIGITS 6 // number of seven segment modules


class TFTSevenSegmentClockDisplay {


  public:
    TFTSevenSegmentClockDisplay(Adafruit_TFTLCD * , int16_t , int16_t , int16_t , int16_t , uint16_t , uint16_t , int16_t , boolean, float );
    void display(int16_t ,  int16_t , int16_t, boolean );
    void displaySeconds(long, boolean );
    void displayMillis(long, boolean );
    void setPosition(int16_t , int16_t );
    void setOnColor(uint16_t );
    void setOffColor(uint16_t );
    void setLedWidth(int16_t  );
    void setSegmentWidth(int16_t  );
    void setSegmentHeight(int16_t );
    int16_t getSegmentWidth( ) ;
    int16_t getSegmentHeight();

  private:
    Adafruit_TFTLCD * m_tft;
    int16_t m_x{};
    int16_t m_y{};
    int16_t m_w{};
    int16_t m_h{};
    uint16_t m_onColor{};
    uint16_t m_offColor{};
    int16_t m_ledWidth{};
    boolean m_showHours{};
    float m_secondsHeightRatio{};
    TFTSevenSegmentModule* digits[DIGITS];
    enum Unit { HH1 = 0, HH2 , MM1, MM2, SS1, SS2};


};

#endif // _TFTSevenSegmentClockDisplay_H_
