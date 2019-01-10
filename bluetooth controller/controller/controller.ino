#include <LCD5110_Basic.h>
LCD5110 lcd(8, 9, 10, 11, 12);

extern uint8_t SmallFont[];
extern uint8_t MediumFont[];
extern uint8_t BigNumbers[];



#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  //Serial.begin(9600);
  mySerial.begin(9600);
  lcd.InitLCD();
  lcd.setFont(SmallFont);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  lcd.setContrast(60);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop() {
  String gelenveri = "";
  //  int gvu;
  //  String birinci_sat, ikinci_sat, ucuncu_sat, dorduncu_sat, besinci_sat, altinci_sat;

  while (mySerial.available()) {// serialden veri alımı tamamlanana kadar dön
    //lcd satırlarını temizle (satır no,başlangıç px,bitiş px)
    lcd.clrRow(0, 0, 84); // 1. satırı sil
    //

    delay(5);
    char gv = mySerial.read(); //gelen veri ASCI kodda char olarak geliyor
    gelenveri += gv;
    gelenveri.toLowerCase();
  }


  lcd.print(gelenveri, LEFT, 0);
  if (gelenveri == "fw") {//gelen komut clear_all ise ekranı temizle
    digitalWrite(4, HIGH);
  } else if (gelenveri == "stp") {
    //değilse gelen veriyi ekrana yazdır
    digitalWrite(4, LOW);
  }

  if (gelenveri == "bw") {//gelen komut clear_all ise ekranı temizle

    digitalWrite(5, HIGH);
  } else if (gelenveri == "stp") {
    //değilse gelen veriyi ekrana yazdır
    digitalWrite(5, LOW);
  }
  if (gelenveri == "tr") {//gelen komut clear_all ise ekranı temizle

    digitalWrite(6, HIGH);
  } else if (gelenveri == "stp") {
    //değilse gelen veriyi ekrana yazdır
    digitalWrite(6, LOW);
  }
  if (gelenveri == "tl") {//gelen komut clear_all ise ekranı temizle

    digitalWrite(7, HIGH);
  } else if (gelenveri == "stp") {
    //değilse gelen veriyi ekrana yazdır
    digitalWrite(7, LOW);
  }
}



