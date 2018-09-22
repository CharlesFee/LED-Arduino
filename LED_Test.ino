#include <FastLED.h>

#define NUM_LEDS 100
#define LED_PIN 2
//Sound Sensor
int loudness;
int loudMax;
int loudMin;
int loudCheck;
int LEDB;
int leftifCounter;
int rightifCounter;
long loopCounter;
int patternSelector;
int leftlastLEDUpdated;
int rightlastLEDUpdated;
int wubbifier;
boolean flowDirection = true;
CRGB led[NUM_LEDS];
void setup() {
  loudness = 0;
  loudMax = 0;
  loudMin = 1024;
  loudCheck = 0;
  leftifCounter = 0;
  rightifCounter = 0;
  loopCounter = 0;
  patternSelector = 0;
  leftlastLEDUpdated = 51;
  rightlastLEDUpdated = 50;
  wubbifier = 0;
  flowDirection = true;
  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(50, 0, 0);
  }
  Serial.begin(115200);

  FastLED.show();
}

void loop() {
  Serial.println(loudness);
  if (analogRead(0) > 245 && analogRead(0) < 295) {
    loudness = analogRead(0);
  }
  else if (analogRead(0) < 245) {
    loudness = 246;
  } else if (analogRead(0) > 345) {
    loudness = 344;
  }
  if (loudness > loudMax) {
    loudMax = loudness;
  } else if (loudness < loudMin) {
    loudMin = loudness;
  }

  //Simple Snake Pattern
  if (patternSelector == 0) {
    smoothwub();
  }
  if (patternSelector == 1) {
    if (loudness > (loudMax / 1.2)) {
      if (flowDirection == false) {
        flowDirection = true;
      } else {
        flowDirection = false;
      }
    }
    snake();
    loudCheck++;
  }
  if (patternSelector == 2) {
    if (loudness > (loudMax / 1.2)) {
      if (flowDirection == false) {
        flowDirection = true;
      } else {
        flowDirection = false;
      }
    }
    shortSnake();
    loudCheck++;
  }
  if (patternSelector == 3) {
    seizurewub();
  }
}

void resetLEDS() {
  for (int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(50, 0, 0);
  }
}

void snake() {
  //Move left snake out
  if (flowDirection == true && leftifCounter == 10) {
    led[leftlastLEDUpdated] = CRGB(0, 0, 50);
    if (leftlastLEDUpdated < (NUM_LEDS - 1)) {
      leftlastLEDUpdated++;
    }
    FastLED.show();
    leftifCounter = 0;
  }
  //Move left snake in
  if (flowDirection == false && leftifCounter == 10) {
    led[leftlastLEDUpdated] = CRGB(50, 0, 0);
    //Make sure that the LED doesnt Overflow
    if (leftlastLEDUpdated != ((NUM_LEDS / 2) + 1)) {
      leftlastLEDUpdated--;
    }
    FastLED.show();
    leftifCounter = 0;
  }

  //Move right snake in
  if (flowDirection == false && rightifCounter == 10) {
    led[rightlastLEDUpdated] = CRGB(50, 0, 0);
    if ((NUM_LEDS / 2) > rightlastLEDUpdated) {
      rightlastLEDUpdated++;
    }
    FastLED.show();
    rightifCounter = 0;
  }
  //Move right snake out
  if (flowDirection == true && rightifCounter == 10) {
    led[rightlastLEDUpdated] = CRGB(0, 0, 50);
    //Make sure that the LED doesnt Overflow
    if (rightlastLEDUpdated != 1) {
      rightlastLEDUpdated--;
    }
    FastLED.show();
    rightifCounter = 0;
  }
  rightifCounter++;
  leftifCounter++;
}

