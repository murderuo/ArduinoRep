#include <VirtualWire.h>


#define AG_ADI "xxxxxxxxxxxxxxxxx"
#define PAROLA "xxxxxxxxxxx"
//#define sensorPin 0 // LM35'i A0 pinine takıyoruz.
String API_KEY("xxxxxxxxxx"); // Buraya Thingspeak üzerinden aldığınız API Key gelecek.
#define IP "184.106.153.149" // thingspeak.com IP adresi


struct isik
{
  byte isikMiktari;

};

typedef struct isik isikM;
isikM data;

void setup()
{
  vw_set_rx_pin(4);
  //  vw_set_ptt_inverted(true); //
  vw_setup(750);// speed of data transfer Kbps
  vw_rx_start();

  pinMode (13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(115200);
  Serial.println("AT");
  delay(2000);
  // Wi-Fi Bağlantısı
  if (Serial.find("OK")) {
    Serial.println("AT+CWMODE=1");
    delay(2000);
    String baglantiKomutu = String("AT+CWJAP=\"") + AG_ADI + "\",\"" + PAROLA + "\"";
    Serial.println(baglantiKomutu);
    delay(10000);// Bağlantının sağlanması için 10 saniye bekleyelim:

  }
}

void loop()
{
  uint8_t buf[sizeof(data)];
  uint8_t buflen = sizeof(data);

  if (vw_have_message()) {

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      memcpy(&data, &buf, buflen);
      isigiGonder(data.isikMiktari);
      delay(10000);
    }
  }


}

int isigiGonder(byte data) {

  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");
  // Sunucuya bağlantının kurulabilmesi için 3 saniye bekleyelim:
  delay(3000);

  if (Serial.find("OK")) {

    String isikMiktari = "GET /update?api_key=";
    isikMiktari += API_KEY;
    isikMiktari += "&field3=" ;
    isikMiktari += String(data);

    isikMiktari += "\r\n";

    String komutuBaslat = "AT+CIPSEND=";
    komutuBaslat += isikMiktari.length();
    Serial.println(komutuBaslat);

    //    Serial.println(veriKomutu.length());
    // Sorun oluşmadıysa veriyi gönder.

    delay(1000);
    if (Serial.find(">")) {
      Serial.print(isikMiktari);
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
    }
    else {
      Serial.println("AT+CIPCLOSE");
    }

  }

}
