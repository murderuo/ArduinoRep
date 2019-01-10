#include <VirtualWire.h>


#define buton 4

void setup() {
  Serial.begin(9600);
  pinMode(buton, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  vw_set_tx_pin(12);
  vw_set_ptt_inverted(true); //
  vw_setup(500);// speed of data transfer Kbps
  //digitalWrite(buton, LOW);
  digitalWrite(LED_BUILTIN,LOW);
}

void loop() {
  char butondegeri[] = {'0', '1'};
  int btndrm = digitalRead(buton);
  delay(100);
  
  if (btndrm == HIGH ) {
    Serial.println("butona basildi");
    digitalWrite(LED_BUILTIN,HIGH);
    vw_send((uint8_t*)butondegeri[1], sizeof(butondegeri));
    vw_wait_tx();
    Serial.print("buton durumu 1");
    Serial.println(butondegeri[1]);
//    delay(250);
  } else {
    vw_send((uint8_t*)butondegeri[0], 1);
    vw_wait_tx();
    Serial.print("buton durumu 0");
    Serial.println(butondegeri[0]);
//    delay(250);
  }
    digitalWrite(LED_BUILTIN,LOW);

}
