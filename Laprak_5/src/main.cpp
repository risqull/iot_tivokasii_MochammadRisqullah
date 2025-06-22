#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>          // Ganti dengan ESP8266WiFi.h jika menggunakan ESP8266
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";       // Ganti dengan SSID Wi-Fi kamu
const char* password = ""; // Ganti dengan password Wi-Fi kamu
String apiKey = "20ca0ff523294dcdeb424dfc5802e21b";       // API Key dari OpenWeatherMap
String city = "Malang";              // Kota yang ingin ditampilkan
String units = "metric";              // Untuk Celsius gunakan "metric", untuk Fahrenheit "imperial"
String server = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&units=" + units + "&appid=" + apiKey;
//String server= "https://api.openweathermap.org/data/2.5/weather?q=Malang&appid=20ca0ff523294dcdeb424dfc5802e21b";

LiquidCrystal_I2C lcd(0x27, 16, 2);   // Inisialisasi LCD dengan alamat I2C 0x27

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Weather Info:");
  
  // Inisialisasi Wi-Fi
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 1);
  lcd.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected!");
  delay(2000);
  lcd.clear();
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {  // Check WiFi connection status
    
    HTTPClient http;
    http.begin(server);     // Specify the URL
    int httpCode = http.GET();  // Make the request
    
    if (httpCode > 0) { // Check for the returning code
      
      String payload = http.getString();
      Serial.println(payload);   // Print the response payload
      
      // Parse data (extract temperature)
      int tempIndex = payload.indexOf("temp");
      String temp = payload.substring(tempIndex + 6, payload.indexOf(",", tempIndex));
      
      // Display temperature on LCD
      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.setCursor(6, 0);
      lcd.print(temp);
      lcd.print(" C");
      
      // Extract weather description
      int descIndex = payload.indexOf("description");
      String desc = payload.substring(descIndex + 14, payload.indexOf("\"", descIndex + 14));
      
      // Display description on LCD
      lcd.setCursor(0, 1);
      lcd.print(desc);
      
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();  // Free the resources
  }
  
  delay(60000);  // Update every minute
} 