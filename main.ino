#include <Arduino_FreeRTOS.h>

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);

void setup() {

  TaskHandle_t task1_handle;
  TaskHandle_t task2_handle;
  BaseType_t status;

  Serial.begin(9600);

  status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
  configASSERT(status == pdPASS);
  status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
  configASSERT(status == pdPASS);

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