#define analoginput A0


void setup() {
  Serial.begin(9600);

  while (!Serial) {
  }

}

void loop() {
  int butondegeri = analogRead(analoginput);
  Serial.println(butondegeri);


}
