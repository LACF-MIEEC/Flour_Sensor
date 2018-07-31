/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

/**
 Section: Included Files
*/

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h> 
#include <stdint.h>
#include <stdlib.h>

//#include "LEDboard.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Macro Definition
*/
                
#define COMMAND_LENGTH 2
/**
  Section: Data Types
*/

/** USB Commands

  @Summary

  @Description

*/
typedef enum
{
    INPUT_CHANGE = 0xA,
    
    MODE_CHANGE = 0xB

} USB_COMMAND_TYPE;



static uint8_t USB_Command[COMMAND_LENGTH];
static uint8_t BLUETOOTH_Command[COMMAND_LENGTH];

/**
  Section: Interface Routines
*/

/**
  @Summary
    

  @Description
    

  @Preconditions
    
 
  @Param
    

  @Returns
    

  @Comment
    
 
  @Example
    <code>
        
    </code>

  @Remarks
    
 */
//bool USB_GetCommand(void);

/**
  @Summary
    

  @Description
    

  @Preconditions
    
 
  @Param
    

  @Returns
    

  @Comment
    
 
  @Example
    <code>
        
    </code>

  @Remarks
    
 */
//bool BLUETOOTH_GetCommand(void);

/**
  @Summary
    

  @Description
    

  @Preconditions
    
 
  @Param
    

  @Returns
    

  @Comment
    
 
  @Example
    <code>
        
    </code>

  @Remarks
    
 */
void ADC_Aquire(void);

/**
  @Summary
    

  @Description
    

  @Preconditions
    
 
  @Param
    

  @Returns
    

  @Comment
    
 
  @Example
    <code>
        
    </code>

  @Remarks
    
 */
void POTENTIOMETER_Calibrate(void);

/**
  @Summary
    

  @Description
    

  @Preconditions
    
 
  @Param
    

  @Returns
    

  @Comment
    
 
  @Example
    <code>
        
    </code>

  @Remarks
    
 */
bool SYSTEM_Configuration(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

