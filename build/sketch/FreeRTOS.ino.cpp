#include <Arduino.h>
#line 1 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
#include <Arduino_FreeRTOS.h>

//static void task1_handler(void* parameters);
//static void task2_handler(void* parameters);
static void led_green_handler(void* parameters);
static void led_red_handler(void* parameters);
static void led_yellow_handler(void* parameters);
static void button_handler(void* parameters);

#line 10 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
void setup();
#line 51 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
void loop();
#line 53 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
static void task1_handler(void* parameters);
#line 60 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
static void task2_handler(void* parameters);
#line 10 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
void setup() {

  //TaskHandle_t task1_handle;
  //TaskHandle_t task2_handle;
  TaskHandle_t ledg_handle;
  TaskHandle_t ledr_handle;
  TaskHandle_t ledy_handle;
  TaskHandle_t btn_handle;
  TaskHandle_t volatile next_task_handle = NULL;
  BaseType_t status;

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
/*
  Serial.begin(9600);

  status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
  configASSERT(status == pdPASS);
  status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
  configASSERT(status == pdPASS);
  */

  status=xTaskCreate(led_green_handler, "LED_green_task", 200, NULL, 1, &ledg_handle);
  configASSERT(status=pdPASS);
  next_task_handle = ledg_handle;
  status=xTaskCreate(led_red_handler, "LED_red_task", 200, NULL, 3, &ledr_handle);
  configASSERT(status=pdPASS);
  status=xTaskCreate(led_yellow_handler, "LED_yellow_task", 200, NULL, 2, &ledy_handle);
  configASSERT(status=pdPASS);
  status=xTaskCreate(button_handler, "Button_task", 200, NULL, 4, &btn_handle);
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

  TickType_t last_wakeup_time;
  last_wakeup_time = xTaskGetTickCount();

  BaseType_t status;

  while(1){
    digitalWrite(2, HIGH);
    vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(1000));
    digitalWrite(2, LOW);
    vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(1000));
    status=xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(1000));
    if(status=pdTRUE){
      next_task_handle = ledy_handle;
      digitalWrite(2, HIGH);
      vTaskDelete(NULL);
    }
  }
}

static void led_red_handler(void* parameters){

  TickType_t last_wakeup_time;
  last_wakeup_time = xTaskGetTickCount();

  BaseType_t status;

  while(1){
    digitalWrite(4, HIGH);
    vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(800));
    digitalWrite(4, LOW);
    vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(800));
    status=xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(800));
    if(status=pdTRUE){
      next_task_handle = NULL;
      digitalWrite(4, HIGH);
      vTaskDelete(NULL);
      vTaskDelete(btn_handle);
    }
  } 
}

static void led_yellow_handler(void* parameters){

  TickType_t last_wakeup_time;
  last_wakeup_time = xTaskGetTickCount();

  BaseType_t status;
  while(1){
    digitalWrite(7, HIGH);
    vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(400));
    digitalWrite(7, LOW);
    vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(400));
    status=xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(400));
    if(status=pdTRUE){
      next_task_handle = ledr_handle;
      digitalWrite(7, HIGH);
      vTaskDelete(NULL);
    }
   }
  }


static void button_handler(void* parameters){

  uint8_t btn_read=0;
  uint8_t prev_read=0;

  while(1){
    btn_read = digitalRead(8);

    if(btn_read){
      if(! prev_read){
        xTaskNotify(next_task_handle,0,eNoAction);
      }
    }
    prev_read = btn_read;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
