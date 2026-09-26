#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "display.h"
#include "button.h"
#include "temperature.h"

#include <driver/i2c.h>
#include <esp_log.h>

typedef enum
{
    enum_speed,
    enum_rpm,
    enum_engtemp,
    enum_battvolt,
    enum_consump,
    enum_fuelgaug,
    enum_temp,
    enum_END
} display_state_t;

void app_main(void)
{
    display_state_t state = enum_speed;
    uint32_t io_num;
    TickType_t last_press = 0;

    display_init();
    button_init();

    while (1)
    {
        if (xQueueReceive(button_queue, &io_num, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            TickType_t press = xTaskGetTickCount();

            if ((press - last_press) > pdMS_TO_TICKS(300))
            {
                last_press = press;
                state = (state + 1) % enum_END;

                xQueueReset(button_queue);
                printf("%d\n",state);
            }
        }

        switch (state)
        {
        case enum_speed:
            speed();
            break;

        case enum_rpm:
            rpm();
            break;

        case enum_engtemp:
            engtemp();
            break;

        case enum_battvolt:
            battvolt();
            break;

        case enum_consump:
            consump();
            break;

        case enum_fuelgaug:
            fuelgaug();
            break;

        case enum_temp:
            temp();
            break;

        default:
            break;
        }
    }
}