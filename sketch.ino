#include <ESP32Servo.h>

#define LED_RED 23
#define LED_BLUE 22
#define TRIG_PIN 12
#define ECHO_PIN 14

float duration_us, distance_cm;

Servo myServo;

void setup() {
  Serial.begin(115200);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  myServo.attach(5); // GPIO pin number for servo
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  delay(10); // this speeds up the simulation
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;

  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (distance_cm <= 5) {
    for (int pos = 0; pos <= 90; pos += 1) {
      myServo.write(pos);
      delay(10);
    }
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);

    delay(2000);

    for (int pos = 90; pos >= 0; pos -= 1) {
      myServo.write(pos);
      delay(10);
    }
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
  }

  delay(500);
}
