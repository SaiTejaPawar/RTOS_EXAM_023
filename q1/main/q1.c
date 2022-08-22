#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle, task5_handle;
QueueHandle_t msg_queue;
void task_1(void *data)
{
    while (1)
    {
        printf("Here is the task 1 created\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void task_2(void *data)
{
    while (1)
    {
        printf("Here task 2 is created\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void task_3(void *data)
{
    while (1)
    {
        printf("Here task 3 is created\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void task_4(void *data)
{
    int my_data = 0;
    printf(" Here is task 4 is created\n");
    while (1)
    {
        my_data++;
        xQueueSend(msg_queue, &my_data, pdMS_TO_TICKS(10000));
        printf("Task 4  sending data to Task 5\n");
    }
}

void task_5(void *data)
{
    int buffer;
    printf("Here  task 5 is created\n");
    while (1)
    {
        xQueueReceive(msg_queue, &buffer, pdMS_TO_TICKS(10000));
        printf("Task 5 Received Data is %d\n", buffer);
    }
}

void app_main(void)
{
    msg_queue = xQueueCreate(2, sizeof(int));
    xTaskCreate(task_1, "Task1", 2048, NULL, 5, &task1_handle);
    xTaskCreate(task_2, "Task2", 2048, NULL, 6, &task2_handle);
    xTaskCreate(task_3, "Task3", 2048, NULL, 7, &task3_handle);
    xTaskCreate(task_4, "Task4", 2048, NULL, 8, &task4_handle);
    xTaskCreate(task_5, "Task5", 2048, NULL, 9, &task5_handle);
}