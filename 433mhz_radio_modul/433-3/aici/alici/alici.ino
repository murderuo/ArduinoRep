#include <VirtualWire.h>
#define led 4

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  vw_set_rx_pin(12);
  vw_set_ptt_inverted(true); //
  vw_setup(750);// speed of data transfer Kbps
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_have_message()) {
    Serial.println("mesaj geldi");
    delay(100);

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      String mesaj = "";
      for (int i = 0; i <= buflen; i++) {

        //        Serial.println(char(buf[i]));
        mesaj += char(buf[i]);
      }
      Serial.print("alınan mesaj: ");
      Serial.println(mesaj);
    }
  } else {
    Serial.println("mesaj yok");
    delay(100);

  }
}
