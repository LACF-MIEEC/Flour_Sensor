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
#include "LEDboard.h"
#include "Potentiometer.h"

/**
  Section: Custom Routines
*/


bool SYSTEM_Configuration(void){
    
    _TON=0; // disable timer
    U2MODEbits.UARTEN = 0;  // disable Bluetooth
    _ADON=0; // disable ADC
    

    
    return true;
    
}

void ADC_Acquire(void){
    
    int acq;
    
    ADC1_Enable(); // Enable ADC
    LED_EN_SetHigh(); // Turn on LED
    ADC1_Start();   // Start acquisition
    
    while( ! ADC1_IsSampleReady() ); //wait
    acq = ADC1_SampleGet();
    
    ADC1_Stop();
    ADC1_Disable();
    
}


/**
  End of File
*/