#include <AFMotor.h>

#define sensor1 A0
#define sensor2 A1
#define sensor3 A2

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// PID Constants
double Kp = 1.2;  // Proportional gain
double Ki = 0.005; // Integral gain
double Kd = 0.5;  // Derivative gain

int setpoint = 1; // Target position for PID
int previousError = 0;
int integral = 0;

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

  int error = calculateError(value1, value2, value3);
  int pidOutput = calculatePID(error);

  // Adjust motor speeds based on PID output
  int leftSpeed = 200 + pidOutput;
  int rightSpeed = 200 - pidOutput;

  // Ensure motor speeds are within limits
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Apply motor control
  motor3.setSpeed(leftSpeed);
  motor4.setSpeed(rightSpeed);

  // Adjust motor directions based on sensor values
  if (value1 == HIGH && value2 == LOW && value3 == HIGH) {
    forward();
  } else if (value1 == HIGH && value2 == HIGH && value3 == LOW) {
    turnRight();
  } else if (value1 == LOW && value2 == HIGH && value3 == HIGH) {
    turnLeft();
  } else {
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

int calculateError(int value1, int value2, int value3) {
  // Implement your own logic to calculate error based on sensor values
  // This is a simple example, and you may need to adjust it depending on your specific hardware setup and requirements.
  // The error can be calculated, for example, as the difference between the desired setpoint and the actual position.
  int error = setpoint - (value1 + 2 * value2 + 3 * value3);
  return error;
}

int calculatePID(int error) {
  // PID calculations
  int proportional = Kp * error;
  integral += error;
  int derivative = Kd * (error - previousError);
  previousError = error;

  // PID output
  int pidOutput = proportional + Ki * integral + derivative;

  return pidOutput;
}
