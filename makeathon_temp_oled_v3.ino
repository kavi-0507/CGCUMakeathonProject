#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHT_PIN     4
#define DHT_TYPE    DHT11
//#define BUZZER_PIN  26
#define HEATER_PIN  16
#define TEMP_DANGER 30

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  //pinMode(BUZZER_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  
  // 3. Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common I2C address
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("System Ready!");
  display.display();

  //tone(BUZZER_PIN, 1000, 2000);
  delay(500);
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Sensor error!");
    return;
  }

  Serial.printf("Temp: %.1f°C\n", temp);
  
  bool heaterOn = false;
  if (temp < TEMP_DANGER) {
    digitalWrite(HEATER_PIN, LOW);
    heaterOn = true;
    //tone(BUZZER_PIN, 1000, 500); delay(600);
    //tone(BUZZER_PIN, 1000, 500); delay(600);
    //tone(BUZZER_PIN, 1000, 500); delay(1000);
  } else {
    digitalWrite(HEATER_PIN, HIGH);
    //noTone(BUZZER_PIN);
    heaterOn = false;
  }
  // --- Display Logic ---
  display.clearDisplay();
  
  // Temperature Row
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Current Temp:");
  
  display.setTextSize(2);
  display.setCursor(0,15);
  display.print(temp);
  display.print(" C");

  // Status Row
  display.setTextSize(1);
  display.setCursor(0,45);
  display.print("Heater: ");
  display.println(heaterOn ? "ON" : "OFF");

  display.display();
  delay(1500);
}