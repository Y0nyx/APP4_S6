#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define TX_PIN 13
#define RX_PIN 12
#define BIT_PERIOD 2000  // Bit period in microseconds

void setup() {
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
  Serial.begin(115200);
  
  // Create the Manchester receiver task
  xTaskCreate(receiveManchesterTask, "ManchRx", 1024, NULL, 1, NULL);
  
  // Create the Manchester transmitter task
  xTaskCreate(sendManchesterTask, "ManchTx", 1024, NULL, 1, NULL);
}

void loop() {
  // Nothing needed here, all work is done in the tasks
}

void receiveManchesterTask(void *parameter) {
  while (1) {
    byte data = 0;
    for (int i = 7; i >= 0; i--) {
      // Wait for a transition
      while (digitalRead(RX_PIN) == HIGH);
      while (digitalRead(RX_PIN) == LOW);
      
      // Wait for half a bit period and then read the bit
      vTaskDelay(BIT_PERIOD / 2 / portTICK_PERIOD_MS);
      bool bit = digitalRead(RX_PIN);
      data |= (bit << i);
    }
    
    // Print out the received byte
    Serial.println(data, HEX);
  }
}

void sendManchesterTask(void *parameter) {
  byte data = 0x5A;  // Example data byte to send
  
  while (1) {
    for (int i = 7; i >= 0; i--) {
      bool bit = data & (1 << i);
      if (bit) {
        digitalWrite(TX_PIN, HIGH);
        vTaskDelay(BIT_PERIOD / 2 / portTICK_PERIOD_MS);
        digitalWrite(TX_PIN, LOW);
        vTaskDelay(BIT_PERIOD / 2 / portTICK_PERIOD_MS);
      } else {
        digitalWrite(TX_PIN, LOW);
        vTaskDelay(BIT_PERIOD / 2 / portTICK_PERIOD_MS);
        digitalWrite(TX_PIN, HIGH);
        vTaskDelay(BIT_PERIOD / 2 / portTICK_PERIOD_MS);
      }
    }
    
    // Delay before sending the next byte
    vTaskDelay(BIT_PERIOD / portTICK_PERIOD_MS);
  }
}
