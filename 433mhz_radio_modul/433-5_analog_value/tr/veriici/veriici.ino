#include <VirtualWire.h>


#define X_pin A4
#define Y_pin A5

struct analog
{
  int X_deger;
  int Y_deger;
};


typedef struct analog Analog;
Analog data;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  vw_set_tx_pin(12);
  vw_set_ptt_inverted(true); //
  vw_setup(750);// speed of data transfer Kbps
}

void loop() {
  //  char * mesaj[] = {"merhaba","dünya"};
  int X_eksen = analogRead(X_pin);
  int Y_eksen = analogRead(Y_pin);
  data.X_deger = map (X_eksen, 0, 1023, 0, 240);
  data.Y_deger = map (Y_eksen, 0, 1023, 0, 240);

  vw_send((uint8_t *)&data, sizeof(data));
  vw_wait_tx();
  Serial.print("x deger:");
  Serial.println(data.X_deger);

  Serial.print("y deger:");
  Serial.println(data.Y_deger);
  delay(250);

}
