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