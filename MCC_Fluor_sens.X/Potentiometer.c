/**
 * 
  @Company
    

  @File Name
    Potentiometer.c

  @Summary
    
 
  @Description
    
*/
#include "mcc_generated_files/mcc.h"
#include "Potentiometer.h"

/**
  Section: Local Variables
 */
static I2C_SLAVE i2c_potentiometer;
I2C_STATUS I2C_POTENTIOMETER_STATUS;

#define POTENTIOMETER_CONNECTION_TIMEOUT 100
#define POTENTIOMETER_CONNECTION_MAX_RETRY 50

/**
  Section: Potentiometer Interface
*/

bool POTENTIOMETER_Configure(){
    
    i2c_potentiometer.address = POTENTIOMETER_ADDRESS;
    i2c_potentiometer.timeout = POTENTIOMETER_CONNECTION_TIMEOUT;
    i2c_potentiometer.max_retry = POTENTIOMETER_CONNECTION_MAX_RETRY;
    

    uint8_t WriteBuffer[2] = {0x00,
        0x00};
    uint8_t bitMask = 0x80;
    uint16_t offset;
    
    if(!POTENTIOMENTER_StepOffsetGet(&offset, &I2C_POTENTIOMETER_STATUS))
        return false;

    offset /= 2;
    
    ADC1_Enable(); // Enable ADC
    uint8_t i;
    
    for (i = 0; i < 8; i++) {

        WriteBuffer[1] |= bitMask; // set bit to 1

        if (!I2C_Send(WriteBuffer, 2, &i2c_potentiometer, &I2C_POTENTIOMETER_STATUS))
            return false;

        else if (I2C_POTENTIOMETER_STATUS == I2C_COMPLETE) {

            LED_EN_SetHigh(); // Turn on LED
            ADC1_Start(); // Start acquisition

            while (!ADC1_IsSampleReady()); //wait for acquisition

            LED_EN_SetLow(); // Turn off LED

            if (ADC1_SampleGet() > AMPLIFIER_OUTPUT_REFERENCE_VALUE) {
                if (ADC1_SampleGet() - AMPLIFIER_OUTPUT_REFERENCE_VALUE <= offset)
                    break;
                
                WriteBuffer[1] &= ~bitMask; //set bit to 0
                
                if (i == 7) { // Update before exit loop
                    if (!I2C_Send(WriteBuffer, 2, &i2c_potentiometer, &I2C_POTENTIOMETER_STATUS))
                        return false;
                    else if (I2C_POTENTIOMETER_STATUS != I2C_COMPLETE)
                        return false;
                }
                
            } else if (ADC1_SampleGet() < AMPLIFIER_OUTPUT_REFERENCE_VALUE) {
                if (AMPLIFIER_OUTPUT_REFERENCE_VALUE - ADC1_SampleGet() <= offset)
                    break;
                
            } else
                break;

            bitMask >>= 1; // Moves to next bit
        } else
            return false;
    }

    ADC1_Disable(); // Disable ADC
    return true;

}

bool POTENTIOMENTER_StepOffsetGet(uint16_t *step, I2C_STATUS *status){
    
        uint8_t WriteBuffer[2] = {0x00,
        0x80};
        
        uint16_t temp;
        
        if (!I2C_Send(WriteBuffer, 2, &i2c_potentiometer, status))
            return false;

        else if (*status == I2C_COMPLETE) {
            ADC1_Enable(); // Enable ADC
            LED_EN_SetHigh(); // Turn on LED
            ADC1_Start(); // Start acquisition

            while (!ADC1_IsSampleReady()); //wait for acquisition

            LED_EN_SetLow(); // Turn off LED
            
            temp = ADC1_SampleGet();
            ADC1_Disable(); // Enable ADC
        }
        else
            return false;
        
        WriteBuffer[1] += 0x01;
        
        if (!I2C_Send(WriteBuffer, 2, &i2c_potentiometer, status))
            return false;

        else if (*status == I2C_COMPLETE) {
            ADC1_Enable(); // Enable ADC
            LED_EN_SetHigh(); // Turn on LED
            ADC1_Start(); // Start acquisition

            while (!ADC1_IsSampleReady()); //wait for acquisition

            LED_EN_SetLow(); // Turn off LED
            
            *step = ADC1_SampleGet() - temp;
            ADC1_Disable(); // Enable ADC
        }
        else
            return false;      
        
        return true;
}

I2C_STATUS* POTENTIOMENTER_I2CstatusGet(void){
    return &I2C_POTENTIOMETER_STATUS;
}