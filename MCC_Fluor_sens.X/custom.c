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
#include "i2c_pin_extender.h"
#include "rgb.h"
#include "libpic30.h"
/**
  Section: Custom Routines
 */

void SampleChamber(void) {

    LED_EN_SetHigh(); // Turn on LED

    ADC1_Start(); // Start acquisition
    while (!ADC1_IsSampleReady()); //wait for samplling completion

    LED_EN_SetLow(); // Turn off LED
}

void Acquire(void) {

    ADC1_Enable();
    PUMP_EN_SetHigh();
    __delay_ms(500);
    SampleChamber();
    PUMP_EN_SetLow();
    ADC1_Disable();
}

void TMR1_CallBack(void) {

    if ((AUTO_SAMPLING)&(!AUTO_SAMPLING_STAND_BY)) {
        SampleChamber();

        if (I2C_PIN_EXTENDER_IsEnabled()) {
            if (!I2C_PIN_EXTENDER_BarGraphDisplay(ADC1_SampleGet()))
                I2C_ErrorHandler(I2C_PIN_EXTENDER_I2CstatusGet());
        }
        // else{ send elsewhere, UART for example)}
    }
}

void PlayWithLeds(void) {
    int i;
    uint8_t NLeds = 0;
    uint8_t mask = 0x01;

    for (i = 0; i <= 8; i++) {
        if (!I2C_PIN_EXTENDER_SetOutputPortA(NLeds))
            i--;
        else {
            NLeds |= mask; // set led
            mask <<= 1; // shift mask for next led
            __delay_ms(250);
        }
    }

    I2C_PIN_EXTENDER_DisplayLed1(RGB_RED);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed1(RGB_GREEN);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed1(RGB_BLUE);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed1(RGB_WHITE);

    I2C_PIN_EXTENDER_DisplayLed2(RGB_RED);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed2(RGB_GREEN);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed2(RGB_BLUE);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed2(RGB_WHITE);
    __delay_ms(250);
    I2C_PIN_EXTENDER_DisplayLed2(RGB_BLACK);
    I2C_PIN_EXTENDER_DisplayLed1(RGB_BLACK);
}

void PlayWithButtons(void) {

    bool buttonA, buttonB;

    static uint8_t A_counter = 0, B_counter = 0;
    static uint8_t NLeds = 0;
    static uint8_t mask = 0x01;

    I2C_PIN_EXTENDER_GetButtons(&buttonA, &buttonB);

    // this part is useful for a 2 functions button (single and long press)
    if (buttonA) {
        A_counter++;
        if (A_counter >= 100)
            I2C_PIN_EXTENDER_DisplayLed1(RGB_GREEN);
        else
            I2C_PIN_EXTENDER_DisplayLed1(RGB_RED);
    } else {
        A_counter = 0;
        I2C_PIN_EXTENDER_DisplayLed1(RGB_BLACK);
    }

    // this part is useful for a keep pressed button (ex: keep pressed for increase/decrease ligth)
    if (buttonB) {
        B_counter++;
        if (B_counter == 10) {
            NLeds |= mask; // set led
            mask <<= 1; // shift mask for next led
            I2C_PIN_EXTENDER_SetOutputPortA(NLeds);
            B_counter = 0;
        }
        I2C_PIN_EXTENDER_DisplayLed2(RGB_RED);
    } else {
        NLeds = 0;
        mask = 0x01;
        I2C_PIN_EXTENDER_SetOutputPortA(NLeds);
        I2C_PIN_EXTENDER_DisplayLed2(RGB_BLACK);
        B_counter = 0;
    }
}


/**
  End of File
 */