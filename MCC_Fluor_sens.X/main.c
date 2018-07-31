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

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "custom.h"
#include "libpic30.h"
#include "LEDboard.h"
#include "Potentiometer.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    SYSTEM_Configuration();
    
        
    LEDSTRIPE_STATUS ledstripeStatus;
    
    if( !LEDSTRIPE_Configure(&ledstripeStatus) ){
        UART1_Write(ledstripeStatus);
    }
    UART1_Write(ledstripeStatus);
    
//    POTENTIOMETER_STATUS potentiometerStatus;
//    
//    __delay_ms(1000);
//    
//    if( !POTENTIOMETER_Configure(&potentiometerStatus) )
//        UART1_Write(MSSP1_I2C_ErrorCountGet());
// 
//    UART1_Write(ledstripeStatus);
    
    while (1)
    {
        
        UART1_Write(ledstripeStatus);
        __delay_ms(1000);
        
//        LEDSTRIPE_RIGTH_RED;
//        __delay_ms(1000);
        /*
        LEDSTRIPE_RIGTH_RED;
        __delay_ms(1000);
        LEDSTRIPE_RIGTH_GREEN;
        __delay_ms(1000);
        LEDSTRIPE_RIGTH_BLUE;
        __delay_ms(1000);
        LEDSTRIPE_CENTER_RED;
        __delay_ms(1000);
        LEDSTRIPE_CENTER_GREEN;
        __delay_ms(1000);
        LEDSTRIPE_CENTER_BLUE;
        __delay_ms(1000);
        LEDSTRIPE_LEFT_GREEN;
        __delay_ms(1000);
        LEDSTRIPE_LEFT_BLUE;
        __delay_ms(1000);
        */
        //LEDSTRIPE_ON;
        //while(1);       
        
    }

    
    return -1;
}
 
/**
 End of File
*/