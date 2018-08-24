
#include "i2c.h"

bool I2C_Send(uint8_t *wdata, uint8_t length, I2C_SLAVE *slave, I2C_STATUS *send_status){
    
    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;
    
    uint16_t slaveTimeOut, retryTimeOut;


    MSSP1_I2C_MasterWrite(wdata,
            length,
            slave->address,
            &status);

    retryTimeOut = 0;
    slaveTimeOut = 0;

    while (status != MSSP1_I2C_MESSAGE_FAIL) {
        // now send the transactions

        // wait for the message to be sent or status has changed.
        while (status == MSSP1_I2C_MESSAGE_PENDING) {
            // add some delay here
            __delay_ms(1);
            // timeout checking
            // check for max retry
            if (slaveTimeOut == slave->timeout){
                *send_status = I2C_TIMEOUT;
                return true;
            }
            else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE)
            *send_status = I2C_COMPLETE;
            return true;
        
        __delay_ms(1);
        
        // check for max retry
        if (retryTimeOut == slave->max_retry){
            
            if((status == MSSP1_I2C_MESSAGE_ADDRESS_NO_ACK)||(status == MSSP1_I2C_DATA_NO_ACK)){
                *send_status = I2C_NO_ACK;
                return true;
            }
        }
        else
            retryTimeOut++;

    }
    if(status == MSSP1_I2C_MESSAGE_FAIL){
        *send_status = I2C_FAIL;
        return true;
    }
    
    *send_status = I2C_FAIL;
    return false;
}   

bool I2C_Read(uint8_t *rbuffer, uint8_t length, I2C_SLAVE *slave, I2C_STATUS *read_status){

}

void I2C_ErrorHandler(I2C_STATUS *status){
    /* This should turn on a LED or other error signal
     * but the adicional outputs we have work with I2C, 
     * so their not realiable since this an I2C error handler.
     * A solution is to create a new output from the unused pins.
     */
}