#define AG_ADI "xxxxxxxxxxx"
#define PAROLA "xxxxxxxxxxxx"
#define IP "184.106.153.149"//thingspeak.com IP adresi

#include <LCD5110_Basic.h>//ekran kütüphanesini ekliyoruz
LCD5110 myGLCD(8, 9, 10, 11, 12);//ekranımızı oluşturuyoruz
extern uint8_t SmallFont[];//ekranda kullanılacak fontu belirliyoruz



void setup() {
  myGLCD.InitLCD();//ekraımızı başlatıyoruz
  myGLCD.setFont(SmallFont);//ekran fontumuzu oluşturuyoruz


  Serial.begin(115200);
  Serial.println("AT");
  delay(2000);
  // Wi-Fi Bağlantısı
  if (Serial.find("OK")) {
    Serial.println("AT+CWMODE=1");
    delay(2000);
    String baglantiKomutu = String("AT+CWJAP=\"") + AG_ADI + "\",\"" + PAROLA + "\"";
    Serial.println(baglantiKomutu);
    delay(5000); //5sn bekliyoruz

  }
}


void loop() {



  twitAt();
    delay(150);

  ekranayaz(twitAt());
  delay(120000);


}

String twitAt() {

  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  //thingspeak sunucusuna bağlanmak için bu kodu kullanıyoruz.
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

  String atilan_tweetno = String(randNumber); //fonksiyondan atılan twetno çekiyoruz

  durum += randNumber;// gelen rastegele sayıdan 25000 çıkardık ki rastgele sayıyı 4 hneye düşürdük


  tweet += 32 + durum.length();
  tweet += "\r\n\r\n";
  tweet += String("api_key=xxxxxxxxxxxxxx");                           //ThingSpeak'den aldığımız Twitter API KEY'ini buraya yazıyoruz.
  tweet += String("&status=");

  tweet += durum; //twiti String olarak ekliyoruz

  Serial.print("AT+CIPSEND=");                    //veri yollayacağımız zaman bu komutu kullanıyoruz. Bu komut ile önce kaç tane karakter yollayacağımızı söylememiz gerekiyor.
  delay(100);
  Serial.println(tweet.length());

  if (Serial.find(">")) {                         //eğer sunucu ile iletişim sağlayıp komut uzunluğunu gönderebilmişsek ESP modülü bize ">" işareti ile geri dönüyor.
    // arduino da ">" işaretini gördüğü anda sıcaklık verisini esp modülü ile thingspeak sunucusuna yolluyor.
    Serial.println(tweet);
    Serial.println("AT+CIPCLOSE=0");

    delay(250);
    //randNumber = 0;
  }

return atilan_tweetno;//fonksiyondan atılan tweti çekiyoruz
}

void ekranayaz(String tweetno) {
  myGLCD.clrRow(2, 0, 80); // satır numarası (0-5 aarası), x baslangıc(px),X son(px))

  myGLCD.print("Tweet Numarasi", CENTER, 0);//string, x,y=0,8,16,24,32,40 satırlar
  myGLCD.print(tweetno, CENTER, 8);

  //
  //  myGLCD.printNumI(ydegeri, 55, 16);//integer bir deger, x=55px den sonra yaz,y=0 ilk satıra yaz
  //  myGLCD.print("Y degeri: ", LEFT, 24);
  //  myGLCD.clrRow(3, 55, 80);
  //  myGLCD.printNumI(xdegeri, 55, 24);//integer bir deger, x=55px den sonra yaz,y=8 ikinci satıra yaz
  //
  //  myGLCD.print("buton durum:", LEFT, 32);
  //  myGLCD.printNumI(pindurum, 70, 32);




}


