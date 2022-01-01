/*!
 * @file TFTSevenSegmentModule.h
 *
 * This is part of for TFTSevenSegment library
 *
 *
 * Written by Enrique Albertos, with
 * contributions from the open source community.
 *
 * This code is in the public domain.
 *
 */


#include "arduino.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library



class TFTSevenSegmentModule {
  private:
    Adafruit_TFTLCD * m_tft;
    int16_t m_x;
    int16_t m_y;
    int16_t m_w;
    int16_t m_h;
    uint16_t m_onColor;
    uint16_t m_offColor;
    int16_t m_ledWidth;
    void draw_F_LeftUpperLed(uint16_t ) ;
    void draw_E_LeftBottomLed(uint16_t ) ;
    void draw_B_RightUpperLed(uint16_t );
    void draw_C_RightBottomLed(uint16_t ) ;
    void draw_A_UpperLed(uint16_t );
    void draw_G_MiddleLed(uint16_t );
    void draw_D_BottomLed(uint16_t ) ;

  public:
    TFTSevenSegmentModule(Adafruit_TFTLCD * , int16_t , int16_t , int16_t, int16_t, uint16_t , uint16_t , int16_t, boolean );
    void display(int16_t digit);
    void setPosition( int16_t ,  int16_t );
    void setOnColor( uint16_t );
    void setOffColor( uint16_t );
    void setLedWidth( int16_t  );
    void setWidth( int16_t  );
    void setHeight( int16_t );
    void setTft(Adafruit_TFTLCD * );
    void on();
    void off();
    int16_t getX();
    int16_t getY();
    int16_t getWidth();
    int16_t getHeight();
    boolean m_on;

};
