#include <Servo.h>

#define LDR1 A0
#define LDR2 A1
#define servoPin 2
#define ERROR 30  // Acceptable difference
#define MIN_ANGLE 40
#define MAX_ANGLE 140
#define LDR_OFFSET -40  // Calibration offset (adjust as needed)

int Spoint = 90;  // Initial servo position
Servo servo;

int averageRead(int pin) {
  long sum = 0;
  for (int i = 0; i < 20; i++) {  // Reduced to 20 for better speed
    sum += analogRead(pin);
  }
  return sum / 20;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Program!");

  servo.attach(servoPin);
  servo.write(Spoint);
  delay(1000);
}

void loop() {
  int ldr1 = averageRead(LDR1);
  int ldr2 = averageRead(LDR2) + LDR_OFFSET;  // Apply offset

  Serial.print("LDR 1: ");
  Serial.println(ldr1);
  Serial.print("LDR 2 (Calibrated): ");
  Serial.println(ldr2);

  int diff = abs(ldr1 - ldr2);

  if (diff > ERROR) {  // If difference is significant
    if (ldr1 > ldr2 && Spoint < MAX_ANGLE) {
      Spoint += 2;
    } else if (ldr1 < ldr2 && Spoint > MIN_ANGLE) {
      Spoint -= 2;
    }

    servo.write(Spoint);
    Serial.println("Servo moved to: " + String(Spoint));
  }

  delay(200);
}
