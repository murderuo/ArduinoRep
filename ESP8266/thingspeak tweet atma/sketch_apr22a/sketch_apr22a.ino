#define AG_ADI "XXXXXXXXXXX"
#define PAROLA "XXXXXXXXXXXXX"
#define IP "184.106.153.149"//thingspeak.com IP adresi

void setup() {
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

int randNumber;

void loop() {



  twitAt();
  delay(120000);


}


void twitAt() {

  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  //thingspeak sunucusuna bağlanmak için bu kodu kullanıyoruz.
  //AT+CIPSTART komutu ile sunucuya bağlanmak için sunucudan izin istiyoruz.
  //TCP burada yapacağımız bağlantı çeşidini gösteriyor. 80 ise bağlanacağımız portu gösteriyor
  delay(1500);
  String tweet = "POST /apps/thingtweet/1/statuses/update HTTP/1.1\n";
  tweet += "Host: api.thingspeak.com\n";
  tweet += "Connection: close\n";
  tweet += "Content-Type: application/x-www-form-urlencoded\n";
  tweet += "Content-Length:";

  //char emojiler[] = {'✌', '😂', '😝', '😁', '😱', '👉', '🙌', '🍻', '🔥', '🌈', '☀', '🎈', '🌹', '💄', '🎀', '⚽', '🎾', '🏁', '😡', '👿', '🐻', '🐶', '🐬', '🐟', '🍀', '👀', '🚗', '🍎', '💝', '💙', '👌', '❤', '😍', '😉', '😓', '😳', '💪', '💩', '🍸', '🔑', '💖', '🌟', '🎉', '🌺', '🎶', '👠', '🏈', '⚾', '🏆', '👽', '💀', '🐵', '🐮', '🐩', '🐎', '💣', '👃', '👂', '🍓', '💘', '💜', '👊', '💋', '😘', '😜', '😵', '🙏', '👋', '🚽', '💃', '💎', '🚀', '🌙', '🎁', '⛄', '🌊', '⛵', '🏀', '🎱', '💰', '👶', '👸', '🐰', '🐷', '🐍', '🐫', '🔫', '👄', '🚲', '🍉', '💛', '💚'};
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


  durum += randNumber;// gelen rastegele sayıdan 25000 çıkardık ki rastgele sayıyı 4 hneye düşürdük


  tweet += 32 + durum.length();
  tweet += "\r\n\r\n";
  tweet += String("api_key=M17IXWLTBZU4NDWT");                           //ThingSpeak'den aldığımız Twitter API KEY'ini buraya yazıyoruz.
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
    randNumber = 0;


  }
}


