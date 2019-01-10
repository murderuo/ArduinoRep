#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
 }

void loop() {
  String gelenveri = ""; //string türünden alınacak veri türünü belirliyoruz

  while (bluetooth.available()) {
	  // serialden veri alımı tamamlanana kadar dön
    //lcd satırlarını temizle (satır no,başlangıç px,bitiş px)
    delay(5);
    char gv = bluetooth.read(); //gelen veri ASCI kodda char olarak geliyor
    gelenveri += gv;
    gelenveri.toLowerCase();
  }


  Serial.println(gelenveri);
  delay(100);
}



