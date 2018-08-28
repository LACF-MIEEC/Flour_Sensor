
#include "i2c.h"
#include "mcc_generated_files/mcc.h"
#include "libpic30.h"

bool I2C_Send(uint8_t *wdata, uint8_t length, I2C_SLAVE *slave, I2C_STATUS *send_status) {

    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;

    uint16_t slaveTimeOut, retryTimeOut;


    MSSP1_I2C_MasterWrite(wdata,
            length,
            slave->address,
            &status);

    retryTimeOut = 0;
    slaveTimeOut = 0;

    while (status != MSSP1_I2C_MESSAGE_FAIL) {

        // wait for the message to be sent or status has changed.
        while (status == MSSP1_I2C_MESSAGE_PENDING) {
            // add some delay here
            __delay_ms(1);
            // timeout checking
            // check for max retry
            if (slaveTimeOut == slave->timeout) {
                *send_status = I2C_TIMEOUT;
                return true;
            } else
                slaveTimeOut++;
        }

        if (status == MSSP1_I2C_MESSAGE_COMPLETE) {
            *send_status = I2C_COMPLETE;
            return true;
        }

        // check for max retry
        if (retryTimeOut == slave->max_retry) {

            if ((status == MSSP1_I2C_MESSAGE_ADDRESS_NO_ACK) || (status == MSSP1_I2C_DATA_NO_ACK)) {
                *send_status = I2C_NO_ACK;
                return true;
            }
        } else
            retryTimeOut++;

    }
    if (status == MSSP1_I2C_MESSAGE_FAIL) {
        *send_status = I2C_FAIL;
        return true;
    }

    *send_status = I2C_FAIL;
    return false;
}

bool I2C_Read(uint8_t *pData, uint8_t nCount, uint8_t regAddress, I2C_SLAVE *slave, I2C_STATUS *read_status) {

    MSSP1_I2C_MESSAGE_STATUS status;
    MSSP1_I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];

    uint16_t slaveTimeOut, retryTimeOut;

    // this initial value is important
    status = MSSP1_I2C_MESSAGE_PENDING;


    // Build TRB for sending address
    MSSP1_I2C_MasterWriteTRBBuild(&readTRB[0],
            &regAddress,
            1,
            slave->address);
    // Build TRB for receiving data
    MSSP1_I2C_MasterReadTRBBuild(&readTRB[1],
            pData,
            nCount,
            slave->address);

    retryTimeOut = 0;
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
            if (slaveTimeOut == slave->timeout) {
                *read_status = I2C_TIMEOUT;
                return true;
            } else
                slaveTimeOut++;
        }


        if (status == MSSP1_I2C_MESSAGE_COMPLETE) {
            *read_status = I2C_COMPLETE;
            return true;
        }
        // check for max retry
        if (retryTimeOut == slave->max_retry) {

            if ((status == MSSP1_I2C_MESSAGE_ADDRESS_NO_ACK) || (status == MSSP1_I2C_DATA_NO_ACK)) {
                *read_status = I2C_NO_ACK;
                return true;
            }
        } else
            retryTimeOut++;

    }
    if (status == MSSP1_I2C_MESSAGE_FAIL) {
        *read_status = I2C_FAIL;
        return true;
    }

    *read_status = I2C_FAIL;
    return false;
}

void I2C_ErrorHandler(I2C_STATUS *status) {
    /* This should turn on a LED or other error signal
     * but the adicional outputs we have work with I2C, 
     * so their not realiable since this an I2C error handler.
     * A solution is to create a new output from the unused pins.
     */
    UART1_Write(0xFA);

}