
#define ag_ismi "XXXXXXXXXX"  //Wifi adı>>Wifi name
#define ag_sifresi "XXXXXXXXXXXXXX"  //Wifi şifresi>>Wifi password

void setup()
{
  Serial.begin(115200); //ESP modülünün baudRate değeri 115200 bu yüzden Seriport'u 115200 yazıyoruz>>The baud rate of the ESP module is 115200, so we write Seriport 115200
  Serial.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz>>We check whether the Esp module is connected or not
  delay(2000);

  if (Serial.find("OK")) //Eğer Esp8266 ile bağlantı kurulmuşsa "OK" komutu geri dönüş yapıyor>>If the Esp8266 is connected,the "OK" commands returns
  {
    Serial.println("AT+CWMODE=1"); //Esp modülümüzün WiFi modunu STA şekline getiriyoruz ve wifiyi açıyoruz eğer=2 olursa wifiyi kapanır>>We bring STA the our wifi mode of Esp and open,if equal the 2,wifi is closed
    delay(2000);
    String baglantiKomutu = String("AT+CWJAP=\"") + ag_ismi + "\",\"" + ag_sifresi + "\""; //Wifiye bağlanmasını sağlıyoruz>>We provide connection
    Serial.println(baglantiKomutu);
    delay(5000);
  }

  Serial.print("AT+CIPMUX=1\r\n");//Çoklu bağlatıyı açıyoruz.>>We open multiple links.
  delay(2000);
  Serial.print("AT+CIPSERVER=1,80\r\n");// Bağlantının açık olduğunu ve portunu söylüyoruz.>>We tell that connection is clear and port's value
  delay(2000);
}
void loop() {
  if (Serial.available() > 0) {
    if (Serial.find("+IPD,")) {
      delay(500);
      int baglanti = Serial.read() -48;

      String metin = "<head> MERHABALAR</head>";//Başlık>>Title
      
      String cipsend = "AT+CIPSEND=";//Komut gönderiyoruz>>We send commands
      cipsend += baglanti;
      cipsend += ",";
      cipsend += metin.length();
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(1000);
      
      Serial.println(metin);
  
      String kapatma = "AT+CIPCLOSE=";
      kapatma += baglanti;
      kapatma += "\r\n";


      Serial.print(kapatma);//Sunucuyu kapatttık>>We closed the server

    }
  }
}

