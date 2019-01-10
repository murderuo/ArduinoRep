/*esp8266 arayüzünde sms gönderiyor*/



#define AG_ADI "your_wifi_SSID"
#define PAROLA "your_wifi_password"
#define IP "translate.ubidots.com"   // dnt change



const String apiKey = "Your_ubidots_TOKEN";//not api key,this is token!!


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

void loop() {


  int randNumber = random(0, 48);  //i dnt have temperature and humidity sensor,this couse this code make some close variable
									//Here produces a temperature value
									
  String randomSicaklik = String(randNumber); // i choose random value for temperature
  
  randNumber+=22; //i add 22 number, cause humidity value different temperature
  String randomNem = String(randNumber);//i choose humidity value

  sendData(randomSicaklik); // send temperature value
  delay(2000);   //delay 2 sc
  sendNemdata(randomNem);//send humidity value

  delay(15000); //wait 15 sc for loop

}


void sendData(String gonderilecekDeger)
{

  Serial.println(String("AT+CIPSTART=0,\"TCP\",\"") + IP + "\",9012");  //connect the thingspeak server if you want to more description pls visit this web adress http://help.ubidots.com/developers/send-data-to-ubidots-over-tcp-or-udp
																// we need to connect this port(9012) cause we can send own data
  
  delay(1500);
  String data = "microchip/1.0|POST|";//data header
  data += apiKey; //token number on ubidots.com
  data += "|arduino_uno=>"; //ubidots.com device
  data += "sicaklik:"; //variable name on this device, you need to change this variable name
  data += gonderilecekDeger; // send data
  data += "|end\n"; //data header and

  Serial.print("AT+CIPSEND=0,");                    //veri yollayacağımız zaman bu komutu kullanıyoruz. Bu komut ile önce kaç tane karakter yollayacağımızı söylememiz gerekiyor.
  delay(100);
  Serial.println(data.length());

  if (Serial.find(">")) {    //if we are  connect ubidots server, esp wait to send data and showing ">" character
    // if arduino see this character ">" write own temperature value .
    Serial.println(data);
    Serial.println("AT+CIPCLOSE=0"); //closing communication

    delay(250);
  } else {
    //Serial.println("AT+CIPCLOSE=0");
    Serial.println(  "gonderilemedi" ); // if we cant send data printing error.
  }

}

void sendNemdata(String nemDegeri)

{

  Serial.println(String("AT+CIPSTART=0,\"TCP\",\"") + IP + "\",9012");  //same description
 
  delay(1500);
  String data = "microchip/1.0|POST|";//data header
  data += apiKey; //token number on ubidots.com
  data += "|arduino_uno=>"; //ubidots.com device
  data += "nem:"; //variable name on this device
  data += nemDegeri; // gönderilen data
  data += "|end\n"; //data

  Serial.print("AT+CIPSEND=0,");                    //same description
  delay(100);
  Serial.println(data.length());

  if (Serial.find(">")) {    //same description
    // same description
    Serial.println(data);
    Serial.println("AT+CIPCLOSE=0");

    delay(250);
  } else {
    Serial.println("AT+CIPCLOSE=0");
    Serial.println(  "gonderilemedi" );
  }



}

