//neopixel stuff
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(34, 0, NEO_GRB + NEO_KHZ800);

//button stuff
#include <Bounce2.h>
Bounce button = Bounce();
int buttonPin = 1;

//cases
int mode = 0;
boolean isBlue = true;

//timers
unsigned long startTime = millis();
int interval1 = 1000;
unsigned long startTimeArray = millis();
unsigned long endTimeArray = millis();


//arrays
int numGrid = 34;
int numFrames = 2;
int whichFrame = 0;

char index[34] {
  0, 1,
  2, 3,
  4, 5, 6, 7,
  8, 9, 10, 11, 12, 13,
  14, 15, 16, 17, 18, 19,
  20, 21, 22, 23, 24, 25,
  26, 27, 28, 29, 30, 31,
  32, 33
};

char colors[2][3] {
  {255, 0, 255}, //pink
  {0, 0, 255}, //blue

};

char frames[2][34] {
  {
          0, 0,
          1, 1,
       1, 0, 0, 1,
    0, 0, 1, 1, 0, 0,
    0, 1, 0, 0, 1, 0,
    0, 1, 0, 0, 1, 0,
    1, 0, 1, 1, 0, 1,
          0, 0,
  },
  {
          1, 1,
          0, 0,
       0, 1, 1, 0,
    1, 1, 0, 0, 1, 1,
    1, 0, 1, 1, 0, 1,
    1, 0, 1, 1, 0, 1,
    0, 1, 0, 0, 1, 0,
          1, 1,
  },
};

void setup() {
  strip.begin();
  strip.clear();
  //strip.setBrightness(20);

  button.attach(buttonPin, INPUT);
  button.interval(25);
}

void loop() {
  button.update();
  if (button.rose() == true) {
    mode ++;
  }

  if (mode > 2) {
    mode = 0;
  }
  switch (mode) {
    case 0:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
      break;
    case 1:
      if (millis() - startTime > interval1) {
        isBlue = !isBlue;
        startTime = millis();
      }
      strip.clear();
      if (isBlue) {
        for (int i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 255);
        }
      }
      else {
        for (int i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 255, 0);
        }
      }
      strip.show();
      break;
    case 2:
      //strip.clear();
      if (millis() - startTimeArray > interval1) {
        whichFrame += 1;
        startTimeArray = millis();
        if (whichFrame >= numFrames) {
          whichFrame = 0;
        }
      }

      for (int i = 0; i < numGrid; i++) {
        int whichLED = i;
        int whichIndex = index[whichLED];
        int whichColor = frames[whichFrame][whichLED];

        int r = colors[whichColor][0];
        int g = colors[whichColor][1];
        int b = colors[whichColor][2];

        strip.setPixelColor (whichIndex, r, g, b);
      }
      strip.show();
      break;
  }
}
