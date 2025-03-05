#include <Arduino.h>

// Definisikan pin untuk tombol dan LED
const int button1Pin = 34;  // Tombol 1
const int button2Pin = 35;  // Tombol 2
const int button3Pin = 32;  // Tombol 3

const int led1Pin = 23;     // LED merah
const int led2Pin = 22;     // LED kuning
const int led3Pin = 21;     // LED hijau

// Variabel untuk debouncing
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  // Inisialisasi pin tombol sebagai input
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  // Inisialisasi pin LED sebagai output
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  // Matikan semua LED pada awal
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
}

void loop() {
  // Membaca status dari tombol dengan debounce
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);

  // Pastikan tombol ditekan dalam waktu yang lebih lama dari debounceDelay
  if (millis() - lastDebounceTime > debounceDelay) {
    // Logika Tombol 1 (Tombol ditekan, LED merah berkedip 5 kali)
    if (button1State == LOW) {
      lastDebounceTime = millis();
      for (int i = 0; i < 5; i++) {
        digitalWrite(led1Pin, HIGH);  // Nyalakan LED merah
        delay(500);                   // Tunggu 500ms
        digitalWrite(led1Pin, LOW);   // Matikan LED merah
        delay(500);                   // Tunggu 500ms
      }
    }

    // Logika Tombol 2 (Tombol ditekan, LED merah dan hijau berkedip bergantian 3 kali)
    if (button2State == LOW) {
      lastDebounceTime = millis();
      for (int i = 0; i < 3; i++) {  // Ubah dari 5 ke 3
        digitalWrite(led1Pin, HIGH);  // Nyalakan LED merah
        digitalWrite(led3Pin, LOW);   // Matikan LED hijau
        delay(500);                   // Tunggu 500ms
        digitalWrite(led1Pin, LOW);   // Matikan LED merah
        digitalWrite(led3Pin, HIGH);  // Nyalakan LED hijau
        delay(500);                   // Tunggu 500ms
      }
      // Matikan kedua LED setelah selesai
      digitalWrite(led1Pin, LOW);
      digitalWrite(led3Pin, LOW);
    }

    // Logika Tombol 3 (Tombol ditekan, LED merah, kuning, dan hijau berkedip bergantian)
    if (button3State == LOW) {
      lastDebounceTime = millis();
      for (int i = 0; i < 5; i++) {
        digitalWrite(led1Pin, HIGH);  // Nyalakan LED merah
        digitalWrite(led2Pin, LOW);   // Matikan LED kuning
        digitalWrite(led3Pin, LOW);   // Matikan LED hijau
        delay(500);                   // Tunggu 500ms

        digitalWrite(led1Pin, LOW);   // Matikan LED merah
        digitalWrite(led2Pin, HIGH);  // Nyalakan LED kuning
        delay(500);                   // Tunggu 500ms

        digitalWrite(led2Pin, LOW);   // Matikan LED kuning
        digitalWrite(led3Pin, HIGH);  // Nyalakan LED hijau
        delay(500);                   // Tunggu 500ms

        digitalWrite(led3Pin, LOW);   // Matikan LED hijau
      }
    }
  }
}