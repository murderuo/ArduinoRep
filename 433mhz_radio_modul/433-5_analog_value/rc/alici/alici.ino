#include <VirtualWire.h>


struct analog
{
  int X_deger ;
  int Y_deger ;
};
typedef struct analog Analog;
Analog data;

char X_valueChar[3];
char Y_valueChar[3];

void setup() {
  Serial.begin(9600);

  vw_set_rx_pin(12);
  //  vw_set_ptt_inverted(true); //
  vw_setup(750);// speed of data transfer Kbps
  vw_rx_start();
}


void loop() {
  uint8_t buf[sizeof(data)];
  uint8_t buflen = sizeof(data);

  if (vw_have_message()) {
    //    Serial.println("mesaj geldi");


    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      memcpy(&data, &buf, buflen);

      Serial.print("x deger:");
      Serial.println(data.X_deger);

      Serial.print("y deger:");
      Serial.println(data.Y_deger);
      delay(250);
    }
  }
  //  else {
  //    Serial.println("mesaj yok");
  //    delay(100);
  //
  //  }
}
