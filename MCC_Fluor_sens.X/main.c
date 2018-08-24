/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.55
        Device            :  PIC24FV16KM202
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.34
        MPLAB             :  MPLAB X v4.15
*/

#include "mcc_generated_files/mcc.h"
#include "custom.h"
#include "libpic30.h"
#include "Potentiometer.h"
#include "i2c.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    if(!POTENTIOMETER_Configure(&I2C_POTENTIOMETER_STATUS)){
        I2C_ErrorHandler(&I2C_POTENTIOMETER_STATUS);
    }
    //Configure pin_expantion
    
    while (1)
    {
        // pool i2c Pin Expander inputs
        
        // pool UART commands
        
    }

    
    return -1;
}
 
/**
 End of File
*/