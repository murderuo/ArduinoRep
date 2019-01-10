#include <VirtualWire.h>

#define LDRpin A1
#define ledpin 7


struct LDR
{
  int isikMiktari;

};

typedef struct LDR isik;
isik data;


void setup()
{
  
  pinMode(LDRpin, INPUT);
  pinMode(ledpin, OUTPUT);

  vw_set_tx_pin(4);
  vw_set_ptt_inverted(true); //
  vw_setup(750);// speed of data transfer Kbps
}

void loop()
{
  data.isikMiktari = analogRead(LDRpin);
  data.isikMiktari = map(data.isikMiktari, 0, 1023, 0, 100);
  delay(10000);
  vw_send((uint8_t *)&data, sizeof(data));
  vw_wait_tx();


  digitalWrite(ledpin, HIGH);
  delay(50);
  digitalWrite(ledpin, LOW);



}

