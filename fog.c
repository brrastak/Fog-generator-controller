// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//user
#include "fog.h"
#include "main.h"
#include "spi.h"
#include "gpio.h"


uint16_t spi_buf[2];


// Get temperature
bool GetTemp(int16_t * temp_value)
{
    // Raw data
    int32_t tc_raw;
    // Thermocouple data & error
    int32_t tc_temp;
    static int32_t average = 0;
    bool tc_error = false;
    static int err_cnt = 0;
    
    // Get sensor data from SPI
    TransmitSpi(spi_buf, 2);
    ReceiveSpi(spi_buf, 2);
        
    while (ReceivedSpi() == false)
        ;
    DeselectChipSpi();
    
    // Decode data
    tc_raw = (spi_buf[0] << 16) + spi_buf[1];
    tc_error = (tc_raw & (1 << 16)) != 0;
    tc_temp = (tc_raw & (0xFFF << 20)) >> 20;
    
    // Get average temperature value (if no error)
    if (tc_error == false) {
        
        average = average * (AVERAGE_NUM - 1) + tc_temp;
        average /= AVERAGE_NUM;
    }
    
    // Detect thermocouple error
    if (tc_error == true)
        err_cnt++;
    else
        err_cnt = 0;
    if (err_cnt >= COUNTER_NUM)
        err_cnt = COUNTER_NUM;
    else
        tc_error = false;
    
    // Return value
    *temp_value = tc_temp;
    return tc_error;
        
}
// Actuators
void EnableHeater(void)
{
    SetPin(HEATER_CTRL_PIN);
}
void DisableHeater(void)
{
    ResetPin(HEATER_CTRL_PIN);
}
void EnablePump(void)
{
    SetPin(PUMP_CTRL_PIN);
}
void DisablePump(void)
{
    ResetPin(PUMP_CTRL_PIN);
}
// Indicators
void IndicateTempOk(void)
{
    SetPin(LED2_GREEN_PIN);
    ResetPin(LED2_RED_PIN);
}
void IndicateTempNotOk(void)
{
    ResetPin(LED2_GREEN_PIN);
    SetPin(LED2_RED_PIN);
}
void IndicateHeaterOn(void)
{
    SetPin(LED1_RED_PIN);
}
void IndicateHeaterOff(void)
{
    ResetPin(LED1_RED_PIN);
}

