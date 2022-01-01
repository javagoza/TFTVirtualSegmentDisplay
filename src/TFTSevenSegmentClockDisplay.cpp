#include "TFTSevenSegmentClockDisplay.h"

TFTSevenSegmentClockDisplay::TFTSevenSegmentClockDisplay(
  Adafruit_TFTLCD* tft,
  int16_t x = 0,
  int16_t y = 0,
  int16_t w = 16,
  int16_t h = 32,
  uint16_t onColor = 255, 
  uint16_t offColor = 0, 
  int16_t ledWidth = 3,
  boolean showHours = true,
  float secondsHeightRatio = 3/4):
    m_tft{tft},
    m_x{x},
    m_y{y},
    m_w{w},
    m_h{h},
    m_onColor{onColor},
    m_offColor{offColor},
    m_ledWidth{ledWidth},
    m_showHours{showHours},
    m_secondsHeightRatio{secondsHeightRatio} {
    
  int groupOffset = 0;
  int digit = 0;
  int offsetx;
  for (int i = m_showHours ? 0 : 2; i < DIGITS; i++) {
    
    if(i < SS2 ){
       offsetx = digit * (w + w / 8 + 3) + groupOffset;
    } else {
      offsetx = offsetx + (w  + w / 8 )* m_secondsHeightRatio + 3;
    }
    digits[i] = new TFTSevenSegmentModule(tft, x + offsetx , y, w, h, m_onColor, m_offColor, m_ledWidth, true);
    ++digit;
    if (i % 2 != 0) {
      groupOffset += w / 2;
    }
  }
  digits[SS1]->setHeight((float)h * m_secondsHeightRatio);
  digits[SS2]->setHeight((float)h * m_secondsHeightRatio);
  digits[SS1]->setWidth((float)w * m_secondsHeightRatio);
  digits[SS2]->setWidth((float)w * m_secondsHeightRatio);
}

#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MILLIS_IN_SECOND 1000

void TFTSevenSegmentClockDisplay::displaySeconds(long timeSeconds, boolean isSeparatorOn) {
  display((timeSeconds / (SECONDS_IN_MINUTE * MINUTES_IN_HOUR)) % HOURS_IN_DAY,
   (timeSeconds / SECONDS_IN_MINUTE) % MINUTES_IN_HOUR,
    timeSeconds % SECONDS_IN_MINUTE, isSeparatorOn);
}

void TFTSevenSegmentClockDisplay::displayMillis(long timeMillis, boolean isSeparatorOn) {
  displaySeconds(timeMillis / MILLIS_IN_SECOND, isSeparatorOn);
}

void TFTSevenSegmentClockDisplay::display(int16_t hours, int16_t minutes, int16_t seconds, boolean isSeparatorOn) {

  if (minutes > 9 || m_showHours) {
    digits[MM1]->on();
    digits[MM1]->display((minutes / 10) % 10);
  } else {
    digits[MM1]->off();
    digits[MM1]->display(0);
  }

  digits[MM2]->display(minutes % 10);

  digits[SS1]->display((seconds / 10) % 10);

  digits[SS2]->display(seconds % 10);

  if (m_showHours) {
    if (hours > 9) {
      digits[HH1]->on();
      digits[HH1]->display((hours / 10) % 10);
    } else {
      digits[HH1]->off();
      digits[HH1]->display(0);
    }


    digits[HH2]->display(hours % 10);
    
    m_tft->fillCircle(digits[HH2]->getX() + digits[HH2]->getWidth() + (digits[MM1]->getX() - (digits[HH2]->getX() + digits[HH2]->getWidth())) / 2,
                      digits[HH2]->getY() + digits[MM1]->getHeight() / 4,
                      m_ledWidth/ 2,
                      isSeparatorOn == true? m_onColor:m_offColor);

    m_tft->fillCircle(digits[HH2]->getX()
                      + digits[HH2]->getWidth() + (digits[MM1]->getX() - (digits[HH2]->getX() + digits[HH2]->getWidth())) / 2,
                      digits[HH2]->getY() + 3 * digits[MM1]->getHeight() / 4,
                      m_ledWidth/ 2,
                      isSeparatorOn == true? m_onColor:m_offColor);

    m_tft->fillCircle(digits[MM2]->getX() + digits[MM2]->getWidth() + (digits[SS1]->getX() - (digits[MM2]->getX() + digits[MM2]->getWidth())) / 2,
                      digits[MM2]->getY() + digits[SS1]->getHeight() / 4,
                      m_ledWidth/ 2,
                      isSeparatorOn == true? m_onColor:m_offColor);

    m_tft->fillCircle(digits[MM2]->getX()
                      + digits[MM2]->getWidth() + (digits[SS1]->getX() - (digits[MM2]->getX() + digits[MM2]->getWidth())) / 2,
                      digits[MM2]->getY() + 3 * digits[SS1]->getHeight() / 4,
                      m_ledWidth/ 2,
                      isSeparatorOn == true? m_onColor:m_offColor);
  }
}




void TFTSevenSegmentClockDisplay::setPosition(int16_t x, int16_t y) {
  m_x = x;
  m_y = y;
}
void TFTSevenSegmentClockDisplay::setOnColor(uint16_t color) {
  for (int i = 0; i < DIGITS; i++) {
    digits[i]->setOnColor(color);
  }
  m_onColor = color;
}
void TFTSevenSegmentClockDisplay::setOffColor(uint16_t color) {
  for (int i = 0; i < DIGITS; i++) {
    digits[i]->setOffColor(color);
  }
  m_offColor = color;
}
void TFTSevenSegmentClockDisplay::setLedWidth(int16_t ledWidth) {
  for (int i = 0; i < DIGITS; i++) {
    digits[i]->setLedWidth(ledWidth);
  }
  m_ledWidth = ledWidth;
}
void TFTSevenSegmentClockDisplay::setSegmentWidth(int16_t w) {
  m_w = w;
}
void TFTSevenSegmentClockDisplay::setSegmentHeight(int16_t h) {
  m_h = h;
}

int16_t TFTSevenSegmentClockDisplay::getSegmentWidth() {
  return -1;
}
int16_t TFTSevenSegmentClockDisplay::getSegmentHeight() {
  return -1;
}
