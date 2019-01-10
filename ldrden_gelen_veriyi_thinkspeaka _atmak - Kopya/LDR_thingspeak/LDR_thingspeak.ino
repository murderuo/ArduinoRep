#define LDRpin A1
#define ledpin 7

#define AG_ADI "xxxx"
#define PAROLA "xxxxxxxxx"
//#define sensorPin 0 // LM35'i A0 pinine takıyoruz.
String API_KEY("xxxxxxx"); // Buraya Thingspeak üzerinden aldığınız API Key gelecek.
#define IP "184.106.153.149" // thingspeak.com IP adresi

void setup()
{
  pinMode(LDRpin, INPUT);
  pinMode(ledpin, OUTPUT);
  
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
  int data = analogRead(LDRpin);
  data = map(data, 0, 1023, 0, 100);

  isigiGonder(data);
delay(10000);
}

int isigiGonder(byte data){
  
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
      digitalWrite(ledpin, HIGH);
      delay(50);
      digitalWrite(ledpin, LOW);
    }
    else {
      Serial.println("AT+CIPCLOSE");
    }

  }
  
  }
