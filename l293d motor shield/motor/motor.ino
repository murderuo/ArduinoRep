#include <AFMotor.h>
AF_DCMotor motor1(1); //, MOTOR12_8KHZ); // 10 pine baglı sol motor pwm
AF_DCMotor motor2(2);//, MOTOR12_8KHZ); // 11 pine bağlı sağ motorpwm




void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
    motor1.setSpeed(100);
    motor2.setSpeed(100);
  

}

void loop() {
  Serial.println("ileri");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(2000);
  Serial.println("geri");

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(2000);
  Serial.println("dur");

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(2000);

}



