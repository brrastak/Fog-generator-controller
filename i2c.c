// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

// user
#include "i2c.h"

// Local variables
// Data
uint8_t* transmit_buf;
//static uint8_t* receive_buf;
// Data transmit address
uint8_t addr;
// Number of data
int to_transmit = 0;
//int to_receive = 0;
// Flags
volatile bool transmitted = true;
volatile bool received = true;


// I2C interrupt
void I2C1_EV_IRQHandler(void)
{   
    // Start condition generated
    if ((I2C1->SR1 & I2C_SR1_SB) != 0) {
        
        (void)I2C1->SR1;                // clear flags
        I2C1->DR = addr;                // send I2C address
    }
    // Address sent
    if ((I2C1->SR1 & I2C_SR1_ADDR) != 0) {
        
        (void)I2C1->SR1;                // clear flags
        (void)I2C1->SR2;
        I2C1->DR = transmit_buf[0];     // send first data byte
        transmit_buf++;
        to_transmit--;
    }
    // Transmitter register empty
    if ((I2C1->SR1 & I2C_SR1_TXE) != 0) {
        
        if (to_transmit == 0) {         // no more data to send

            I2C1->CR2 &= ~I2C_CR2_ITBUFEN;      // buffer interrupt disable
        }
        else {
            
            I2C1->DR = transmit_buf[0];         // send data byte
            transmit_buf++;
            to_transmit--;
        }
    }
    // Transmission completed
    if (((I2C1->SR1 & I2C_SR1_BTF) != 0) && (to_transmit == 0)) {
        
        I2C1->CR2 &= ~I2C_CR2_ITEVTEN;      // event interrupt disable
        I2C1->CR1 |= I2C_CR1_STOP;          // generate stop condition
        transmitted = true;
    }

}
void InitI2c(void)
{
    // Transmitter in master mode
    I2C1->CR2 = 36;                     // RCC 36MHz
    I2C1->CCR |= 180;                   // 100kHz
    I2C1->TRISE = 0x55;                 // 1000ns
    I2C1->CR1 |= I2C_CR1_PE;            // peripheral enable
}
void TransmitI2c(uint8_t i2c_addr, uint8_t* buf, int num)
{
    to_transmit = num;
    addr = i2c_addr;
    transmit_buf = buf;
    transmitted = false;
    
    I2C1->CR2 |=    I2C_CR2_ITEVTEN |   // event interrupt enable
                    I2C_CR2_ITBUFEN;    // buffer interrupt enable
    
    // Generate start condition
    I2C1->CR1 |= I2C_CR1_START;
}
bool TransmittedI2c(void)
{
    // After transmitting the last data byte should wait for stop condition
    return (transmitted && ((I2C1->CR1 & I2C_CR1_STOP) == 0));
}
bool ReceivedI2c(void)
{
    return received;
}
void WaitForTransmitI2c(void)
{
    while (! TransmittedI2c())
        ;
}
void WaitForReceiveI2c(void)
{
    while (! received)
        ;
}
