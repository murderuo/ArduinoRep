#include <HID-Project.h>

#define analoginput A0
const int pinLed = LED_BUILTIN;

int secim = 0;

void setup() {
  //  Serial.begin(9600);
  //  while (!Serial) {
  //  }
  pinMode(pinLed, OUTPUT);

  Consumer.begin();

}
boolean butondurum;

void loop() {
  butondurum = false;

  int butondegeri = analogRead(analoginput);
  if (butondegeri >= 20) {
    if (butondegeri <= 100 && butondegeri >= 70) {
      butondurum = true;
      digitalWrite(pinLed, HIGH);
      secim = 2;
      if (butondurum == true) {
        while (1) {
          butondegeri = analogRead(analoginput);
          if (butondegeri == 0) {
            break;
          }
        }
      }

      //    Serial.println("play-pause");


    } else if (butondegeri <= 200 && butondegeri >= 150) {
      butondurum = true;
      digitalWrite(pinLed, HIGH);
      secim = 1;
      if (butondurum == true) {
        while (1) {
          butondegeri = analogRead(analoginput);
          if (butondegeri == 0) {
            break;
          }
        }
      }

      //    Serial.println("onceki");
    } else if (butondegeri <= 1023 && butondegeri >= 1000) {
      butondurum = true;
      digitalWrite(pinLed, HIGH);
      secim = 3;
      if (butondurum == true) {
        while (1) {
          butondegeri = analogRead(analoginput);
          if (butondegeri == 0) {
            break;
          }
        }
      }

      //    Serial.println("sonraki");
    } else  digitalWrite(pinLed, HIGH);


    switch (secim)
    {
      case 2:
        delay(60);
        Consumer.write(MEDIA_PLAY_PAUSE);
        break;
      case 1:
        delay(60);
        Consumer.write(MEDIA_PREVIOUS);
        break;
      case 3:
        delay(60);
        Consumer.write(MEDIA_NEXT);
        break;
      default:
        secim = 0;
        break;


    }

  }
}






