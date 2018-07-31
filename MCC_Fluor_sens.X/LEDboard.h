/* 
 * File:   LEDboard.h
 * Author: Luis Ferreira
 *
 * Created on July 23, 2018, 6:38 PM
 */

#ifndef LEDBOARD_H
#define	LEDBOARD_H


/**
 Section: Included Files
*/

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h> 
#include <stdint.h>
#include <stdlib.h>

/**
 Section: Macro Definition
*/

#define OFF 0x00

#define BLUE 0x01
#define RED 0x02
#define GREEN 0x04

#define CYAN 0x05
#define PINK 0x03
#define YELLOW 0x06

#define WHITE 0x07

#define RIGTH 0x07
#define CENTER 0x38
#define LEFT 0xC0

#define LEDSTRIPE_RIGTH_RED LEDSTRIPE_SetLEDColor(RIGTH,RED)
#define LEDSTRIPE_RIGTH_GREEN LEDSTRIPE_SetLEDColor(RIGTH,GREEN)
#define LEDSTRIPE_RIGTH_BLUE LEDSTRIPE_SetLEDColor(RIGTH,BLUE)
#define LEDSTRIPE_RIGTH_YELLOW LEDSTRIPE_SetLEDColor(RIGTH,YELLOW)
#define LEDSTRIPE_RIGTH_PINK LEDSTRIPE_SetLEDColor(RIGTH,PINK)
#define LEDSTRIPE_RIGTH_WHITE LEDSTRIPE_SetLEDColor(RIGTH,WHITE)
#define LEDSTRIPE_RIGTH_CYAN LEDSTRIPE_SetLEDColor(RIGTH,CYAN)
#define LEDSTRIPE_RIGTH_OFF LEDSTRIPE_SetLEDColor(RIGTH,OFF)

#define LEDSTRIPE_CENTER_RED LEDSTRIPE_SetLEDColor(CENTER,RED)
#define LEDSTRIPE_CENTER_GREEN LEDSTRIPE_SetLEDColor(CENTER,GREEN)
#define LEDSTRIPE_CENTER_BLUE LEDSTRIPE_SetLEDColor(CENTER,BLUE)
#define LEDSTRIPE_CENTER_YELLOW LEDSTRIPE_SetLEDColor(CENTER,YELLOW)
#define LEDSTRIPE_CENTER_PINK LEDSTRIPE_SetLEDColor(CENTER,PINK)
#define LEDSTRIPE_CENTER_WHITE LEDSTRIPE_SetLEDColor(CENTER,WHITE)
#define LEDSTRIPE_CENTER_CYAN LEDSTRIPE_SetLEDColor(CENTER,CYAN)
#define LEDSTRIPE_CENTER_OFF LEDSTRIPE_SetLEDColor(CENTER,OFF)

#define LEDSTRIPE_LEFT_GREEN LEDSTRIPE_SetLEDColor(LEFT,RED)
#define LEDSTRIPE_LEFT_BLUE LEDSTRIPE_SetLEDColor(LEFT,BLUE)
#define LEDSTRIPE_LEFT_CYAN LEDSTRIPE_SetLEDColor(LEFT,PINK)
#define LEDSTRIPE_LEFT_OFF LEDSTRIPE_SetLEDColor(LEFT,OFF)

#define LEDSTRIPE_ON LEDSTRIPE_RIGTH_WHITE;LEDSTRIPE_CENTER_WHITE;LEDSTRIPE_LEFT_CYAN
#define LEDSTRIPE_OFF 

#define LEDSTRIPE_OUTPUT_OFF 0x00
#define LEDSTRIPE_OUTPUT_ON 0xFF

#define LEDSTRIPE_ADDRESS 0x0027 //shifted right because of R/W bit

#define LEDSTRIPE_CONFIG_REGISTER 0x03
#define LEDSTRIPE_CONFIG_ALL_OUTPUT 0x00
#define LEDSTRIPE_OUTPUT_REGISTER 0x01

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
    LEDSTRIPE_SLAVE_TIMEOUT = 0xA1,
    LEDSTRIPE_RETRY_TIMEOUT_ADDRESS = 0xA2,
    LEDSTRIPE_RETRY_TIMEOUT_DATA = 0xA3,
    LEDSTRIPE_FAIL = 0xA4,
    LEDSTRIPE_OK = 0x00
}LEDSTRIPE_STATUS;
    
/**
 Section: Functions
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
bool LEDSTRIPE_Configure(LEDSTRIPE_STATUS *ledstripeStatus);

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
bool LEDSTRIPE_SetLEDColor (uint8_t led, uint8_t color );

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
bool LEDSTRIPE_GetOutput(uint8_t *outputReg);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDBOARD_H */

