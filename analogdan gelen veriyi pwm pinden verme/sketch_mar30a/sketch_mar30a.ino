
byte pot_pin=A4;
byte led_yak=3;

int pot_gelen_veri;

void setup() 
{
 pinMode(led_yak,OUTPUT);
 Serial.begin(9600);

}

void loop() 
{
  pot_gelen_veri = analogRead(pot_pin);
  Serial.println(pot_gelen_veri);
  delay(250);
  int lede_ayarla= map(pot_gelen_veri,0,1023,0,255);//pottan gelen 0-1023 arası veriyi
  //analog çıkışa vermek için analog çıkş miktarı olan 
  //0-255 arası bir değere map'liyoruz
  //ADC->analog dijital convertor hafızası 10 bit , 0ile 1023 araı değer alırken
  //PWM ->hafızası 8 bit olduğu için 0 ile 255 arası değer alır.
//  float lede_giden_voltaj=((pot_gelen_veri/1023.0)*5000)/10;
//  Serial.print("lede giden veri :" );
//  Serial.println( lede_giden_voltaj );
  analogWrite(3,lede_ayarla);
  delay(200);
}
