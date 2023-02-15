# 1 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
# 2 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 2

//static void task1_handler(void* parameters);
//static void task2_handler(void* parameters);
static void led_green_handler(void* parameters);
static void led_red_handler(void* parameters);
static void led_yellow_handler(void* parameters);
static void button_handler(void* parameters);

void setup() {

  //TaskHandle_t task1_handle;
  //TaskHandle_t task2_handle;
  TaskHandle_t ledg_handle;
  TaskHandle_t ledr_handle;
  TaskHandle_t ledy_handle;
  TaskHandle_t btn_handle;
  TaskHandle_t volatile next_task_handle = 
# 18 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                                          __null
# 18 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                                              ;
  BaseType_t status;

  pinMode(2, 0x1);
  pinMode(4, 0x1);
  pinMode(7, 0x1);
  pinMode(8, 0x0);
/*
  Serial.begin(9600);

  status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
  configASSERT(status == pdPASS);
  status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
  configASSERT(status == pdPASS);
  */

  status=xTaskCreate(led_green_handler, "LED_green_task", 200, 
# 34 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                                                              __null
# 34 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                                                                  , 1, &ledg_handle);
  ;
  next_task_handle = ledg_handle;
  status=xTaskCreate(led_red_handler, "LED_red_task", 200, 
# 37 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                                                          __null
# 37 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                                                              , 3, &ledr_handle);
  ;
  status=xTaskCreate(led_yellow_handler, "LED_yellow_task", 200, 
# 39 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                                                                __null
# 39 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                                                                    , 2, &ledy_handle);
  ;
  status=xTaskCreate(button_handler, "Button_task", 200, 
# 41 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                                                        __null
# 41 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                                                            , 4, &btn_handle);
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

  TickType_t last_wakeup_time;
  last_wakeup_time = xTaskGetTickCount();

  BaseType_t status;

  while(1){
    digitalWrite(2, 0x1);
    do { ( void ) xTaskDelayUntil( ( &last_wakeup_time ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 1000 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 76 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
   0 
# 76 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
   /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) ); } while( 0 );
    digitalWrite(2, 0x0);
    do { ( void ) xTaskDelayUntil( ( &last_wakeup_time ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 1000 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 78 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
   0 
# 78 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
   /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) ); } while( 0 );
    status=xTaskGenericNotifyWait( ( 0 ), ( 0 ), ( 0 ), ( 
# 79 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
          __null 
# 79 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
          ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 1000 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 79 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
          0 
# 79 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
          /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) );
    if(status=( ( BaseType_t ) 1 )){
      next_task_handle = ledy_handle;
      digitalWrite(2, 0x1);
      vTaskDelete(
# 83 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                 __null
# 83 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                     );
    }
  }
}

static void led_red_handler(void* parameters){

  TickType_t last_wakeup_time;
  last_wakeup_time = xTaskGetTickCount();

  while(1){
    digitalWrite(4, 0x1);
    do { ( void ) xTaskDelayUntil( ( &last_wakeup_time ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 800 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 95 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
   0 
# 95 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
   /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) ); } while( 0 );
    digitalWrite(4, 0x0);
    do { ( void ) xTaskDelayUntil( ( &last_wakeup_time ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 800 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 97 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
   0 
# 97 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
   /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) ); } while( 0 );
  }
}

static void led_yellow_handler(void* parameters){

  TickType_t last_wakeup_time;
  last_wakeup_time = xTaskGetTickCount();

  BaseType_t status;
  while(1){
    digitalWrite(7, 0x1);
    do { ( void ) xTaskDelayUntil( ( &last_wakeup_time ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 400 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 109 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
   0 
# 109 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
   /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) ); } while( 0 );
    digitalWrite(7, 0x0);
    do { ( void ) xTaskDelayUntil( ( &last_wakeup_time ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 400 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 111 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
   0 
# 111 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
   /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) ); } while( 0 );
    status=xTaskGenericNotifyWait( ( 0 ), ( 0 ), ( 0 ), ( 
# 112 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
          __null 
# 112 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
          ), ( ( ( TickType_t ) ( ( ( uint32_t ) ( 1000 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 112 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
          0 
# 112 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
          /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ) ) );
    if(status=( ( BaseType_t ) 1 )){
      next_task_handle = ledr_handle;
      digitalWrite(7, 0x1);
      vTaskDelete(
# 116 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
                 __null
# 116 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
                     );
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
        xTaskGenericNotify( ( next_task_handle ), ( ( 0 ) ), ( 0 ), ( eNoAction ), 
# 132 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3 4
       __null 
# 132 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
       );
      }
    }
    prev_read = btn_read;
    vTaskDelay(( ( TickType_t ) ( ( ( uint32_t ) ( 10 ) * ( TickType_t ) ( (TickType_t)( (uint32_t)128000 >> (
# 136 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino" 3
              0 
# 136 "/Users/georgi/GitHub/FreeRTOS/FreeRTOS.ino"
              /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) / ( TickType_t ) 1000U ) ));
  }
}
