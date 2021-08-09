// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//user
#include "main.h"
#include "init.h"
#include "gpio.h"
#include "debug_led.h"
#include "timer.h"
#include "i2c.h"
#include "spi.h"
#include "display.h"
#include "fog.h"
#include "button.h"


char disp_buf[20];

// Thermocouple temp
int16_t temp;
bool error = false;

// Flags
bool heat_on = false;
bool pump_on = false;


int main()
{    
    // System init
    InitRcc();
    InitGpio();
    InitSysTick();
    InitSpi();
    InitI2c();
    InitInterrupt();
    
    InitDisp();
    TurnLedOff();

    
    // Time counters
    uint32_t temp_cnt;
    uint32_t disp_cnt;
    uint32_t btn_cnt;
    
    ResetCounter(&temp_cnt);
    ResetCounter(&disp_cnt);
    ResetCounter(&btn_cnt);
    
    // Start button
    btn_t StartBtn = {START_BTN_PIN, 0, 20, false, false, false};
    
    
    while (true) {
        
        // Get new temperature value
        if (IfDelayPassed(&temp_cnt, MEASURE_PER_MS))
            error = GetTemp(&temp);
        
        // Get start button state
        if (IfDelayPassed(&btn_cnt, 1)) {
            
            CheckBtn(&StartBtn);
        }
        
        // Update display
        if (IfDelayPassed(&disp_cnt, DISPLAY_UPDATE_PER_MS)) {
        
            ClrScr();
            delay_ms(2);
            
            if (error == true)
                WriteLine("ERROR");
            else {
            
                sprintf(disp_buf, "  T: %iC", temp);
                WriteString(disp_buf, strlen(disp_buf));
            }
        
            //BlinkLed();
        }
        
        // Start/stop pump
        if (WasPressed(&StartBtn) == true)
            pump_on = ! pump_on;
        // Stop pump at low temp
        if (temp < TEMP_STOP)
            pump_on = false;

        // Pump control
        if (pump_on == true) {
            
            EnablePump();
            TurnLedOn();
        }
        else {
            
            DisablePump();
            TurnLedOff();
        }
        
        // Temperature control
        if (temp >= TEMP_REG_OFF)
            heat_on = false;
        if ((temp <= TEMP_REG_ON) || (pump_on == true))
            heat_on = true;
    
        // Thermocouple error proceed: turn heater off
        if (error == true)
            heat_on = false;

        
        // Heater control
        if (heat_on == true) {
            
            EnableHeater();
            IndicateHeaterOn();
        }
        else {
            
            DisableHeater();
            IndicateHeaterOff();
        }
    
        // Temp indication
        if ((temp >= TEMP_READY) && (error != true))
            IndicateTempOk();
        else
            IndicateTempNotOk();
        
    }
    
}








