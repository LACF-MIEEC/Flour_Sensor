/* 
 * File:   LEDboard.h
 * Author: Luis Ferreira
 *
 * Created on July 23, 2018, 6:38 PM
 */

#ifndef I2C_PIN_EXTENDER_H
#define	I2C_PIN_EXTENDER_H


/**
 Section: Included Files
 */
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "i2c.h"
/**
 Section: Macro Definition
 */
#define I2C_PIN_EXTENDER_ADDRESS 0x0020 //shifted right because of R/W bit


#ifdef	__cplusplus
extern "C" {
#endif


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
    bool I2C_PIN_EXTENDER_Configure();

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
    void I2C_PIN_EXTENDER_Enable(void);

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
    void I2C_PIN_EXTENDER_Disable(void);

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
    bool I2C_PIN_EXTENDER_IsEnabled(void);

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
    I2C_STATUS* I2C_PIN_EXTENDER_I2CstatusGet(void);

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
    bool I2C_PIN_EXTENDER_BarGraphDisplay(uint16_t value);

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
    bool I2C_PIN_EXTENDER_SetOutputPortA(uint8_t hexaValue);

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
    bool I2C_PIN_EXTENDER_SetOutputPortB(uint8_t hexaValue);

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
    bool I2C_PIN_EXTENDER_DisplayLed1(uint8_t color);

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
    bool I2C_PIN_EXTENDER_DisplayLed2(uint8_t color);
    
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
    bool I2C_PIN_EXTENDER_GetButtons(bool *button1, bool *button2);
    
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
    bool I2C_PIN_EXTENDER_GetOutputPortA(uint8_t *hexaValue);

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
    bool I2C_PIN_EXTENDER_GetOutputPortB(uint8_t *hexaValue);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_PIN_EXTENDER_H */

