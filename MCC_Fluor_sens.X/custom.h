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


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

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


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

