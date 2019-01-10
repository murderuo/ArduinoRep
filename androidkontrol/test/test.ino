/*
  CONSUMER_POWER = 0x30,
  CONSUMER_SLEEP = 0x32,

  MEDIA_RECORD = 0xB2,
  MEDIA_FAST_FORWARD  = 0xB3,
  MEDIA_REWIND  = 0xB4,
  MEDIA_NEXT  = 0xB5,
  MEDIA_PREVIOUS  = 0xB6,
  MEDIA_PREV  = 0xB6, // Alias
  MEDIA_STOP  = 0xB7,
  MEDIA_PLAY_PAUSE  = 0xCD,
  MEDIA_PAUSE = 0xB0,

  MEDIA_VOLUME_MUTE = 0xE2,
  MEDIA_VOL_MUTE = 0xE2, // Alias
  MEDIA_VOLUME_UP = 0xE9,
  MEDIA_VOL_UP  = 0xE9, // Alias
  MEDIA_VOLUME_DOWN = 0xEA,
  MEDIA_VOL_DOWN  = 0xEA, // Alias

  CONSUMER_SCREENSAVER = 0x19e,

  CONSUMER_PROGRAMMABLE_BUTTON_CONFIGURATION = 0x182,
  CONSUMER_CONTROL_CONFIGURATION = 0x183,
  CONSUMER_EMAIL_READER = 0x18A,
  CONSUMER_CALCULATOR = 0x192,
  CONSUMER_EXPLORER = 0x194,

  CONSUMER_BROWSER_HOME = 0x223,
  CONSUMER_BROWSER_BACK = 0x224,
  CONSUMER_BROWSER_FORWARD  = 0x225,
  CONSUMER_BROWSER_REFRESH  = 0x227,
  CONSUMER_BROWSER_BOOKMARKS  = 0x22A,
*/
#include "HID-Project.h"


#define butonpin 8
const int pinLed = LED_BUILTIN;

void setup() {
  pinMode(8, INPUT);
  pinMode(pinLed, OUTPUT);


  Consumer.begin();
  //  Serial.begin(9600);
  //  while (!Serial) {
  //  }
}

void loop() {
  byte durum = digitalRead(butonpin);
  delay(50);
  if (durum == HIGH) {
    digitalWrite(pinLed, HIGH);
    // See HID Project documentation for more Consumer keys
    //Consumer.write(MEDIA_PLAY_PAUSE);
    //Consumer.write(MEDIA_VOLUME_UP);
    Consumer.write(CONSUMER_SCREENSAVER);



    if (durum == HIGH) {
      while (1) {
        durum = digitalRead(butonpin);
        if (durum == LOW) {
          digitalWrite(pinLed, LOW);
          break;
        }
      }
    }
    //  }
    //  else {
    //    //Serial.println("beklemede");
    //    digitalWrite(pinLed, LOW);
    //
    //  }
  }
}
