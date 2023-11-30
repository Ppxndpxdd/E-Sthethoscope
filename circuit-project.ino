//initial define
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

//system define
const int microphonePin = A0;
int delta;

const int battPin = A1;
int value = 0;
float voltage;
float perc;

void setup()
{
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
}

void loop()
{

  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 1000; ++i)
  {

    int val = analogRead(microphonePin);

    mn = min(mn, val);
    mx = max(mx, val);
  }

  delta = mx - mn;
  noTone(11);
  if (delta > 700)
  {
    tone(11, 10000);
  }
  //  Serial.print("Min=");
  //  Serial.print(mn);
  //  Serial.print(" Max=");
  //  Serial.print(mx);
  //  Serial.print(" Delta=");
  Serial.println(delta);

  value = analogRead(battPin);
  voltage = value * 5.0 / 1023;
  perc = map(voltage, 3.6, 4.2, 0, 50);
  Serial.print("Voltage= ");
  Serial.println(voltage);
  //  Serial.print("Battery level= ");
  //  Serial.print(perc);
  //  Serial.println(" %");

  //delay(250);
  updateValue(delta);
}

void updateChart() {

}

void updateValue(int value) {
  display.clearDisplay();
  display.setTextSize(1);          // text size
  display.setTextColor(WHITE);
  display.setCursor(0, 10);        // position to display
  display.println(value); // text to display
  display.display();               // show on OLED
}
