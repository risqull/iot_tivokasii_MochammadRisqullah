
>👩🏻‍💻Feby 🗓 7 June 2025

# IRIS FLOWER CLASSIFICATION USING THE TENSORFLOW LITE MODEL ON ESP 32 MICROCONTROLLER



---
## **A. Introduction**

This practicum aims to implement the Iris dataset classification model locally on the ESP32 microcontroller using Tiny Machine Learning (TinyML) technology with the help of the TensorFlow Lite for Microcontrollers (TFLM) library. The model used is a classification model with three classes (Setosa, Versicolor, Virginica) based on four feature parameters (length and width of sepals and petals). 

## **B. Diagram**
This diagram was created using the ESP32 Microcontroller based Wokwi simulation.
<img width="1020" alt="1" src="https://github.com/user-attachments/assets/e2b9712c-cd69-4780-83b7-9f56dc4629b4" />









```json
{
  "version": 1,
  "author": "subairi",
  "editor": "wokwi",
  "parts": [ { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0, "attrs": {} } ],
  "connections": [ [ "esp:TX", "$serialMonitor:RX", "", [] ], [ "esp:RX", "$serialMonitor:TX", "", [] ] ],
  "dependencies": {}
}




```
## **C. Program Code**
This program code is for setting the temperature and humidity, as well as the connection to Blynk.

```cpp
#include <Arduino.h>
#include <iris_model.h>
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

#define ARENA_SIZE 2000

Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;


void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("__TENSORFLOW IRIS__");
    tf.setNumInputs(4);
    tf.setNumOutputs(3);
    tf.resolver.AddFullyConnected();
    tf.resolver.AddSoftmax();
    
    while (!tf.begin(irisModel).isOk())
        Serial.println(tf.exception.toString());
}


void loop() {
    if (!tf.predict(x0).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }
    Serial.print("expcted class 0, predicted class ");
    Serial.println(tf.classification);

    if (!tf.predict(x1).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }
    Serial.print("expcted class 1, predicted class ");
    Serial.println(tf.classification);
    
    if (!tf.predict(x2).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }
    Serial.print("expcted class 2, predicted class ");
    Serial.println(tf.classification);
    
    
    Serial.print("It takes ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us for a single prediction");
    delay(1000);
}



```
## **C. Result**
TensorFlow Lite running on the ESP32 board successfully classified the IRIS test data. Although a warning was raised about using the AddBuiltin operation more than once, this did not interfere with the inference. The prediction results showed that the model was able to map the test data to the appropriate classes, such as “expected class 0, predicted class 0”, and so on, with an average inference time of about 1086 microseconds per prediction. This shows that the model can run quite fast and efficiently on edge devices such as the ESP32, making it suitable for resource-constrained embedded AI applications.
<img width="1020" alt="2" src="https://github.com/user-attachments/assets/cd72235a-d589-4662-9632-fb0be6d7f73f" />



For more details, please follow the implementation steps in the Iris check report (pdf).
