# 1 "/Users/georgi/GitHub/FreeRTOS/main.ino"
# 2 "/Users/georgi/GitHub/FreeRTOS/main.ino" 2

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);

void setup() {

  TaskHandle_t task1_handle;
  TaskHandle_t task2_handle;
  BaseType_t status;

  status = xTaskCreate(task1_handler, "Task-1", 200, "Hello World from Task-1", 2, &task1_handle);
  ;
  status = xTaskCreate(task2_handler, "Task-2", 200, "Hello World from Task-2", 2, &task2_handle);
  ;

}

void loop() {}

static void task1_handler(void* parameters){

}

static void task2_handler(void* parameters){

}
