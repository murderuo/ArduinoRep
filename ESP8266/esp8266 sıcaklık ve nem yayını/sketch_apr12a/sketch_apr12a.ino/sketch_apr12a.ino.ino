//#include <SoftwareSerial.h>
//
//SoftwareSerial espSerial(12, 13);

#define Durum true
#define AG_ADI "XXXXXXXXXXXXXXX"
#define PAROLA "XXXXXXXXXXXXXXXXX"

void setup() {
  Serial.begin(115200);
//  espSerial.begin(115200);
  ATkomut("AT\r\n", 2000, Durum);
  ATkomut("AT+CWMODE=1\r\n", 1000, Durum);
  String baglantiKomutu = String("AT+CWJAP=\"") + AG_ADI + "\",\"" + PAROLA + "\"";
  ATkomut(baglantiKomutu, 3000, Durum);
  ATkomut("AT+CIFSR\r\n", 2000, Durum);
  ATkomut("AT+CIPMUX=1\r\n", 2000, Durum);
  ATkomut("AT+CIPSERVER=1,80\r\n", 2000, Durum);

}

void loop()
{
  if (Serial.available()) {
    if (Serial.find("+IPD,"))
      delay(500);
    int baglanti = Serial.read() - 48;
    String metin = "<center><head> ARDUINO SENDED TEST DATA</head><br><br><br><br></center>";
    metin += "<table width=\"351\" border=\"0\" align=\"center\"><tr><td width=\"162\">ODA SICAKLIGI</td><td width=\"179\">NEM</td></tr><tr><td>";  
    metin += "38,52";//sicaklik değer
    metin += "</td><td>";
    metin += "57";//nem değer
    metin += "</td></tr></table>";

    String cipsend = "AT+CIPSEND=";//Komut gönderiyoruz>>We send commands
    cipsend += baglanti;
    cipsend += ",";
    cipsend += metin.length();
    cipsend += "\r\n";
    ATkomut(cipsend, 2000, Durum);
    ATkomut(metin, 2000, Durum);
    String kapatma = "AT+CIPCLOSE=";
    kapatma += baglanti;
    kapatma+="\r\n";
    
    ATkomut(kapatma,2000,Durum);//Sunucuyu kapatttık>>We closed the server


  }


}

String ATkomut(String komut, const int sure, boolean durum) {

  String gelen = "";

  Serial.print(komut);
  long int zaman = millis();
  while ((zaman + sure) > millis()) {
    while (Serial.available()) {
      char c = Serial.read();
      gelen += c;
    }
  }
  if (durum) {
    Serial.print(gelen);
  }
  return gelen;

}


