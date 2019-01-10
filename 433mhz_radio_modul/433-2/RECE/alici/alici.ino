#include <VirtualWire.h>
#define led 4

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  vw_set_rx_pin(12);
  vw_set_ptt_inverted(true); //
  vw_setup(500);// speed of data transfer Kbps
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_have_message()) {
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      Serial.print("data boyutu: ");
      Serial.println(buf[buflen]);
      Serial.print("data uzunlugu: ");
      Serial.println(buflen);
      
      if (char(buf[buflen]) == 1) {

        digitalWrite(led , HIGH);
      }
    } else
      Serial.println("Mesaj bekleniyor...");
  }
}
