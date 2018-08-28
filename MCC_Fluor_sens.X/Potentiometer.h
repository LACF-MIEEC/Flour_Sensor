/* 
 * File:   Potentiometer.h
 * Author: Luis Ferreira
 *
 * Created on July 26, 2018, 4:13 PM
 */

#ifndef POTENTIOMETER_H
#define	POTENTIOMETER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "i2c.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
/**
 Section: Macro Definition
*/

#define POTENTIOMETER_ADDRESS 0x002C
    
#define POTENTIOMETER_MIDSCALE_RESET 0x40
#define POTENTIOMETER_SHUTDOWN 0x20


/**
 Section: Functions
*/

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
bool POTENTIOMETER_Configure();

/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>
        Gets the offset of a potenciometer step relative to the ADC1 scale
    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
bool POTENTIOMENTER_StepOffsetGet(uint16_t *step, I2C_STATUS *status);

/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>
        Gets the offset of a potenciometer step relative to the ADC1 scale
    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
I2C_STATUS* POTENTIOMENTER_I2CstatusGet(void);

#ifdef	__cplusplus
}
#endif

#endif	/* POTENTIOMETER_H */

