
#include "TFTSevenSegmentModule.h"

// The codes below indicate which segments must be illuminated to display
// each number.
const unsigned char digitCodeMap[] = {
  //     GFEDCBA  Segments      7-segment map:
  B00111111,  // 0   "0"          AAA
  B00000110,  // 1   "1"         F   B
  B01011011,  // 2   "2"         F   B
  B01001111,  // 3   "3"          GGG
  B01100110,  // 4   "4"         E   C
  B01101101,  // 5   "5"         E   C
  B01111101,  // 6   "6"          DDD
  B00000111,  // 7   "7"
  B01111111,  // 8   "8"
  B01101111   // 9   "9"
};

TFTSevenSegmentModule::TFTSevenSegmentModule(Adafruit_TFTLCD* tft, int16_t x = 0, int16_t y = 0, int16_t w = 16, int16_t h = 32, uint16_t onColor = 0, uint16_t offColor = 0, int16_t ledWidth = 3, boolean on = true)
  : m_tft{tft}, m_x{x}, m_y{y}, m_w{w}, m_h{h}, m_onColor{onColor}, m_offColor{offColor}, m_ledWidth{ledWidth}, m_on{on} {};


void TFTSevenSegmentModule::display(const int16_t digit) {
  const byte leds = digitCodeMap[digit];
  draw_A_UpperLed((leds & 1) && m_on ? m_onColor : m_offColor);
  draw_B_RightUpperLed((leds & 2)&& m_on ? m_onColor : m_offColor);
  draw_C_RightBottomLed((leds & 4)&& m_on ? m_onColor : m_offColor);
  draw_D_BottomLed((leds & 8) && m_on? m_onColor : m_offColor);
  draw_E_LeftBottomLed((leds & 16) && m_on ? m_onColor : m_offColor);
  draw_F_LeftUpperLed((leds & 32) && m_on ? m_onColor : m_offColor);
  draw_G_MiddleLed((leds & 64) && m_on ? m_onColor : m_offColor);
}


void TFTSevenSegmentModule::draw_F_LeftUpperLed(uint16_t color) {
  m_tft->startWrite();
  for (uint16_t i = 0; i < m_ledWidth; i++) {
    m_tft->writeFastVLine(m_x + i, m_y + i, m_h / 2 - 2 * i, color);
  }
  m_tft->endWrite();
}

void TFTSevenSegmentModule::draw_E_LeftBottomLed(uint16_t color) {
  m_tft->startWrite();
  for (uint16_t i = 0; i < m_ledWidth; i++) {
    m_tft->writeFastVLine(m_x + i, m_h / 2 + m_y + i + 1, m_h / 2 - 2 * i, color);
  }
  m_tft->endWrite();
}

void TFTSevenSegmentModule::draw_B_RightUpperLed(uint16_t color) {
  m_tft->startWrite();
  for (uint16_t i = 0; i < m_ledWidth; i++) {
    m_tft->writeFastVLine(m_x + m_w - i, m_y + i, m_h / 2 - 2 * i, color);
  }
  m_tft->endWrite();
}

void TFTSevenSegmentModule::draw_C_RightBottomLed(uint16_t color) {
  m_tft->startWrite();
  for (uint16_t i = 0; i < m_ledWidth; i++) {
    m_tft->writeFastVLine(m_x + m_w - i, m_y + m_h / 2 + i + 1, m_h / 2 - 2 * i, color);
  }
  m_tft->endWrite();
}



void TFTSevenSegmentModule::draw_G_MiddleLed(uint16_t color) {
  m_tft->startWrite();
  int ledWidth = m_ledWidth<2?1:m_ledWidth/2;
  for (uint16_t i = 0;  i < ledWidth ; i++) {
    m_tft->writeFastHLine(m_x + i + 2, m_y + m_h / 2 - i, m_w - 2 * i - 4, color);
    if (m_ledWidth>1){
      m_tft->writeFastHLine(m_x + i + 2, m_y + m_h / 2 + i + 1, m_w - 2 * i - 4, color);
    }
  }
  m_tft->endWrite();
}

void TFTSevenSegmentModule::draw_A_UpperLed(uint16_t color) {
  m_tft->startWrite();
  for (uint16_t i = 0; i < m_ledWidth; i++) {
    m_tft->writeFastHLine(m_x + i + 3, m_y + i, m_w - 2 * i - 5, color);
  }
  m_tft->endWrite();
}

void TFTSevenSegmentModule::draw_D_BottomLed(uint16_t color) {
  m_tft->startWrite();
  for (uint16_t i = 0; i < m_ledWidth; i++) {
    m_tft->writeFastHLine(m_x + i + 3, m_y + m_h - i, m_w - 2 * i - 5, color);
  }
  m_tft->endWrite();
}

void TFTSevenSegmentModule::setPosition(int16_t x, int16_t y) {
  m_x = x;
  m_y = y;
}
void TFTSevenSegmentModule::setOnColor(uint16_t color) {
  m_onColor = color;
}
void TFTSevenSegmentModule::setOffColor(uint16_t color) {
  m_offColor = color;
}
void TFTSevenSegmentModule::setLedWidth(int16_t ledWidth) {
  m_ledWidth = ledWidth;
}
void TFTSevenSegmentModule::setWidth(const int16_t w) {
  m_w = w;
}
void TFTSevenSegmentModule::setHeight(const int16_t h) {
  m_h = h;
}

void TFTSevenSegmentModule::setTft(Adafruit_TFTLCD* tft) {
  m_tft = tft;
}

void TFTSevenSegmentModule::on() {
  m_on = true;
}

void TFTSevenSegmentModule::off() {
  m_on = false;
}

int16_t TFTSevenSegmentModule::getX() {
  return m_x;
}
int16_t TFTSevenSegmentModule::getY() {
  return m_y;
}
int16_t TFTSevenSegmentModule::getWidth() {
  return m_w;
}
int16_t TFTSevenSegmentModule::getHeight() {
  return m_h;
}
