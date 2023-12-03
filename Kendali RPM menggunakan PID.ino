#define hall_sensorA_left 2      // Sensor Hall Effect untuk motor kiri
#define hall_sensorA_right 3     // Sensor Hall Effect untuk motor kanan
#define encoder_kal 2            // Faktor kalibrasi encoder
#define PWM_left 6               // Pin PWM untuk motor kiri
#define PWM_right 5              // Pin PWM untuk motor kanan
#define in1_left 7               // Pin kontrol motor kiri
#define in2_left 8               // Pin kontrol motor kiri
#define in1_right 9              // Pin kontrol motor kanan
#define in2_right 10             // Pin kontrol motor kanan

int interval = 60;
int motorSpeedLeft = 0;
int motorSpeedRight = 0;
long previousMillis = 0;
long currentMillis = 0;
int rpmLeft = 0;
int rpmRight = 0;
int encoderValueLeft = 0;
int encoderValueRight = 0;
int data = 0;
int sp = 140;
float kp = 1;
float ki = 0.95;
float kd = 0;
float p, i, d;
int errorLeft = 0;
int lastErrorLeft = 0;
int sumErrorLeft = 0;
int errorRight = 0;
int lastErrorRight = 0;
int sumErrorRight = 0;

void setup() {
  // Inisialisasi
  Serial.begin(9600);
  pinMode(hall_sensorA_left, INPUT_PULLUP);
  pinMode(hall_sensorA_right, INPUT_PULLUP);
  pinMode(PWM_left, OUTPUT);
  pinMode(PWM_right, OUTPUT);
  pinMode(in1_left, OUTPUT);
  pinMode(in2_left, OUTPUT);
  pinMode(in1_right, OUTPUT);
  pinMode(in2_right, OUTPUT);
  digitalWrite(in1_left, LOW);
  digitalWrite(in2_left, HIGH);
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, HIGH);
  encoderValueLeft = 0;
  encoderValueRight = 0;
  attachInterrupt(digitalPinToInterrupt(hall_sensorA_left), updateEncoderLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(hall_sensorA_right), updateEncoderRight, RISING);
  previousMillis = millis();
}

void loop() {
  // Kendali RPM
  while (data <= 100) {
    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      // Pembacaan RPM dan PID
      rpmLeft = (float)(encoderValueLeft * encoder_kal);
      rpmRight = (float)(encoderValueRight * encoder_kal);
      previousMillis = currentMillis;
      Serial.print("Left: ");
      Serial.print(rpmLeft);
      Serial.print("  Right: ");
      Serial.println(rpmRight);
      encoderValueLeft = 0;
      encoderValueRight = 0;

      // PID untuk motor kiri
      errorLeft = sp - rpmLeft;
      sumErrorLeft = sumErrorLeft + errorLeft;
      p = kp * errorLeft;
      i = ki * sumErrorLeft;
      d = kd * (errorLeft - lastErrorLeft);
      motorSpeedLeft = p + i + d;
      if (motorSpeedLeft > 250) motorSpeedLeft = 250;
      else if (motorSpeedLeft < 0) motorSpeedLeft = 0;

      // PID untuk motor kanan
      errorRight = sp - rpmRight;
      sumErrorRight = sumErrorRight + errorRight;
      p = kp * errorRight;
      i = ki * sumErrorRight;
      d = kd * (errorRight - lastErrorRight);
      motorSpeedRight = p + i + d;
      if (motorSpeedRight > 250) motorSpeedRight = 250;
      else if (motorSpeedRight < 0) motorSpeedRight = 0;

      analogWrite(PWM_left, motorSpeedLeft);
      analogWrite(PWM_right, motorSpeedRight);

      lastErrorLeft = errorLeft;
      lastErrorRight = errorRight;
      data++;
    }
  }
  analogWrite(PWM_left, 0);
  analogWrite(PWM_right, 0);
}

void updateEncoderLeft() {
  // Fungsi interupsi untuk menghitung encoder motor kiri
  encoderValueLeft++;
}

void updateEncoderRight() {
  // Fungsi interupsi untuk menghitung encoder motor kanan
  encoderValueRight++;
}
