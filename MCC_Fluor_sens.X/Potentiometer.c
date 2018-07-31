/**
 * 
  @Company
    

  @File Name
    Potentiometer.c

  @Summary
    
 
  @Description
    
*/
#include "custom.h"
#include "mcc_generated_files/mcc.h"
#include "Potentiometer.h"
#include "libpic30.h"

/**
  Section: Macro Definitions
 */
#define POTENTIOMETER_I2C_TIMEOUT 1000
#define POTENTIOMETER_I2C_RETRY_TIMEOUT 100

bool POTENTIOMETER_Configure(POTENTIOMETER_STATUS *potentiometerStatus){
    
    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;
    
    uint16_t slaveTimeOut, timeOut;

    uint8_t WriteBuffer[2] = {0x00,
        0x00};


    MSSP1_I2C_MasterWrite(WriteBuffer,
            2,
            POTENTIOMETER_ADDRESS,
            &status);

    timeOut = 0;
    slaveTimeOut = 0;

    while (status != MSSP1_I2C_MESSAGE_FAIL) {
        // now send the transactions

        // wait for the message to be sent or status has changed.
        while (status == MSSP1_I2C_MESSAGE_PENDING) {
            // add some delay here
            __delay_ms(1);
            // timeout checking
            // check for max retry
            if (slaveTimeOut == POTENTIOMETER_I2C_TIMEOUT){
                *potentiometerStatus = POTENTIOMETER_SLAVE_TIMEOUT;
                return false;
            }
            else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE)
            break;//this needs to change
        
        __delay_ms(1);
        
        // check for max retry
        if (timeOut == POTENTIOMETER_I2C_RETRY_TIMEOUT){
            
            if(status == MSSP1_I2C_MESSAGE_ADDRESS_NO_ACK)
                *potentiometerStatus = POTENTIOMETER_RETRY_TIMEOUT_ADDRESS;
            else if(status == MSSP1_I2C_DATA_NO_ACK)
                *potentiometerStatus = POTENTIOMETER_RETRY_TIMEOUT_DATA;
            return false;
        }
        else
            timeOut++;

    }
    if(status == MSSP1_I2C_MESSAGE_FAIL){
        *potentiometerStatus = POTENTIOMETER_FAIL;
        return false;
    }
    
    return true;
    
}
