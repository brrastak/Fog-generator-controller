// STM32F103
#include "stm32f10x.h"

#ifndef __FOG_H__
#define __FOG_H__


// Get temperature (average)
// Returns TRUE in case of thermocouple error
bool GetTemp(int16_t *);
// Actuators
void EnableHeater(void);
void DisableHeater(void);
void EnablePump(void);
void DisablePump(void);
// Indicators
void IndicateTempOk(void);
void IndicateTempNotOk(void);
void IndicateHeaterOn(void);
void IndicateHeaterOff(void);



#endif
