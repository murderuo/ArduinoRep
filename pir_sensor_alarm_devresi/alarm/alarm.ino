#define durumled 5
#define yesilled 2
#define sariled 3
#define kirmiziled 4
#define pirsensor 1
#define butonkontrol 10



void setup() {

  pinMode(yesilled, OUTPUT);
  pinMode(sariled, OUTPUT);
  pinMode(kirmiziled, OUTPUT);
  pinMode(durumled, OUTPUT);
  pinMode(butonkontrol, INPUT);
  pinMode(pirsensor, INPUT);

}

void kapaliMod() {
  digitalWrite(yesilled, LOW);
  digitalWrite(durumled, LOW);
  digitalWrite(sariled, LOW);
  digitalWrite(kirmiziled, HIGH);


}

void ledAktif() {
  digitalWrite(yesilled, LOW);
  digitalWrite(durumled, HIGH);
  digitalWrite(sariled, HIGH);
  digitalWrite(kirmiziled, LOW);


}


void pirAktif() {
  digitalWrite(yesilled, HIGH);
  digitalWrite(sariled, LOW);
  digitalWrite(kirmiziled, LOW);

  byte pirDurum = digitalRead (pirsensor);
  if (pirDurum == HIGH) {
    digitalWrite(durumled, HIGH);
  } else {
    digitalWrite(durumled, LOW);
  }
}
byte secenek = 0;
void loop() {


  byte butonDurum = digitalRead(butonkontrol);
  delay(150);



  if (butonDurum == HIGH) {
    secenek ++;
    if (butonDurum == HIGH) {
      while (1) {
        butonDurum = digitalRead(butonkontrol);
        if (butonDurum == LOW)
          break;
      }
    }
  }
  
  if (secenek == 0) {
    kapaliMod();
  } else if (secenek == 1) {
    ledAktif();
  } else if (secenek == 2) {
    pirAktif();
  } else {
    secenek = 0;
  }





}
