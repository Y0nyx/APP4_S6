#include <Manchester.h>

#define TX_PIN 1
#define RX_PIN 3

void TaskReceiveManchester(void *pvParameters);
void TaskSendManchester(void *pvParameters);

TaskHandle_t receive_manchester_handle;
TaskHandle_t send_manchester_handle;


void setup() {
  Serial.begin(9600);
  man.workAround1MhzTinyCore();
  man.setupTransmit(TX_PIN, MAN_9600);

  xTaskCreate(
    TaskReceiveManchester,
    "Receive Manchester",
    2048,
    NULL,
    1,
    receive_manchester_handle
  );

  xTaskCreate(
    TaskSendManchester,
    "Send Manchester",
    2048, 
    NULL,
    2,
    send_manchester_handle
  )
}

void loop(){
  if(receive_manchester_handle != NULL){ 
    delay(10000);
    vTaskDelete(receive_manchester_handle); 
    receive_manchester_handle = NULL; 
  }

  if(send_manchester_handle != NULL){ 
    delay(10000);
    vTaskDelete(send_manchester_handle); 
    send_manchester_handle = NULL; 
  }
}



/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters){  // This is a task.
  uint32_t blink_delay = *((uint32_t*)pvParameters);

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;){ // A Task shall never return or exit.
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    // arduino-esp32 has FreeRTOS configured to have a tick-rate of 1000Hz and portTICK_PERIOD_MS
    // refers to how many milliseconds the period between each ticks is, ie. 1ms.
    delay(blink_delay);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(blink_delay);
  }
}

void TaskAnalogRead(void *pvParameters){  // This is a task.
  (void) pvParameters;
  // Check if the given analog pin is usable - if not - delete this task
  if(!adcAttachPin(ANALOG_INPUT_PIN)){
    Serial.printf("TaskAnalogRead cannot work because the given pin %d cannot be used for ADC - the task will delete itself.\n", ANALOG_INPUT_PIN);
    analog_read_task_handle = NULL; // Prevent calling vTaskDelete on non-existing task
    vTaskDelete(NULL); // Delete this task
  }

  for (;;){
    // read the input on analog pin:
    int sensorValue = analogRead(ANALOG_INPUT_PIN);
    // print out the value you read:
    Serial.println(sensorValue);
    delay(100); // 100ms delay
  }
}

void TaskReceiveManchester(void *pvParameters){

}

void TaskSendManchester(void *pvParameters){
  (void) pvParameters;



}
