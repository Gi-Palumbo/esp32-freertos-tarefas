#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Definição dos semáforos (um para cada tarefa)
SemaphoreHandle_t xSem1 = NULL;
SemaphoreHandle_t xSem2 = NULL;
SemaphoreHandle_t xSem3 = NULL;

// Declaração das tarefas
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);

void app_main(void)
{
    printf("Iniciando...\n");

    // Criação dos semáforos binários
    xSem1 = xSemaphoreCreateBinary();
    xSem2 = xSemaphoreCreateBinary();
    xSem3 = xSemaphoreCreateBinary();

    if (xSem1 != NULL && xSem2 != NULL && xSem3 != NULL) {
        // Libera o semáforo da Tarefa1 para iniciar a sequência
        xSemaphoreGive(xSem1);

        // Criação das tarefas
        xTaskCreate(vTask1, "Tarefa 1", 2048, NULL, 1, NULL);
        xTaskCreate(vTask2, "Tarefa 2", 2048, NULL, 1, NULL);
        xTaskCreate(vTask3, "Tarefa 3", 2048, NULL, 1, NULL);
    }
}

// ----------------- TAREFA 1 -----------------
void vTask1(void *pvParameters)
{
    while (true) {
        if (xSemaphoreTake(xSem1, portMAX_DELAY) == pdTRUE) {
            printf("Tarefa 1 executou - giovanna palumbo\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1s ANTES de liberar
            xSemaphoreGive(xSem2); // Libera a Tarefa 2
        }
    }
}

// ----------------- TAREFA 2 -----------------
void vTask2(void *pvParameters)
{
    while (true) {
        if (xSemaphoreTake(xSem2, portMAX_DELAY) == pdTRUE) {
            printf("Tarefa 2 executou - giovanna palumbo\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1s ANTES de liberar
            xSemaphoreGive(xSem3); // Libera a Tarefa 3
        }
    }
}

// ----------------- TAREFA 3 -----------------
void vTask3(void *pvParameters)
{
    while (true) {
        if (xSemaphoreTake(xSem3, portMAX_DELAY) == pdTRUE) {
            printf("Tarefa 3 executou - giovanna palumbo\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1s ANTES de liberar
            xSemaphoreGive(xSem1); // Volta para Tarefa 1
        }
    }
}
