#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TFTSevenSegmentClockDisplay.h>


// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TFTSevenSegmentClockDisplay clockDisplayD(&tft,  120,  0,  9,   12,  YELLOW, tft.color565(20,20,20),   1, true,1);
TFTSevenSegmentClockDisplay clockDisplayW(&tft,  0,  0,  13,   24,  BLUE, tft.color565(20,20,20),   2, true,1);
TFTSevenSegmentClockDisplay clockDisplayB(&tft,  0,  30,  26,   48,  RED, tft.color565(20,20,20),   4, false ,1);
TFTSevenSegmentClockDisplay clockDisplayA(&tft,  0,  50,  40,   64, WHITE, tft.color565(20,20,20),   6, true,3.0/4.0);
TFTSevenSegmentClockDisplay clockDisplayC(&tft,  0,  120,  48,   110, CYAN, tft.color565(20,20,20),   8, false,.60);
void setup() {
  // put your setup code here, to run once:

  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);

  tft.fillScreen(BLACK);

}
long a = 0;
boolean toggleSeparator= false;
void loop() {
   showHorizontalClocks();
   showVerticalClocks();
}

void showHorizontalClocks() {
   tft.fillScreen(BLACK);
  for(int i = 1; i < 180; i++) {
    tft.setRotation(0);
    clockDisplayD.displaySeconds(a,toggleSeparator);
    clockDisplayB.displaySeconds(a,toggleSeparator);
    clockDisplayW.displaySeconds(86400-a,toggleSeparator);
    clockDisplayC.displaySeconds(86400-a,toggleSeparator);
    toggleSeparator = !toggleSeparator;
    a++;
    delay(10);
  }
}


void showVerticalClocks() {
   tft.fillScreen(BLACK);
  for(int i = 1; i < 180; i++) {
    tft.setRotation(1);
    clockDisplayD.displaySeconds(a,toggleSeparator);
    clockDisplayW.displaySeconds(a,toggleSeparator);
    clockDisplayA.displaySeconds(86400-a,toggleSeparator);
    clockDisplayC.displaySeconds(86400-a,toggleSeparator);
    toggleSeparator = !toggleSeparator;
    a++;
    delay(10);
  }
}
