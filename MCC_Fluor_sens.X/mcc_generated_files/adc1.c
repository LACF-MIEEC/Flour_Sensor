
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.55
        Device            :  PIC24FV16KM202
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.34
        MPLAB 	          :  MPLAB X v4.15
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc1.h"

/**
  Section: Data Type Definitions
*/

/* ADC Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

 */
typedef struct
{
	uint8_t intSample;
    uint16_t avgSample;
    bool sampleReady;
}

ADC_OBJECT;

static ADC_OBJECT adc1_obj;

/**
  Section: Driver Interface
*/


void ADC1_Initialize (void)
{
    // ASAM enabled; ADSIDL disabled; DONE disabled; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Internal counter ends sampling and starts conversion; MODE12 12-bit; ADON disabled; 

   AD1CON1 = 0x0474;

    // CSCNA disabled; NVCFG0 AVSS; PVCFG 4 * Internal VBG; ALTS disabled; BUFM disabled; SMPI Generates interrupt after completion of every 10th sample/conversion operation; OFFCAL disabled; BUFREGEN disabled; 

   AD1CON2 = 0xC024;

    // SAMC 4; EXTSAM disabled; ADRC FOSC/2; ADCS 9; 

   AD1CON3 = 0x0409;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

   AD1CHS = 0x0000;

    // CSS26 disabled; CSS23 disabled; CSS22 disabled; CSS21 disabled; CSS20 disabled; CSS30 disabled; CSS19 disabled; CSS18 disabled; CSS29 disabled; CSS17 disabled; CSS28 disabled; CSS16 disabled; CSS27 disabled; 

   AD1CSSH = 0x0000;

    // CSS9 disabled; CSS5 disabled; CSS4 disabled; CSS3 disabled; CSS2 disabled; CSS15 disabled; CSS1 disabled; CSS14 disabled; CSS0 disabled; CSS13 disabled; CSS12 disabled; CSS11 disabled; CSS10 disabled; 

   AD1CSSL = 0x0000;

    // ASEN disabled; WM Legacy operation; ASINT No interrupt; CM Less Than mode; BGREQ disabled; CTMREQ disabled; LPEN disabled; 

   AD1CON5 = 0x0000;

    // CHH20 disabled; CHH22 disabled; CHH21 disabled; CHH23 disabled; CHH17 disabled; CHH16 disabled; CHH19 disabled; CHH18 disabled; 

   AD1CHITH = 0x0000;

    // CHH9 disabled; CHH5 disabled; CHH4 disabled; CHH3 disabled; CHH2 disabled; CHH1 disabled; CHH0 disabled; CHH11 disabled; CHH10 disabled; CHH13 disabled; CHH12 disabled; CHH15 disabled; CHH14 disabled; 

   AD1CHITL = 0x0000;

    // CTMEN23 disabled; CTMEN21 disabled; CTMEN22 disabled; CTMEN20 disabled; CTMEN18 disabled; CTMEN19 disabled; CTMEN16 disabled; CTMEN17 disabled; 

   AD1CTMENH = 0x0000;

    // CTMEN5 disabled; CTMEN9 disabled; CTMEN12 disabled; CTMEN13 disabled; CTMEN10 disabled; CTMEN0 disabled; CTMEN11 disabled; CTMEN1 disabled; CTMEN2 disabled; CTMEN3 disabled; CTMEN4 disabled; CTMEN14 disabled; CTMEN15 disabled; 

   AD1CTMENL = 0x0000;


   adc1_obj.intSample = AD1CON2bits.SMPI;
   
   // Enabling ADC1 interrupt.
   //IEC0bits.AD1IE = 1;
}

void ADC1_Enable(void)
{
    _ADON = 1;
}
void ADC1_Disable(void)
{
    _ADON = 0;
}
void ADC1_Start(void)
{
    adc1_obj.sampleReady = false; // Clear ready flag
   _AD1IF = 0; // Clear interrupt flag
   _AD1IE = 1; // Enable interruptions
}
void ADC1_Stop(void)
{
   _AD1IE = 0; // Disable interruptions
}

uint16_t ADC1_ConversionResultBufferGet(uint16_t *buffer)
{
    int count;
    uint16_t *ADC16Ptr;

    ADC16Ptr = (uint16_t *)&(ADC1BUF0);

    for(count=0;count<=adc1_obj.intSample;count++)
    {
        buffer[count] = (uint16_t)*ADC16Ptr;
        ADC16Ptr++;
    }
    return count;
}

uint16_t ADC1_SampleGet(void)
{
    return adc1_obj.avgSample;
}

bool ADC1_IsSampleReady( void )
{
    return adc1_obj.sampleReady;   
}

void ADC1_ChannelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADC1Interrupt ( void )
{
    if(!adc1_obj.sampleReady){
        uint16_t ADC_Buffer[adc1_obj.intSample];

        ADC1_ConversionResultBufferGet(ADC_Buffer);

        int count;
        uint16_t sum = 0;

        for(count=0; count <= adc1_obj.intSample; count++)
        {
            sum += ADC_Buffer[count];
        }
        adc1_obj.avgSample = sum / ((uint16_t)adc1_obj.intSample + 1);

        adc1_obj.sampleReady = true;
    }
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}


/**
  End of File
*/
