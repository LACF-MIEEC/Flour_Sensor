/**
 * 
  @Company
    

  @File Name
    custom.c

  @Summary
    
 
  @Description
    
 */

/**
  Section: Macro Definitions
 */
#define LEDSTRIPE_I2C_TIMEOUT 500
#define LEDSTRIPE_I2C_RETRY_TIMEOUT 500


#include "i2c_pin_expander.h"
#include "mcc_generated_files/mcc.h"
#include "libpic30.h"

bool LEDSTRIPE_Configure(LEDSTRIPE_STATUS *ledstripeStatus) {

    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;
    uint16_t slaveTimeOut, timeOut;

    uint8_t WriteBuffer[2] = {LEDSTRIPE_CONFIG_REGISTER,
        LEDSTRIPE_CONFIG_ALL_OUTPUT};


    MSSP1_I2C_MasterWrite(WriteBuffer,
            2,
            LEDSTRIPE_ADDRESS,
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
            if (slaveTimeOut == LEDSTRIPE_I2C_TIMEOUT){
                *ledstripeStatus = LEDSTRIPE_SLAVE_TIMEOUT;
                return false;
            }
            else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE)
            break;
        
        __delay_ms(1);
        
        // check for max retry
        if (timeOut == LEDSTRIPE_I2C_RETRY_TIMEOUT){
            
            if(status == MSSP1_I2C_MESSAGE_ADDRESS_NO_ACK)
                *ledstripeStatus = LEDSTRIPE_RETRY_TIMEOUT_ADDRESS;
            else if(status == MSSP1_I2C_DATA_NO_ACK)
                *ledstripeStatus = LEDSTRIPE_RETRY_TIMEOUT_DATA;
            return false;
        }
        else
            timeOut++;

    }
    if(status == MSSP1_I2C_MESSAGE_FAIL){
        *ledstripeStatus = LEDSTRIPE_FAIL;
        return false;
    }

    __delay_ms(2000); // Keep LED's on for 2 seconds

    WriteBuffer[0] = LEDSTRIPE_OUTPUT_REGISTER;
    WriteBuffer[1] = LEDSTRIPE_OUTPUT_OFF;


    MSSP1_I2C_MasterWrite(WriteBuffer,
            2,
            LEDSTRIPE_ADDRESS,
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
            if (slaveTimeOut == LEDSTRIPE_I2C_TIMEOUT){
                *ledstripeStatus = LEDSTRIPE_SLAVE_TIMEOUT;
                return false;
            }
            else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE)
            break;
        
        __delay_ms(1);
        
        // check for max retry
        if (timeOut == LEDSTRIPE_I2C_RETRY_TIMEOUT){
            
            if(status == MSSP1_I2C_MESSAGE_ADDRESS_NO_ACK)
                *ledstripeStatus = LEDSTRIPE_RETRY_TIMEOUT_ADDRESS;
            else if(status == MSSP1_I2C_DATA_NO_ACK)
                *ledstripeStatus = LEDSTRIPE_RETRY_TIMEOUT_DATA;
            return false;
        }
        else
            timeOut++;

    }
    if(status == MSSP1_I2C_MESSAGE_FAIL){
        *ledstripeStatus = LEDSTRIPE_FAIL;
        return false;
    }
    return true;

}

bool LEDSTRIPE_SetLEDColor(uint8_t led, uint8_t color) {
    
    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;
    
    uint16_t slaveTimeOut, timeOut;
    
    uint8_t WriteBuffer[2];
    
    uint8_t LEDSTRIPE_output;
    
    if( ! LEDSTRIPE_GetOutput( &LEDSTRIPE_output ) )
        return false;
    
    LEDSTRIPE_output = LEDSTRIPE_output && (!led); // clear led output
    
    uint8_t mask = 0x07, n = 0;   
    
    // get led offset
    while( mask != led ){
        mask = mask << 3;
        n++;
    }
    //apply offset to color
    color = color << (3*n);
    
    LEDSTRIPE_output = LEDSTRIPE_output || color;
    
    WriteBuffer[0] = LEDSTRIPE_OUTPUT_REGISTER;
    WriteBuffer[1] = LEDSTRIPE_output;

    MSSP1_I2C_MasterWrite(WriteBuffer,
            2,
            LEDSTRIPE_ADDRESS,
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
            if (slaveTimeOut == LEDSTRIPE_I2C_TIMEOUT)
                return false;
            else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE)
            break;

        // check for max retry
        if (timeOut == LEDSTRIPE_I2C_RETRY_TIMEOUT)
            return false;
        else
            timeOut++;

    }
    return true;
}

bool LEDSTRIPE_GetOutput(uint8_t *outputReg) {

    MSSP1_I2C_MESSAGE_STATUS status;
    MSSP1_I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];

    uint16_t timeOut, slaveTimeOut;
    uint8_t regAddress = LEDSTRIPE_OUTPUT_REGISTER;

    // Build TRB for sending address
    MSSP1_I2C_MasterWriteTRBBuild(&readTRB[0],
            &regAddress,
            1,
            LEDSTRIPE_ADDRESS);
    // Build TRB for receiving data
    MSSP1_I2C_MasterReadTRBBuild(&readTRB[1],
            outputReg,
            1,
            LEDSTRIPE_ADDRESS);

    timeOut = 0;
    slaveTimeOut = 0;

    while (status != MSSP1_I2C_MESSAGE_FAIL) {
        // now send the transactions
        MSSP1_I2C_MasterTRBInsert(2, readTRB, &status);

        // wait for the message to be sent or status has changed.
        while (status == MSSP1_I2C_MESSAGE_PENDING) {
            // add some delay here
            __delay_ms(1);
            // timeout checking
            // check for max retry
            if (slaveTimeOut == LEDSTRIPE_I2C_TIMEOUT)
                return false;
            else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE)
            break;

        // check for max retry
        if (timeOut == LEDSTRIPE_I2C_RETRY_TIMEOUT)
            return false;
        else
            timeOut++;

    }
    return true;
}