/**
 * 
  @Company
    

  @File Name
    custom.c

  @Summary
    
 
  @Description
    
*/
#include "custom.h"
#include "mcc_generated_files/mcc.h"
/**
  Section: Custom Routines
*/

void SampleChamber(void){
    
    LED_EN_SetHigh(); // Turn on LED
    
    ADC1_Start();   // Start acquisition
    while( ! ADC1_IsSampleReady() ); //wait for samplling completion
    
    LED_EN_SetLow(); // Turn off LED
}

void Acquire(void){
    
    SampleChamber();
    
    if(I2C_PinExpander_Enabled){
        if( !BarGraphDisplay(ADC1_SampleGet(), &I2C_PIN_EXPANDER_STATUS) )
            I2C_ErrorHandler(&I2C_PIN_EXPANDER_STATUS);
    }
    // else{ send elsewhere, UART for example)}
    
}

/**
  End of File
*/