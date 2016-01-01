/*********************************************************************
Photon cloud messages consumer connected to the SSD1306 OLED display
*********************************************************************/

#include "Adafruit_SSD1306/Adafruit_GFX.h"
#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define DELAY_TIME 50

#define LOGO16_GLCD_WIDTH  40 
#define LOGO16_GLCD_HEIGHT 34 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int y=0;
int resetNextTime = 0;

#define MAX_LINE_LENGTH 21

String CMD_RESET_DISPLAY = "%RESET_DISPLAY%";

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(500);
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,y);
  display.clearDisplay();
  Particle.subscribe("general-information", myHandler, MY_DEVICES);
}


void loop() {
  
}


void myHandler(const char *event, const char *data)
{
  String s = data;
  
  if (CMD_RESET_DISPLAY.equals(s)) {
      display.clearDisplay();
      display.display();
      y=0;
  } else {
    if (resetNextTime==1) {
      display.clearDisplay();
      display.display();
      y=0;
      resetNextTime = 0;
    }
    display.setCursor(0,y);
    display.println(data);
    display.display();
    int lines = (s.length()/MAX_LINE_LENGTH);
    y+=8*lines;
    if (y>56) {
      resetNextTime=1;  
    }
  }
}

