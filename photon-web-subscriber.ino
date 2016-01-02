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

#define MAX_LINE_LENGTH 21

String CMD_RESET_DISPLAY = "%RESET_DISPLAY%";

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

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
  } else {
    int x=0;
    int y=0;
    display.clearDisplay();
    char c;
    for (int i=0;i<s.length();++i) {
        c = s.charAt(i);
        if (c=='|') {
            x=0;
            y++;
        } else {
            display.setCursor(x*CHAR_WIDTH,y*CHAR_HEIGHT);
            display.print(c);
            x++;
            if (x>=(SSD1306_LCDWIDTH/CHAR_WIDTH)) {
                x=0;
                y++;
            }
        }
    }
    display.display();
  }
}
