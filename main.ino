#include <Arduino_FreeRTOS.h>

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);

void setup() {

  TaskHandle_t task1_handle;
  TaskHandle_t task2_handle;
  TaskHandle_t task3_handle;
  BaseType_t status;
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
/*
  Serial.begin(9600);

  status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
  configASSERT(status == pdPASS);
  status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
  configASSERT(status == pdPASS);
  */

  status=xTaskCreate(led_green_handler, "LED_green_task", 200, NULL, 2, &task1_handle);
  configASSERT(status=pdPASS);
  status=xTaskCreate(led_red_handler, "LED_red_task", 200, NULL, 2, &task2_handle);
  configASSERT(status=pdPASS);
  status=xTaskCreate(led_yellow_handler, "LED_yellow_task", 200, NULL, 2, &task3_handle);
  configASSERT(status=pdPASS);

  /*Start the FreeRTOS Scheduler*/
  vTaskStartScheduler();

  /*If control reaches here, than the launch of the scheduler failed due to insufficient memory in heap*/

}

void loop() {}

static void task1_handler(void* parameters){
  while(1){
    Serial.println((char*) parameters);
    taskYIELD();
  }
}

static void task2_handler(void* parameters){
  while(1){
    Serial.println((char*) parameters);
    taskYIELD();
  }
}

static void led_green_handler(void* parameters){
  while(1){
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
  }
}

static void led_red_handler(void* parameters){
  while(1){
    digitalWrite(4, HIGH);
    delay(800);
    digitalWrite(4, LOW);
    delay(800);
  }
}

static void led_yellow_handler(void* parameters){
  while(1){
    digitalWrite(7, HIGH);
    delay(400);
    digitalWrite(7, LOW);
    delay(400);
  }
}