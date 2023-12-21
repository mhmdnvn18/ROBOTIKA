#include <AFMotor.h>

#define sensor1 A0
#define sensor2 A1
#define sensor3 A2

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value1 = digitalRead(sensor1);
  int value2 = digitalRead(sensor2);
  int value3 = digitalRead(sensor3);

  Serial.print("Sensor 1: ");
  Serial.print(value1);
  Serial.print(" | Sensor 2: ");
  Serial.print(value2);
  Serial.print(" | Sensor 3: ");
  Serial.println(value3);

  // Implementasi logika kontrol motor sesuai dengan kondisi sensor
  if (value1 == HIGH && value2 == LOW && value3 == HIGH) {
    // Kasus maju
    forward();
  } else if (value1 == HIGH && value2 == HIGH && value3 == LOW) {
    // Kasus belok kanan
    turnRight();
  } else if (value1 == LOW && value2 == HIGH && value3 == HIGH) {
    // Kasus belok kiri
    turnLeft();
  } else {
    // Kasus berhenti
    stopMotors();
  }
}

void forward() {
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void stopMotors() {
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
