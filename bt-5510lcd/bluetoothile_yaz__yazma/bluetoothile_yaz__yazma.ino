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

}

void loop() {
  String gelenveri = "";
  int gvu;
  String birinci_sat, ikinci_sat, ucuncu_sat, dorduncu_sat, besinci_sat, altinci_sat;

  while (mySerial.available()) {// serialden veri alımı tamamlanana kadar dön
    //lcd satırlarını temizle (satır no,başlangıç px,bitiş px)
    lcd.clrRow(0, 0, 84); // 1. satırı sil
    lcd.clrRow(1, 0, 84);//2.satırı sil
    lcd.clrRow(2, 0, 84);//3.satırı sil
    lcd.clrRow(3, 0, 84);//4.satırı sil
    lcd.clrRow(4, 0, 84);//4.satırı sil

    delay(5);
    char gv = mySerial.read(); //gelen veri ASCI kodda char olarak geliyor
    gelenveri += gv;
    gvu = gelenveri.length();//gelen veri uzunlugu
    //gelenveri.toLowerCase();
    gelenveri.replace("ı", "i");//tr karakterler ingilizce karakter ile değiştiriliyor
    gelenveri.replace("ü", "u");
    gelenveri.replace("ç", "c");
    gelenveri.replace("ş", "s");
    gelenveri.replace("ö", "o");
    gelenveri.replace("ğ", "g");
    gelenveri.replace("İ", "I");
    gelenveri.replace("Ğ", "G");
    gelenveri.replace("Ç", "C");
    gelenveri.replace("Ö", "O");
    gelenveri.replace("Ş", "S");
    gelenveri.replace("Ü", "U");
    //gelenveri.replace("ğ", "g");

    //    lcd.printNumI(gvu, LEFT, 40);
    //    Serial.println(gvu);

  }

  for (int i = 0; i <= gvu; i++) {
    birinci_sat += gelenveri[i];
    if (i == 14) {
      for (i; i <= gvu; i++) {
        ikinci_sat += gelenveri[i];
        if (i == 28) {
          for (i; i <= gvu; i++) {
            ucuncu_sat += gelenveri[i];
            if (i == 42) {
              for (i; i <= gvu; i++) {
                dorduncu_sat += gelenveri[i];
                if (i == 56) {
                  for (i; i <= gvu; i++) {
                    besinci_sat += gelenveri[i];
                    if (i == 70) {
                      for (i; i <= gvu; i++)
                        altinci_sat = gelenveri[i];
                    }
                  }

                }
              }
            }
          }
        }
      }
      //      break;
    }
  }


  if (gelenveri == "clear_all") {//gelen komut clear_all ise ekranı temizle
    lcd.clrScr();
  } else {
    //değilse gelen veriyi ekrana yazdır

    delay(10);
    //    lcd.print(gelenveri, LEFT, 0);
    //    Serial.println(gelenveri);

    lcd.print(birinci_sat, LEFT, 0);
    //Serial.println(birinci_sat);

    lcd.print(ikinci_sat, LEFT, 8);
//    Serial.println(ikinci_sat);

    lcd.print(ucuncu_sat, LEFT, 16);
//    Serial.println(ucuncu_sat);

    lcd.print(dorduncu_sat, LEFT, 24);
//    Serial.println(dorduncu_sat);

    lcd.print(besinci_sat, LEFT, 32);
//    Serial.println(besinci_sat);

    lcd.print(altinci_sat, LEFT, 40);
//    Serial.println(altinci_sat);





  }
  //  lcd.print(ikincisatir, LEFT, 8);
  //  Serial.println(ikincisatir);
  //    lcd.clrRow(4, 0, 84);
  //    lcd.clrRow(5, 0, 84);





  delay(25);





  //  lcd.print("herhangi bir ", LEFT, 0);
  //  lcd.print("baglanti yok", LEFT, 8);

}