void shortSnake() {
  //Move left snake out
  if (flowDirection == true && leftifCounter == 10) {
    led[leftlastLEDUpdated] = CRGB(0, 0, 50);
    if (leftlastLEDUpdated > ((NUM_LEDS / 2) + 3)) {
      led[leftlastLEDUpdated - 4] = CRGB(50, 0, 0);
    }
    if (leftlastLEDUpdated < NUM_LEDS + 1) {
      leftlastLEDUpdated++;
    }
    FastLED.show();
    leftifCounter = 0;
  }
  //Move left snake in
  if (flowDirection == false && leftifCounter == 10) {
    led[leftlastLEDUpdated] = CRGB(0, 0, 50);
    if (leftlastLEDUpdated < (NUM_LEDS - 3)) {
      led[leftlastLEDUpdated + 4] = CRGB(50, 0, 0);
    }
    //Make sure that the LED doesnt Overflow
    if (leftlastLEDUpdated != ((NUM_LEDS / 2) + 1)) {
      leftlastLEDUpdated--;
    }
    FastLED.show();
    leftifCounter = 0;
  }

  //Move right snake in
  if (flowDirection == false && rightifCounter == 10) {
    led[rightlastLEDUpdated] = CRGB(0, 0, 50);
    if (rightlastLEDUpdated > 3) {
      led[rightlastLEDUpdated - 4] = CRGB(50, 0, 0);
    }
    if ((NUM_LEDS / 2) > rightlastLEDUpdated) {
      rightlastLEDUpdated++;
    }
    FastLED.show();
    rightifCounter = 0;
  }
  //Move right snake out
  if (flowDirection == true && rightifCounter == 10) {
    led[rightlastLEDUpdated] = CRGB(0, 0, 50);
    if (rightlastLEDUpdated < ((NUM_LEDS / 2) - 3)) {
      led[rightlastLEDUpdated + 4] = CRGB(50, 0, 0);
    }
    //Make sure that the LED doesnt Overflow
    if (rightlastLEDUpdated != 1) {
      rightlastLEDUpdated--;
    }
    FastLED.show();
    rightifCounter = 0;
  }
  rightifCounter++;
  leftifCounter++;
}

void seizurewub() {
  wubbifier = (loudness - 265) / 2;
  if (rightifCounter == 0) {
    for (int i = 40; i < 61; i++) {
      led[i] = CRGB(0, 0, 50);
      FastLED.show();
    } rightifCounter = 1;
  }
  //if(leftifCounter == 50){
  for (int i = 51; i < (wubbifier + 60); i++) {
    led[i] = CRGB(0, 0, 50);
    delay(.4);
  }
  FastLED.show();
  for (int i = 50; i > abs(wubbifier - 40); i--) {
    led[i] = CRGB(0, 0, 50);
    delay(.4);
  }
  FastLED.show();
  delay(10);
  for (int i = 100; i > (wubbifier + 60); i--) {
    led[i] = CRGB(50, 0, 0);
    delay(.4);
  }
  for (int i = 0; i < abs(wubbifier - 40); i++) {
    led[i] = CRGB(50, 0, 0);
    delay(.4);
  }
  FastLED.show();
  delay(10);
  leftifCounter = 0;
  //}else{
  leftifCounter++;
  //}
}
void smoothwub() {
  wubbifier = (loudness-265)*40/30;
  if (rightifCounter == 0) {
    for (int i = 40; i < 61; i++) {
      led[i] = CRGB(0, 0, 50);
      FastLED.show();
    } rightifCounter = 1;
    leftlastLEDUpdated = 60;
    rightlastLEDUpdated = 40;
  }
  //Move left snake out
  if (leftlastLEDUpdated < (wubbifier + 60)) {
    led[leftlastLEDUpdated] = CRGB(0, 0, 50);
    leftlastLEDUpdated++;
    FastLED.show();
  }
  //Move right snake out
  if (rightlastLEDUpdated > abs(40 - wubbifier)) {
    led[rightlastLEDUpdated] = CRGB(0, 0, 50);
    rightlastLEDUpdated--;
    FastLED.show();
  }
  delay(3);
  //Move left snake in
  if (leftlastLEDUpdated > (60 + wubbifier)) {
    led[leftlastLEDUpdated] = CRGB(50, 0, 0);
    //Make sure that the LED doesnt Overflow
      leftlastLEDUpdated--;
    FastLED.show();
  }
  //Move right snake in
  if (rightlastLEDUpdated < abs(40 - wubbifier)) {
    led[rightlastLEDUpdated] = CRGB(50, 0, 0);
    rightlastLEDUpdated++;
    FastLED.show();
  }
  delay(3);
}
