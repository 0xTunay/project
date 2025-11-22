/* 

1. Архитектура

Система состоит из трёх задач:

A) TaskVoltageMonitor

Период: 200–500 мс (задай сам).
Опрашивает АЦП или имитацию АЦП (например, рандом или линейное уменьшение).
Результат кладёт в очередь xQueueVoltage.
Если напряжение ниже порога — отправляет событие в LowBatteryEventGroup с помощью флага LOW_BAT_BIT.

B) TaskTelemetry

Период: 2–5 секунд.
Забирает из очереди последнее измеренное напряжение.
Формирует пакет телеметрии (JSON строка или бинарь — на выбор).
Отправляет в UART или имитирует отправку через ESP_LOGI.
Может быть полезен мьютекс, если логика записи разделяет общий ресурс.

C) TaskLowBatteryHandler

Ждёт события LOW_BAT_BIT из LowBatteryEventGroup.
При появлении события:
Логирует предупреждение
Или мигает LED (через GPIO или имитацию)
Или отправляет отдельный "alarm"-пакет в UART
После обработки очищает бит, чтобы снова ждать.

2. Синхронизация

Ты обязан использовать:
Очередь (queue) — обмен ADC-данными между задачами.
Event Group — событие “низкий заряд”.
Мьютекс/семафор — защита UART или общего буфера.

3. Ограничения
Все задачи должны иметь корректно расставленные приоритеты.
Никаких блокирующих задержек сверх разумных.
Никаких глобальных переменных без защиты.

*/
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/list.h"

#include "freertos/event_groups.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include <stdlib.h>

#define uxQueueLength 5 
#define uxItemSize    sizeof(int)

static const char * TAG = "MyModule";


TaskHandle_t TaskLowBatteryHandle = NULL;
QueueHandle_t xQueueVoltage = NULL;


void TaskVoltageMonitor(void *pvParamentrs) {
    BaseType_t xReturn;

    for(;;) {
    
    }

    vTaskDelay(pdMS_TO_TICKS(500));

}
void TaskTelemetry(void *pvParamentrs) {

    for(;;){}


    vTaskDelay(pdMS_TO_TICKS(1000));

}

void TaskLowBatteryHandler(void *pvParamentrs) {

    for(;;){}

    vTaskDelay(pdMS_TO_TICKS(1000));

}
void app_main(void) {

   xQueueVoltage = xQueueCreate(uxQueueLength, uxItemSize);
    if (xQueueVoltage == NULL) {
        ESP_LOGW(TAG, "Create FALSE\n");
    } else {
        ESP_LOGI(TAG, "Create SUCCESS\n");
    }    
    xTaskCreate(TaskLowBatteryHandler, "TaskLowBatteryHandler", 2048, NULL, 3 ,&TaskLowBatteryHandle);
    xTaskCreate(TaskVoltageMonitor, "TaskVoltageMonitor", 2048, NULL, 1, NULL);
    xTaskCreate(TaskTelemetry, "TaskTelemetry", 2048, NULL, 1 ,NULL);
}
