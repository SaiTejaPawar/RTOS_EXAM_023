#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t task1_handle, task2_handle, task3_handle;
TimerHandle_t one_shot_timer;

void timer_callback()
{
    printf("started the timer/n");
    
}

void task1 (void *data)
{
    while(1)
    {
    printf("Task 1 is created\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task2 (void *data)
{
    while(1)
    {
    printf("Task 2 is created\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void task3 (void *data)
{
    while(1)
    {
    printf("Task 3 is created \n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    one_shot_timer = xTimerCreate("timer", pdMS_TO_TICKS(10000), pdFALSE , 0, timer_callback);
    xTimerStart(one_shot_timer, 0);
    }
}

void app_main(void)
{
xTaskCreate(task1, "TASK 1", 2048, NULL, 5, &task1_handle);
xTaskCreate(task2, "TASK 2", 2048, NULL, 6, &task2_handle);
xTaskCreate(task3, "TAsk 3", 2048, NULL, 7, &task3_handle);
}
