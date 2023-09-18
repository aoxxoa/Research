#include "NewPing.h"
#include "DHT.h"

#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define buzzer 10
#define DHTPIN 11
#define DHTTYPE DHT11
#define MAX_DISTANCE 400

DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float hum;
float temp;
float duration;
float soundsp;
float soundcm;
float distance;

int iterations = 2; 
int buzzerDuration = 150;
int buzzercloseDuration = 600;
int buzzertoocloseDuration = 1000;
void setup() {
  Serial.begin (9600);
  dht.begin();
  pinMode(buzzer, OUTPUT);
}

void loop() {
  delay(200);
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  soundsp = 331.4 + (0.606 * temp) + (0.0123 * hum);
  soundcm = soundsp / 10000;
  duration = sonar.ping_median(iterations);
  distance = sonar.ping_cm();
  distance = (duration / 2) * soundcm;
  Serial.print("Sound: ");
  Serial.print(soundsp);
  Serial.print("m/s, ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.print(" C, ");
  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
  }
  else{
    Serial.print(distance);
    Serial.println(" cm");
    if (distance <= 15) {
    digitalWrite(buzzer, HIGH);
  }
  else{
    digitalWrite(buzzer, LOW);
  }
  }
  if (distance <= 70) {
    digitalWrite(buzzer, HIGH);
    delay(buzzerDuration);
    digitalWrite(buzzer, LOW);
  }
  else{digitalWrite(buzzer, LOW);
  }
  if (distance <= 30) {
    digitalWrite(buzzer, HIGH);
    delay(buzzercloseDuration);
    digitalWrite(buzzer, LOW);
  }
  else{digitalWrite(buzzer, LOW);
  }
    if (distance <= 15) {
    digitalWrite(buzzer, HIGH);
    delay(buzzertoocloseDuration);
    digitalWrite(buzzer, LOW);
  }
  else{digitalWrite(buzzer, LOW);
  }
  delay(200);
}