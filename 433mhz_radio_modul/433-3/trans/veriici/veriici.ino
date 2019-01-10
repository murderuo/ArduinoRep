#include <VirtualWire.h>


#define buton 4

void setup() {
  Serial.begin(9600);
  pinMode(buton, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  vw_set_tx_pin(12);
  vw_set_ptt_inverted(true); //
  vw_setup(750);// speed of data transfer Kbps
  //digitalWrite(buton, LOW);
  digitalWrite(LED_BUILTIN,LOW);
}

void loop() {
  char mesaj[] = {'m','e','r','h','a','b','a'};
  int btndrm = digitalRead(buton);
  char gon_karakter;
  char *msj;
//  delay(100);
  
  if (btndrm == HIGH ) {
//    Serial.println("butona basildi");
    digitalWrite(LED_BUILTIN,HIGH);
    msj="merhaba";
    vw_send((uint8_t*)msj, strlen(msj));
    vw_wait_tx();
    Serial.println("merhaba gönderildi");
//    Serial.println(butondegeri[1]);
    delay(100);
  } else {
//    gon_karakter=mesaj[6];
//    vw_send((uint8_t*)gon_karakter,  strlen(gon_karakter));
//    vw_wait_tx();
    Serial.println("hic bir mesaj gonderilemedi");
//    Serial.println(butondegeri[0]);
    delay(100);
  }
    digitalWrite(LED_BUILTIN,LOW);

}
