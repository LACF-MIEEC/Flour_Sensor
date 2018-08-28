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
#include "i2c_pin_extender.h"
#include "rgb.h"
/*
                         Main application
 */

#define MODE_LED I2C_PIN_EXTENDER_DisplayLed1
#define READING_STATUS_LED I2C_PIN_EXTENDER_DisplayLed2

bool AUTO_SAMPLING = false;
bool AUTO_SAMPLING_STAND_BY = false;

int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    //
    //    if (!(UART1_TRANSFER_STATUS_TX_FULL & UART1_TransferStatusGet())) {
    //        UART1_Write(0xBB);
    //    }

    if (!POTENTIOMETER_Configure()) {
        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
        return -1;
    }
    //    if (!(UART1_TRANSFER_STATUS_TX_FULL & UART1_TransferStatusGet())) {
    //        UART1_Write(0xBB);
    //    }

    if (!I2C_PIN_EXTENDER_Configure()) {
        I2C_ErrorHandler(I2C_PIN_EXTENDER_I2CstatusGet());
        return -1;
    }

    AUTO_SAMPLING_STAND_BY = false;

    // Set to Auto Mode
    ADC1_Enable();
    PUMP_EN_SetHigh();
    __delay_ms(500);
    AUTO_SAMPLING = true;

    if (!MODE_LED(RGB_GREEN)) {
        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
        return -1;
    }
    if (!READING_STATUS_LED(RGB_RED)) {
        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
        return -1;
    }


    TMR1_Start();

    bool buttonA, buttonB;
    bool B_pressed, A_pressed;
    uint8_t A_counter = 0, B_counter = 0;

    while (1) {

        if (TMR1_SoftwareCounterGet() >= 5) { // 50 miliseconds granularity

            //Check input status
            if (!I2C_PIN_EXTENDER_GetButtons(&buttonA, &buttonB)) {
                I2C_ErrorHandler(I2C_PIN_EXTENDER_I2CstatusGet());
                return -1;
            }

            //==================================================================
            if (buttonA) {
                // Pressed
                A_pressed = true;
                A_counter++;

                if (A_counter >= 60) { // more than 3 seconds
                    //Kept pressed for more than n time units
                    if (!MODE_LED(RGB_WHITE)) {
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }
                    if (!READING_STATUS_LED(RGB_WHITE)) {
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }
                    PUMP_EN_SetHigh();
                    __delay_ms(500);

                    AUTO_SAMPLING_STAND_BY = true; // this is important, for the timer callback conflicts with the Configuration
                    if (!POTENTIOMETER_Configure()) { // Reset Reference Value
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }
                    __delay_ms(1000);
                    // after calibration stand by mode is disabled and auto mode is set

                    AUTO_SAMPLING_STAND_BY = false;

                    // Set to Auto Mode
                    ADC1_Enable();
                    __delay_ms(500);
                    AUTO_SAMPLING = true;

                    if (!MODE_LED(RGB_GREEN)) {
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }
                    if (!READING_STATUS_LED(RGB_RED)) {
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }

                    A_pressed = false;
                    A_counter = 0;
                }

            } else if (A_pressed) {
                // Released 

                //Single Press


                A_pressed = false;
                A_counter = 0;
            }
            //==================================================================
            if (buttonB) {
                //Pressed
                B_pressed = true;
                B_counter++;

                if (B_counter >= 60) { // more than 3 seconds
                    //Kept pressed for more than n time units
                    if (!AUTO_SAMPLING) { // Reverse Measuring Mode
                        // Set to Auto Mode
                        AUTO_SAMPLING_STAND_BY = false;
                        ADC1_Enable();
                        PUMP_EN_SetHigh();
                        __delay_ms(500);
                        AUTO_SAMPLING = true;

                        if (!MODE_LED(RGB_GREEN)) {
                            I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                            return -1;
                        }
                        if (!READING_STATUS_LED(RGB_RED)) {
                            I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                            return -1;
                        }

                    } else {
                        // Set to single sample mode
                        AUTO_SAMPLING = false;
                        PUMP_EN_SetLow();
                        ADC1_Disable();

                        if (!MODE_LED(RGB_YELLOW)) {
                            I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                            return -1;
                        }
                        if (!READING_STATUS_LED(RGB_BLUE)) {
                            I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                            return -1;
                        }
                    }
                    B_pressed = false;
                    B_counter = 0;
                }
            } else if (B_pressed) {
                // Released

                //Single Press
                if (AUTO_SAMPLING) { // Stand by/wakes up auto-aquisition (if enabled)
                    if (!AUTO_SAMPLING_STAND_BY) {
                        AUTO_SAMPLING_STAND_BY = true;
                        PUMP_EN_SetLow();
                        ADC1_Disable();

                        if (!READING_STATUS_LED(RGB_BLUE)) {
                            I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                            return -1;
                        }

                    } else {
                        ADC1_Enable();
                        PUMP_EN_SetHigh();
                        __delay_ms(500);
                        AUTO_SAMPLING_STAND_BY = false;

                        if (!READING_STATUS_LED(RGB_RED)) {
                            I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                            return -1;
                        }
                    }
                } else { // Single Acquisition (if enabled)

                    if (!READING_STATUS_LED(RGB_RED)) {
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }

                    Acquire();

                    if (!I2C_PIN_EXTENDER_BarGraphDisplay(ADC1_SampleGet()))
                        I2C_ErrorHandler(I2C_PIN_EXTENDER_I2CstatusGet());

                    __delay_ms(200);
                    if (!READING_STATUS_LED(RGB_BLUE)) {
                        I2C_ErrorHandler(POTENTIOMENTER_I2CstatusGet());
                        return -1;
                    }
                }
                B_pressed = false;
                B_counter = 0;
            }
            //==================================================================
            TMR1_SoftwareCounterClear();
        }

    }


    return -1;
}

/**
 End of File
 */