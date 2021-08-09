// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

#ifndef __MAIN_H__
#define __MAIN_H__


// Config
// Temperature regulation
#define TEMP_REG_ON             318     // C
#define TEMP_REG_OFF            320
#define TEMP_READY              300
#define TEMP_STOP               180

// Filter configuration (temperature measurement)
#define AVERAGE_NUM             10
#define COUNTER_NUM             10
#define MEASURE_PER_MS          100

#define DISPLAY_UPDATE_PER_MS   1000



// Pins
// SPI2 to connect with temperature sensor
#define SPI_NSS_PIN             GPIOB, 12
#define SPI_SCK_PIN             GPIOB, 13
#define SPI_MISO_PIN            GPIOB, 14
// I2C1 to connect 1602a display (for debug only)
#define I2C_SCK_PIN             GPIOB, 6
#define I2C_SDA_PIN             GPIOB, 7
// LED indicators
#define LED1_RED_PIN            GPIOA, 4
#define LED1_GREEN_PIN          GPIOA, 3
#define LED2_RED_PIN            GPIOA, 2
#define LED2_GREEN_PIN          GPIOA, 1
// Actuators
#define HEATER_CTRL_PIN         GPIOB, 11
#define PUMP_CTRL_PIN           GPIOB, 10
// Start button
#define START_BTN_PIN           GPIOA, 0






#endif



