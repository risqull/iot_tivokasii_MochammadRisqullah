#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6lVxCrWtH"
#define BLYNK_TEMPLATE_NAME "TugasIot"
#define BLYNK_AUTH_TOKEN "JXgSr6ACZ6oSp8ZnBe3R-f1tv8DGKleN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h> 

char auth[] = BLYNK_AUTH_TOKEN; // Auth Token
char ssid[] = "Wokwi-GUEST"; // Nama hotspot yang digunakan
char pass[] = ""; // Password hotspot yang digunakan

const int DHT_PIN = 15;

int value0, value1, value2, value3, value6;

byte LED_R = 26;
byte LED_Y = 27;
byte LED_G = 14;
byte LED_B = 12;

DHTesp dht;
BlynkTimer timer;

// Fungsi untuk mengirimkan data sensor ke Blynk
void sendSensor() {
    TempAndHumidity data = dht.getTempAndHumidity();

    Serial.print("% Temperature: ");
    Serial.print(data.temperature);
    Serial.println("C ");
    Serial.print("% Kelembaban: ");
    Serial.print(data.humidity);
    Serial.println("% ");

    Blynk.virtualWrite(V3, data.temperature); // Kirim suhu ke V3 
    Blynk.virtualWrite(V1, data.humidity); // Kirim kelembaban ke v1
}


BLYNK_WRITE(V6) {
  int nilaiBacaIO = param.asInt();
  digitalWrite(LED_R, nilaiBacaIO);
  Blynk.virtualWrite(V6, nilaiBacaIO); 
}


void setup() {
    Serial.begin(115200);
    dht.setup(DHT_PIN, DHTesp::DHT22);
    
    pinMode(LED_R, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    Blynk.begin(auth, ssid, pass); // Mulai Blynk

    // Jika menggunakan Wokwi, gunakan mode simulasi WiFi
    #ifdef WOKWI
        Blynk.connectWiFi(ssid, pass);
        Blynk.config(auth);
    #endif

    timer.setInterval(1000, sendSensor); // Kirim data setiap 1000ms
}

void loop() {
    Blynk.run();
    timer.run();
}