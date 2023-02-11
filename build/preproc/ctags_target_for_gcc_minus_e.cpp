# 1 "/Users/georgi/GitHub/FreeRTOS/main.ino"
# 2 "/Users/georgi/GitHub/FreeRTOS/main.ino" 2

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);

void setup() {

  TaskHandle_t task1_handle;
  TaskHandle_t task2_handle;
  TaskHandle_t task3_handle;
  BaseType_t status;
  pinMode(2, 0x1);
  pinMode(4, 0x1);
  pinMode(7, 0x1);
/*
  Serial.begin(9600);

  status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
  configASSERT(status == pdPASS);
  status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
  configASSERT(status == pdPASS);
  */

  status=xTaskCreate(led_green_handler, "LED_green_task", 200, 
# 24 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
                                                              __null
# 24 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                                                                  , 2, &task1_handle);
  ;
  status=xTaskCreate(led_red_handler, "LED_red_task", 200, 
# 26 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
                                                          __null
# 26 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                                                              , 2, &task2_handle);
  ;
  status=xTaskCreate(led_yellow_handler, "LED_yellow_task", 200, 
# 28 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
                                                                __null
# 28 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                                                                    , 2, &task3_handle);
  ;

  /*Start the FreeRTOS Scheduler*/
  vTaskStartScheduler();

  /*If control reaches here, than the launch of the scheduler failed due to insufficient memory in heap*/

}

void loop() {}

static void task1_handler(void* parameters){
  while(1){
    Serial.println((char*) parameters);
    vPortYield();
  }
}

static void task2_handler(void* parameters){
  while(1){
    Serial.println((char*) parameters);
    vPortYield();
  }
}

static void led_green_handler(void* parameters){
  while(1){
    digitalWrite(2, 0x1);
    vPortDelay(1000);
    digitalWrite(2, 0x0);
    vPortDelay(1000);
  }
}

static void led_red_handler(void* parameters){
  while(1){
    digitalWrite(4, 0x1);
    vPortDelay(800);
    digitalWrite(4, 0x0);
    vPortDelay(800);
  }
}

static void led_yellow_handler(void* parameters){
  while(1){
    digitalWrite(7, 0x1);
    vPortDelay(400);
    digitalWrite(7, 0x0);
    vPortDelay(400);
  }
}
