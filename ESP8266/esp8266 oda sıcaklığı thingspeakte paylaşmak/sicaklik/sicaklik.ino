#define AG_ADI "XXXXXXXXXXXXXXXXXX"
#define PAROLA "XXXXXXXXXXXXXX"
//#define sensorPin 0 // LM35'i A0 pinine takıyoruz.
String API_KEY("XXXXXXXXXXX"); // Buraya Thingspeak üzerinden aldığınız API Key gelecek.
#define IP "184.106.153.149" // thingspeak.com IP adresi

#include "DHT.h"//sıcaklık sensörünün kütüphanesi
#define DHTTYPE DHT11  //dht11 adında bir nesne oluşturuyoruz
#define DHTPIN 8   // 8 nolu dijital pine data ayağını bağlıyoruz
DHT dht(DHTPIN, DHTTYPE);//dht adında DHT kütüphanesinden bir nesne oluşturuyoruz.




void setup()
{

  dht.begin();  //dht nesnesini başlatıyoruz
  // Seri port işlemleri:

  Serial.begin(115200);
  Serial.println("AT");
  delay(5000);


  // Wi-Fi Bağlantısı
  if (Serial.find("OK")) {
    Serial.println("AT+CWMODE=3");
    delay(2000);
    String baglantiKomutu = String("AT+CWJAP=\"") + AG_ADI + "\",\"" + PAROLA + "\"";
    Serial.println(baglantiKomutu);
    // Bağlantının sağlanması için 10 saniye bekleyelim:
    delay(10000);
  }
}
void loop() {

  float  nem = dht.readHumidity();
  float  sicaklikNormal = dht.readTemperature();
  float  sicaklik =   dht.computeHeatIndex(sicaklikNormal, nem, false);

  sicaklikGonder(sicaklik);
  delay(60000);

  nemGonder(nem);
  delay(60000);

}

void nemGonder(byte nem){

  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");
  // Sunucuya bağlantının kurulabilmesi için 3 saniye bekleyelim:
  delay(3000);

  if (Serial.find("OK")) {
    
    String nemVerisi = "GET /update?api_key=";
    nemVerisi += API_KEY;
    nemVerisi += "&field2=" ;
    nemVerisi += String(nem);
   
    nemVerisi += "\r\n";

    String komutuBaslat = "AT+CIPSEND=";
    komutuBaslat += nemVerisi.length();
    Serial.println(komutuBaslat);

    //    Serial.println(veriKomutu.length());
    // Sorun oluşmadıysa veriyi gönder.

    delay(1000);
    if (Serial.find(">")) {
      Serial.print(nemVerisi);
    }
    else {
      Serial.println("AT+CIPCLOSE");
    }
    
    }
  
  
  
  }


  
void sicaklikGonder(float sicaklik) {
  // Sunucuya 80 portundan bağlanalım:
  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");
  // Sunucuya bağlantının kurulabilmesi için 3 saniye bekleyelim:
  delay(3000);

  if (Serial.find("OK")) {


    // Elimizdeki değeri sunucuya gönderelim:
    String veriKomutu = "GET /update?api_key=";
    veriKomutu += API_KEY;
    veriKomutu += "&field1=" ;
    veriKomutu += String(sicaklik);
   // veriKomutu += " *C ";
    veriKomutu += "\r\n";

    String komutuBaslat = "AT+CIPSEND=";
    komutuBaslat += veriKomutu.length();
    Serial.println(komutuBaslat);

    //    Serial.println(veriKomutu.length());
    // Sorun oluşmadıysa veriyi gönder.

    delay(1000);
    if (Serial.find(">")) {
      Serial.print(veriKomutu);
    }
    else {
      Serial.println("AT+CIPCLOSE");
    }





  } else
  {
    //    Serial.println("AT+RST");
  }

}
