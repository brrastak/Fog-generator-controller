// STM32F103
#include "stm32f10x.h"

// user
#include "init.h"
#include "main.h"
#include "gpio.h"
#include "debug_led.h"


void InitRcc(void)
{
    // port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // port C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    // TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // TIM4
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    // SPI2
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    // I2C1
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
}
void InitInterrupt(void)
{
    // I2C1
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    // SPI2
    NVIC_EnableIRQ(SPI2_IRQn);
}
void InitGpio(void)
{
    // SPI2 to connect with temperature sensor
    SetGpioMode(SPI_NSS_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(SPI_SCK_PIN, PIN_MODE_2MHZ_AFPP);
    SetGpioMode(SPI_MISO_PIN, PIN_MODE_IFLOAT);
    // I2C1 to connect 1602a display (for debug only)
    SetGpioMode(I2C_SCK_PIN, PIN_MODE_2MHZ_AFOD);
    SetGpioMode(I2C_SDA_PIN, PIN_MODE_2MHZ_AFOD);
    // LED indicators
    SetGpioMode(LED1_RED_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LED1_GREEN_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LED2_RED_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(LED2_GREEN_PIN, PIN_MODE_2MHZ_OPP);
    // Actuators
    SetGpioMode(HEATER_CTRL_PIN, PIN_MODE_2MHZ_OPP);
    SetGpioMode(PUMP_CTRL_PIN, PIN_MODE_2MHZ_OPP);
    // Start button
    SetGpioMode(START_BTN_PIN, PIN_MODE_IFLOAT);
    
    // Debug LED
    SetGpioMode(LED_PIN, PIN_MODE_2MHZ_OPP);

}
