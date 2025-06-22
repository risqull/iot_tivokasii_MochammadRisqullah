#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHTPIN 19
#define DHTTYPE DHT22
#define TIMEDHT 1000

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LDR_PIN 34 // Sensor cahaya di GPIO34

float humidity, celsius;
uint32_t timerDHT = TIMEDHT;
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Fungsi untuk membaca suhu dan kelembapan
void getTemperature() {
  if ((millis() - timerDHT) > TIMEDHT) {
    timerDHT = millis();
    humidity = dht.readHumidity();
    celsius = dht.readTemperature();

    if (isnan(humidity) || isnan(celsius)) {
      Serial.println("Gagal membaca sensor DHT!");
      return;
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal diinisialisasi");
    for (;;);
  }
  
  display.clearDisplay();
}

void loop() {
  getTemperature();
  int lightValue = analogRead(LDR_PIN); // Membaca intensitas cahaya
  
  // Menampilkan data di serial monitor
  Serial.print("Temp: ");
  Serial.print(celsius);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Light: ");
  Serial.println(lightValue);

  // Menampilkan di OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(celsius);
  display.println(" C");

  display.setCursor(0, 16);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 32);
  display.print("Light: ");
  display.print(lightValue);

  display.display();
  delay(1000);
}