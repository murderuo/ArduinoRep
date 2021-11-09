#include <LCD5110_Basic.h>
LCD5110 myGLCD(8, 9, 10, 11, 12);
extern uint8_t SmallFont[];

#define ag_ismi "xxxxxxxxxxxxxx"  //Wifi adı>>Wifi name
#define ag_sifresi "xxxxxxxxxxxxxxxxx"  //Wifi şifresi>>Wifi password
#define IP "184.106.153.149"//thingspeak.com IP adresi


void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);

  Serial.begin(115200); //ESP modülünün baudRate değeri 115200 bu yüzden Seriport'u 115200 yazıyoruz>>The baud rate of the ESP module is 115200, so we write Seriport 115200
  Serial.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz>>We check whether the Esp module is connected or not
  delay(2000);
  String serialdengelen = Serial.readString();
  myGLCD.print(serialdengelen, LEFT, 0);//string, x=left,y=0,8,16,24,32,40 satırlar

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



  twitAt();
  String gelentwit=twitAt();
 twitiYayinla(gelentwit);

  delay(10000);
}



String twitAt() {

  Serial.println(String("AT+CIPSTART=4,\"TCP\",\"") + IP + "\",80");  //thingspeak sunucusuna bağlanmak için bu kodu kullanıyoruz.
  //AT+CIPSTART komutu ile sunucuya bağlanmak için sunucudan izin istiyoruz.
  //TCP burada yapacağımız bağlantı çeşidini gösteriyor. 80 ise bağlanacağımız portu gösteriyor
  delay(1500);

  String tweet = "POST /apps/thingtweet/1/statuses/update HTTP/1.1\n";
  tweet += "Host: api.thingspeak.com\n";
  tweet += "Connection: close\n";
  tweet += "Content-Type: application/x-www-form-urlencoded\n";
  tweet += "Content-Length:";

  String durum = "";
  int randNumber = random(0, 9999);
  if (randNumber > 0 && randNumber < 999) {
    durum = "#bedelliaskerlik istiyoruz duyun sesimizi🇹🇷  ";
    //durum = "BedelliAskerlik SözüTutulsun @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }
  else if (randNumber >= 999 && randNumber < 1999) {
    durum = "#BedelliAskerlik herkesi mutlu eder.Aileri,sosyal yardim bekleyenleri ";//  🇹🇷
    //    durum = "BedelliAskerlik SözüTutulsun @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }
  else if (randNumber >= 1999 && randNumber < 2999) {
    durum = "Zor durumda olan,ailelerine bakmak zorunda olan gencleriz.#bedelliaskerlik ";
    //    durum = "BedelliAskerlik SözüTutulsun @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }//++
  else if (randNumber >= 2999 && randNumber < 3999) {
    durum = "#bedelliaskerlik yurt dışında yaşayanlara tanınıyor? Bize neden yok?";
    //    durum = "BedelliAskerlik SözüTutulsun #BedelliAskerlik @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }//++
  else if (randNumber >= 3999 && randNumber < 4999) {
    durum = "Sayın Bakanım yüzbinler #Bedelliaskerlik istiyor.Mağduriyetleri giderin @Burhankuzu ";
    //    durum = "BedelliAskerlik SözüTutulsun @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }
  else if (randNumber >= 4999 && randNumber < 5999) {
    durum = "şimdi tam zamanı.600bin bakaya gencin derdine derman #BedelliAskerlik @RT_Erdogan ";
    //    durum = "BedelliAskerlik SözüTutulsun #BedelliAskerlik @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }
  else if (randNumber >= 5999 && randNumber < 6999) {
    durum = "#BedelliAskerlik🇹🇷@TC_Basbakan @tcbestepe @RT_Erdogan @BA_Yildirim ";
    //    durum = "BedelliAskerlik SözüTutulsun @RT_Erdogan @tcbestepe @TC_Basbakan ";

  }
  else
    durum = "@RT_ERDOGAN @TC_BASBAKAN #bedelliaskerlik🇹🇷bekliyoruz ulkenin gelecegi gencler ";                         // Yollamak istediğimiz tweeti buraya yazıyoruz.
  //    durum = "BedelliAskerlik SözüTutulsun @RT_Erdogan @tcbestepe @TC_Basbakan ";

	return durum;

  durum += randNumber;// gelen rastegele sayıdan 25000 çıkardık ki rastgele sayıyı 4 hneye düşürdük

  

  tweet += 32 + durum.length();
  tweet += "\r\n\r\n";
  tweet += String("api_key=xxxxxx");                           //ThingSpeak'den aldığımız Twitter API KEY'ini buraya yazıyoruz.
  tweet += String("&status=");

  tweet += durum; //twiti String olarak ekliyoruz

  Serial.print("AT+CIPSEND=4,");                    //veri yollayacağımız zaman bu komutu kullanıyoruz. Bu komut ile önce kaç tane karakter yollayacağımızı söylememiz gerekiyor.
  delay(100);
  Serial.println(tweet.length());

  if (Serial.find(">")) {                         //eğer sunucu ile iletişim sağlayıp komut uzunluğunu gönderebilmişsek ESP modülü bize ">" işareti ile geri dönüyor.
    // arduino da ">" işaretini gördüğü anda sıcaklık verisini esp modülü ile thingspeak sunucusuna yolluyor.
    Serial.println(tweet);
    Serial.println("AT+CIPCLOSE=4");

    delay(250);
    randNumber = 0;
  }
 


}

void twitiYayinla() {


  if (Serial.available() > 0) {
    if (Serial.find("+IPD,")) {
      delay(500);
      int baglanti = Serial.read() - 48;

      String metin = "<head> Atilan Tweet________:</head><br><br>";//Başlık>>Title
      metin += twitAt();

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





