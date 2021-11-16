int x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
 
#define UpperThreshold 625
#define LowerThreshold 610
 
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const int PULSE_INPUT = A0;  //PIN A0 is on Signal of Pulse sensor
const int PULSE_BLINK = 3;    // Pin 13 is the on-board LED
const int THRESHOLD = 910;   // A ajuster en fonction de votre montage


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




void setup() {
   Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
}
 
 
void loop() 
{
  if(x>127)  
  {
    display.clearDisplay();
    x=0;
    lastx=x;
  }
 
  int value=analogRead(PULSE_INPUT);
  display.setTextColor(WHITE);
  int y=60-1.5*(value-LowerThreshold);
  display.writeLine(lastx,lasty,x,y,WHITE);
  lasty=y;
  lastx=x;
  // calc bpm
 
  if(value>UpperThreshold)
  {
    if(BeatComplete)
    {
      BPM=millis()-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  if((value<LowerThreshold)&(BPMTiming))
    BeatComplete=true;
    // display bpm
  display.writeFillRect(0,50,128,16,BLACK);
  display.setCursor(0,50);
  display.print(BPM);
  display.print(" BPM");
  display.display();
  x++;
}
