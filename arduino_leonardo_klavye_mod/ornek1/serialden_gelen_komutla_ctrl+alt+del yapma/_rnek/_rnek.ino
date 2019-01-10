#include <Keyboard.h>
void setup()
{
  Serial.begin(9600);

}

void loop()
{
  char gelendata;
  String stringecevir = "";
  while (Serial.available()) {

    gelendata = Serial.read();
    stringecevir += gelendata;

  }

  if (stringecevir == "kontrol") {

    Serial.println("birazdan Ctrl+alt+del yapilacak");
    delay(1000);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_DELETE);
    delay(100);
    Keyboard.releaseAll();


  }
  else {
    Serial.print(stringecevir);
    delay(150);
  }



}

