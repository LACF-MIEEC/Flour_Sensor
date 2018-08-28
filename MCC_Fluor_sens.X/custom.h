/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef CUSTOM_H
#define	CUSTOM_H

/**
 Section: Included Files
*/

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h> 
#include <stdint.h>
#include <stdlib.h>


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

        
extern bool AUTO_SAMPLING;
extern bool AUTO_SAMPLING_STAND_BY;
        
/**
  Section: Functions Declarations
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
void SampleChamber(void);

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
void Acquire(void);

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
void PlayWithLeds(void);

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
void PlayWithButtons(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CUSTOM_H */

