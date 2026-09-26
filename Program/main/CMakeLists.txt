idf_component_register(SRCS "button.c" "temperature.c" "MAIN.c" "display.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_i2c u8g2 u8g2-hal-esp-idf esp_driver_gpio esp_timer)
