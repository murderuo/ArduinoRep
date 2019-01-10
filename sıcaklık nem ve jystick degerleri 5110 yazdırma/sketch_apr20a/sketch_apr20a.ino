// LCD5110_Bitmap
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of how to use bitmaps.
// You can also see how to use invert().
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Basic.h>
LCD5110 myGLCD(8, 9, 10, 11, 12);
extern uint8_t SmallFont[];
extern uint8_t MediumFont[];
extern uint8_t BigNumbers[];
#define x_eksen A5
#define y_eksen A4
#define buton 13

#include "DHT.h"//sıcaklık sensörünün kütüphanesi
#define DHTTYPE DHT22  //dht11 adında bir nesne oluşturuyoruz
#define DHTPIN 2   // 8 nolu dijital pine data ayağını bağlıyoruz
DHT dht(DHTPIN, DHTTYPE);//dht adında DHT kütüphanesinden bir nesne oluşturuyoruz.



void setup()
{
  myGLCD.InitLCD();
  Serial.begin(9600);
  pinMode (buton, INPUT);
  myGLCD.setFont(SmallFont);
  dht.begin();



}

void loop()
{
  sicaklikvenem();

  //degeroku();

  ekranayaz();


  delay(50);

//  myGLCD.clrScr();
}

float sicaklikvenem() {

  float  nem = dht.readHumidity();
  float  sicaklikNormal = dht.readTemperature();
  float  sicaklik =   dht.computeHeatIndex(sicaklikNormal, nem, false);

  myGLCD.print("Sicaklik:", LEFT, 0);
  myGLCD.printNumF(sicaklik , 2, 52, 0); //sayı,basamak sa,x,y değeri
  myGLCD.print("Nem: ", LEFT, 8);
  myGLCD.printNumF(nem, 2, 32, 8);

  delay(25);

  //    Serial.println(nem);
  //    Serial.println(sicaklik);



}



int degeroku() {

  int xdegeri = analogRead(x_eksen);
  int ydegeri = analogRead(y_eksen);
  int pindurum = digitalRead(buton);

  //  Serial.print("x degeri: ");
  //  Serial.print(xdegeri);
  //  Serial.print("y degeri: ");
  //  Serial.print(ydegeri);
  //  Serial.println("########################3");
  //  delay(500);
  xdegeri = map (xdegeri, 0, 1023, 0, 180);
  ydegeri = map (ydegeri, 0, 1023, 0, 180);



  Serial.print("x degeri: ");
  Serial.print(xdegeri);
  Serial.print("  y degeri: ");
  Serial.print(ydegeri);
  Serial.print("  pin durumu  ");
  Serial.print(pindurum);
  Serial.println("------");
  delay(20);



}

int ekranayaz() {

  int xdegeri = analogRead(x_eksen);
  int ydegeri = analogRead(y_eksen);
  byte pindurum = digitalRead(buton);

  //  Serial.print("x degeri: ");
  //  Serial.print(xdegeri);
  //  Serial.print("y degeri: ");
  //  Serial.print(ydegeri);
  //  Serial.println("########################3");
  //  delay(500);
  xdegeri = map (xdegeri, 0, 1023, 0, 180);
  ydegeri = map (ydegeri, 0, 1023, 0, 180);


  myGLCD.print("X degeri: ", LEFT, 16);//string, x,y=0,8,16,24,32,40 satırlar
  myGLCD.clrRow(2,55,80);// satır numarası (0-5 aarası), x baslangıc(px),x son(px))
  myGLCD.printNumI(ydegeri, 55, 16);//integer bir deger, x=55px den sonra yaz,y=0 ilk satıra yaz
  myGLCD.print("Y degeri: ", LEFT, 24);
   myGLCD.clrRow(3,55,80);
  myGLCD.printNumI(xdegeri, 55, 24);//integer bir deger, x=55px den sonra yaz,y=8 ikinci satıra yaz

  myGLCD.print("buton durum:", LEFT, 32);
  myGLCD.printNumI(pindurum, 70, 32);

  delay(25);



}
