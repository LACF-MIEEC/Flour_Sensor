
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_H
#define	I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef	__cplusplus
    extern "C" {
#endif /* __cplusplus */
        
/**
  I2C Components Definition

  @Summary
    Defines the configuration of an I2C component

  @Description
    ....

 */
typedef struct
{
    uint16_t address; // Component I2C bus address 
    uint16_t timeout; // Conection Timeout
    uint16_t max_retry; // Busy device max Retry 
    
} I2C_SLAVE;


/**
  I2C Send Status Enumeration

  @Summary
    Defines the different states of the i2c master.

  @Description
    This defines the different states that the i2c master
    used to process transactions on the i2c bus.
*/
typedef enum
{
    I2C_TIMEOUT,
    I2C_RETRY_TIMEOUT,
    I2C_NO_ACK,
    I2C_FAIL,
    I2C_COMPLETE,
} I2C_STATUS;


/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
bool I2C_Send(uint8_t *wdata, uint8_t length, I2C_SLAVE *slave, I2C_STATUS *send_status);

/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
bool I2C_Read(uint8_t *pData, uint8_t nCount, uint8_t regAddress, I2C_SLAVE *slave, I2C_STATUS *read_status);

/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
void I2C_ErrorHandler(I2C_STATUS *status);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* I2C_H */

