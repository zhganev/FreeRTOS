# 1 "/Users/georgi/GitHub/FreeRTOS/main.ino"
/*
 * Example of a basic FreeRTOS queue
 * https://www.freertos.org/Embedded-RTOS-Queues.html
 */

// Include Arduino FreeRTOS library
# 8 "/Users/georgi/GitHub/FreeRTOS/main.ino" 2

// Include queue support
# 11 "/Users/georgi/GitHub/FreeRTOS/main.ino" 2

/* 
 * Declaring a global variable of type QueueHandle_t 
 * 
 */
QueueHandle_t integerQueue;

void setup() {

  /**
   * Create a queue.
   * https://www.freertos.org/a00116.html
   */
  integerQueue = xQueueGenericCreate( ( 10 ), ( /* Queue length*/ sizeof(int) /* Queue item size*/ ), ( ( ( uint8_t ) 0U ) ) )

                               ;

  if (integerQueue != 
# 28 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
                     __null
# 28 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                         ) {

    // Create task that consumes the queue if it was created.
    xTaskCreate(TaskSerial, // Task function
                "Serial", // A name just for humans
                128, // This stack size can be checked & adjusted by reading the Stack Highwater
                
# 34 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
               __null
# 34 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                   ,
                2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
                
# 36 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
               __null
# 36 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                   );


    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskAnalogRead, // Task function
                "AnalogRead", // Task name
                128, // Stack size
                
# 43 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
               __null
# 43 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                   ,
                1, // Priority
                
# 45 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
               __null
# 45 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                   );

  }


  xTaskCreate(TaskBlink, // Task function
              "Blink", // Task name
              128, // Stack size 
              
# 53 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
             __null
# 53 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                 ,
              0, // Priority
              
# 55 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3 4
             __null 
# 55 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                  );

}

void loop() {}


/**
 * Analog read task
 * Reads an analog input on pin 0 and send the readed value through the queue.
 * See Blink_AnalogRead example.
 */
void TaskAnalogRead(void *pvParameters)
{
  (void) pvParameters;

  for (;;)
  {
    // Read the input on analog pin 0:
    int sensorValue = analogRead(A0);

    /**
     * Post an item on a queue.
     * https://www.freertos.org/a00117.html
     */
    xQueueGenericSend( ( integerQueue ), ( &sensorValue ), ( ( TickType_t ) 0xffff ), ( ( BaseType_t ) 0 ) );

    // One tick delay (15ms) in between reads for stability
    vTaskDelay(1);
  }
}

/**
 * Serial task.
 * Prints the received items from the queue to the serial monitor.
 */
void TaskSerial(void * pvParameters) {
  (void) pvParameters;

  // Init Arduino serial
  Serial.begin(9600);

  // Wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  while (!Serial) {
    vTaskDelay(1);
  }

  int valueFromQueue = 0;

  for (;;)
  {

    /**
     * Read an item from a queue.
     * https://www.freertos.org/a00118.html
     */
    if (xQueueReceive(integerQueue, &valueFromQueue, ( TickType_t ) 0xffff) == ( ( ( BaseType_t ) 1 ) )) {
      Serial.println(valueFromQueue);
    }
  }
}

/* 
 * Blink task. 
 * See Blink_AnalogRead example. 
 */
void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  pinMode(13, 0x1);

  for (;;)
  {
    digitalWrite(13, 0x1);
    vTaskDelay( 250 / ( (TickType_t) 1000 / ( (TickType_t)( (uint32_t)128000 >> (
# 130 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3
                     0 
# 130 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                     /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) );
    digitalWrite(13, 0x0);
    vTaskDelay( 250 / ( (TickType_t) 1000 / ( (TickType_t)( (uint32_t)128000 >> (
# 132 "/Users/georgi/GitHub/FreeRTOS/main.ino" 3
                     0 
# 132 "/Users/georgi/GitHub/FreeRTOS/main.ino"
                     /* portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick*/ + 11) ) ) /* 2^11 = 2048 WDT scaler for 128kHz Timer*/ ) );
  }
}
