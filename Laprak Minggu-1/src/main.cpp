#include <Arduino.h> // Wajib untuk PlatformIO + ESP32

// Deklarasi pin untuk setiap lampu traffic light
int lampuMerah = 26;
int lampuKuning = 33;
int lampuHijau = 25;

void setup() {
  Serial.begin(115200); // Inisialisasi komunikasi Serial
  Serial.println("Traffic Light Simulation with ESP32");

  // Atur pin sebagai OUTPUT
  pinMode(lampuMerah, OUTPUT);
  pinMode(lampuKuning, OUTPUT);
  pinMode(lampuHijau, OUTPUT);
}

void loop() {
  // Lampu Merah ON selama 20 detik
  digitalWrite(lampuMerah, HIGH);
  digitalWrite(lampuKuning, LOW);
  digitalWrite(lampuHijau, LOW);
  Serial.println("Lampu Merah ON");
  delay(10000); // Tunggu 10 detik

  // Lampu Kuning ON selama 5 detik
  digitalWrite(lampuMerah, LOW);
  digitalWrite(lampuKuning, HIGH);
  digitalWrite(lampuHijau, LOW);
  Serial.println("Lampu Kuning ON");
  delay(3000); // Tunggu  3 detik

  // Lampu Hijau ON selama 15 detik
  digitalWrite(lampuMerah, LOW);
  digitalWrite(lampuKuning, LOW);
  digitalWrite(lampuHijau, HIGH);
  Serial.println("Lampu Hijau ON");
  delay(10000); // Tunggu 10 detik
}