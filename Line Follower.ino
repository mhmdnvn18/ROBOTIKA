#include <AFMotor.h>

AF_DCMotor M3(3); // KIRI
AF_DCMotor M4(4); // KANAN

int R_S = A1; // SENSOR KANAN
int S_S = A2; // SENSOR TENGAH
int L_S = A0; // SENSOR KIRI

void setup() {
  // put your setup code here, to run once:
  pinMode(L_S, INPUT);
  pinMode(S_S, INPUT);
  pinMode(R_S, INPUT);

  M3.setSpeed(250);
  M4.setSpeed(250);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((digitalRead(L_S) == LOW) && (digitalRead(S_S) == HIGH) && (digitalRead(R_S) == LOW)) {
    forward();
  } else if ((digitalRead(L_S) == HIGH) && (digitalRead(S_S) == HIGH) && (digitalRead(R_S) == HIGH)) {
    forward();
  } else if ((digitalRead(L_S) == HIGH) && (digitalRead(S_S) == HIGH) && (digitalRead(R_S) == LOW)) {
    turnLeft();
  } else if ((digitalRead(L_S) == HIGH) && (digitalRead(S_S) == LOW) && (digitalRead(R_S) == LOW)) {
    turnLeft();
  } else if ((digitalRead(L_S) == LOW) && (digitalRead(S_S) == HIGH) && (digitalRead(R_S) == HIGH)) {
    turnRight();
  } else if ((digitalRead(L_S) == LOW) && (digitalRead(S_S) == LOW) && (digitalRead(R_S) == HIGH)) {
    turnRight();
  }

  Serial.print(digitalRead(L_S));
  Serial.print(digitalRead(R_S));
  Serial.println(digitalRead(S_S));
}

void forward() {
  M3.setSpeed(250);
  M4.setSpeed(250);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void turnRight() {
  M3.setSpeed(250);
  M4.setSpeed(50);
  M3.run(FORWARD);
  M4.run(BACKWARD);
}

void turnLeft() {
  M3.setSpeed(50);
  M4.setSpeed(250);
  M3.run(BACKWARD);
  M4.run(FORWARD);
}
