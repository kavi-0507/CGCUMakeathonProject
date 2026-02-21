#include <DHT.h>

#define DHT_PIN     4
#define DHT_TYPE    DHT11
#define BUZZER_PIN  26
#define HEATER_PIN  16
#define TEMP_DANGER 25

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  
  tone(BUZZER_PIN, 1000, 2000);
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Sensor error!");
    return;
  }

  Serial.printf("Temp: %.1f°C\n", temp);

  if (temp < TEMP_DANGER) {
    digitalWrite(HEATER_PIN, HIGH);
    tone(BUZZER_PIN, 1000, 500); delay(600);
    tone(BUZZER_PIN, 1000, 500); delay(600);
    tone(BUZZER_PIN, 1000, 500); delay(1000);
  } else {
    digitalWrite(HEATER_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(2000);
}