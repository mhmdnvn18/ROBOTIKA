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
  int val1 = digitalRead(sensor1);
  int val2 = digitalRead(sensor2);
  int val3 = digitalRead(sensor3);
  Serial.print("Sensor 1 = ");
  Serial.println(val1);
  Serial.print("Sensor 2 = ");
  Serial.println(val2);
  Serial.print("Sensor 3 = ");
  Serial.println(val3);

//   if (val1 <= 1 && val2 <= 1) 
//   {
//     // Jika cahaya terdeteksi oleh kedua sensor, maju
//     motor3.run(BACKWARD);
//     motor4.run(BACKWARD);
//   } 
//   else if (val1 <= 350 && val2 > 350) 
//   {
//     // Jika hanya sensor kiri yang mendeteksi cahaya, belok kiri
//     motor3.run(FORWARD);
//     motor4.run(BACKWARD);
//   } 
//   else if (val1 > 350 && val2 <= 350) 
//   {
//     // Jika hanya sensor kanan yang mendeteksi cahaya, belok kanan
//     motor3.run(BACKWARD);
//     motor4.run(FORWARD);
//   } 
//   else 
//   {
//     // Jika tidak ada sensor yang mendeteksi cahaya, berhenti
//     motor3.run(RELEASE);
//     motor4.run(RELEASE);
//   }
}
