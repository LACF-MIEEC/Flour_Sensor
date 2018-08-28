/**
 * 
  @Company
    

  @File Name
    custom.c

  @Summary
    
 
  @Description
    
 */


#include "i2c_pin_extender.h"
#include "mcc_generated_files/mcc.h"
#include "libpic30.h"


/**
  Section: Macro Definitions
 */
#define I2C_PIN_EXTENDER_CONNECTION_TIMEOUT 100
#define I2C_PIN_EXTENDER_CONNECTION_MAX_RETRY 50

#define I2C_PIN_EXTENDER_REGISTER_IOCON 0x0A
#define I2C_PIN_EXTENDER_REGISTER_GPIOA 0x12
#define I2C_PIN_EXTENDER_REGISTER_GPIOB 0x13
#define I2C_PIN_EXTENDER_REGISTER_OLATA 0x14
#define I2C_PIN_EXTENDER_REGISTER_OLATB 0x15

#define BARGRAPH_SIZE 8

/**
  Section: Local Variables
 */
static I2C_SLAVE i2c_pin_extender;

static bool I2C_PinExtender_Enabled = true;

I2C_STATUS I2C_PIN_EXTENDER_STATUS;

static const int16_t BarGraphPercentValues[BARGRAPH_SIZE] = {10, 30, 50, 70, 80, 85, 90, 95};

/**
  Section: Functions
 */
bool I2C_PIN_EXTENDER_Configure() {

    i2c_pin_extender.address = I2C_PIN_EXTENDER_ADDRESS;
    i2c_pin_extender.timeout = I2C_PIN_EXTENDER_CONNECTION_TIMEOUT;
    i2c_pin_extender.max_retry = I2C_PIN_EXTENDER_CONNECTION_MAX_RETRY;

    uint8_t WriteBuffer[23] = {
        0x00, // First Register Address
        //-------------------------------
        0x00, // IODIRA - Port A all output (BarGrah Display) 
        0xC0, // IODIRB - Port B 2 in( buttons) 6 out(rgb leds)
        0x00, // IPOLA - Port A direct polarity
        0xC0, // IPOLB - Port B input buttons inverted polarity
        0x00, // GPINTENA - Port A Interupts are disabled
        0x00, // GPINTENB - Port B Interupts are disabled
        0x00, // DEFVALA - N/A
        0x00, // DEFVALB - N/A
        0x00, // INTCONA - N/A
        0x00, // INTCONB - N/A
        0x00, // IOCON - Leave empty for now
        0x00, // IOCON - Shared address
        0x00, // GPPUA - No pull-up
        0xC0, // GPPUB - Input buttons pulled up
        0x00, // INTFA - N/A
        0x00, // INTFB - N/A
        0x00, // INTCAPA - N/A
        0x00, // INTCAPB - N/A
        0x00, // GPIOA - Overwrited by write in OLATA
        0x00, // GPIOB - Overwrited by write in OLATB
        0xFF, // OLATA - Bargraph All On
        0x3F, // OLATB - Turn ON Leds
    };
    // Perform a sequential writing in all registers to configure
    if (I2C_Send(WriteBuffer, 23, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) && (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {
        // Now set byte mode
        WriteBuffer[0] = I2C_PIN_EXTENDER_REGISTER_IOCON;
        WriteBuffer[1] = 0x20; // SEQOP = 1 

        if (I2C_Send(WriteBuffer, 2, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) && (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {

            // Turn off the Leds
            WriteBuffer[0] = I2C_PIN_EXTENDER_REGISTER_GPIOB;
            WriteBuffer[1] = 0x00; // Turn off the Leds
            __delay_ms(1000); // wait a sec.

            if (I2C_Send(WriteBuffer, 2, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) && (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {

                // Turn off the Bargraph
                WriteBuffer[0] = I2C_PIN_EXTENDER_REGISTER_GPIOA;
                WriteBuffer[1] = 0x00; // Turn off the Bargraph

                if (I2C_Send(WriteBuffer, 2, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) && (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {
                    return true;
                }

            }
        }
    }
    return false;
}

void I2C_PIN_EXTENDER_Enable(void) {
    I2C_PinExtender_Enabled = true;
}

void I2C_PIN_EXTENDER_Disable(void) {
    I2C_PIN_EXTENDER_SetOutputPortA(0x00);
    I2C_PIN_EXTENDER_SetOutputPortB(0x00);
    I2C_PinExtender_Enabled = false;
}

bool I2C_PIN_EXTENDER_IsEnabled(void) {
    return I2C_PinExtender_Enabled;
}

I2C_STATUS* I2C_PIN_EXTENDER_I2CstatusGet(void) {
    return &I2C_PIN_EXTENDER_STATUS;
}

bool I2C_PIN_EXTENDER_BarGraphDisplay(uint16_t value) {

    uint8_t NLeds = 0;
    uint8_t mask = 0x01;
    uint8_t i;

    int16_t MaxValue = AMPLIFIER_MAX_OUTPUT - AMPLIFIER_OUTPUT_REFERENCE_VALUE;
    int16_t DiffValue = (int16_t) value - AMPLIFIER_OUTPUT_REFERENCE_VALUE;
    float PercentValue = ((float)DiffValue / MaxValue) * 100;;
    //Convert from ADC value to number of LED's
    for (i = 0; i < BARGRAPH_SIZE; i++) {

        if (PercentValue >= BarGraphPercentValues[i]) {
            NLeds |= mask; // set led
            mask <<= 1; // shift mask for next led
        } else
            break;
    }
    if (I2C_PIN_EXTENDER_SetOutputPortA(NLeds))
        return true;
    return false;
}

bool I2C_PIN_EXTENDER_DisplayLed1(uint8_t color) {
    uint8_t Mask = 0x07;
    uint8_t PinExtender_LATB;

    //Read Pin Extenter LATB
    if (!I2C_PIN_EXTENDER_GetOutputPortB(&PinExtender_LATB))
        return false;

    // make sure rgb extra bits are clear
    color &= 0x07;
    //LED A No Shift Needed

    //Clear Current Output
    PinExtender_LATB &= ~Mask;

    // Set New Output
    PinExtender_LATB |= color;

    //Write to Pin Extender LATB
    if (!I2C_PIN_EXTENDER_SetOutputPortB(PinExtender_LATB))
        return false;
    return true;

}

bool I2C_PIN_EXTENDER_DisplayLed2(uint8_t color) {
    uint8_t Mask = 0x38;
    uint8_t PinExtender_LATB;

    //read pin extenter LATB
    if (!I2C_PIN_EXTENDER_GetOutputPortB(&PinExtender_LATB))
        return false;

    // make sure rgb extra bits are clear
    color &= 0x07;
    //Shift color to output bits
    color <<= 3;

    //Clear Current Output
    PinExtender_LATB &= ~Mask;

    // Set New Output
    PinExtender_LATB |= color;

    //Write to Pin Extender LATB
    if (!I2C_PIN_EXTENDER_SetOutputPortB(PinExtender_LATB))
        return false;
    return true;
}

bool I2C_PIN_EXTENDER_GetButtons(bool *button1, bool *button2) {

    uint8_t PinExtender_LATB;
    uint8_t Button1_Mask = 0x80, Button2_Mask = 0x40;

    *button1 = false;
    *button2 = false;

    //Read Pin Extenter LATB
    if (!I2C_PIN_EXTENDER_GetOutputPortB(&PinExtender_LATB))
        return false;

    if ((PinExtender_LATB & Button1_Mask) == Button1_Mask)
        *button1 = true;
    if ((PinExtender_LATB & Button2_Mask) == Button2_Mask)
        *button2 = true;

    return true;
}

bool I2C_PIN_EXTENDER_SetOutputPortA(uint8_t output) {

    uint8_t WriteBuffer[2];

    WriteBuffer[0] = I2C_PIN_EXTENDER_REGISTER_GPIOA;
    WriteBuffer[1] = output;

    if (I2C_Send(WriteBuffer, 2, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) || (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {
        return true;
    }
    return false;
}

bool I2C_PIN_EXTENDER_SetOutputPortB(uint8_t output) {

    uint8_t WriteBuffer[2];

    WriteBuffer[0] = I2C_PIN_EXTENDER_REGISTER_GPIOB;
    WriteBuffer[1] = output;

    if (I2C_Send(WriteBuffer, 2, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) || (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {
        return true;
    }
    return false;
}

bool I2C_PIN_EXTENDER_GetOutputPortA(uint8_t *output) {

    if (I2C_Read(output, 1, I2C_PIN_EXTENDER_REGISTER_GPIOA, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) || (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {
        return true;
    }
    return false;
}

bool I2C_PIN_EXTENDER_GetOutputPortB(uint8_t *output) {
    if (I2C_Read(output, 1, I2C_PIN_EXTENDER_REGISTER_GPIOB, &i2c_pin_extender, &I2C_PIN_EXTENDER_STATUS) || (I2C_PIN_EXTENDER_STATUS == I2C_COMPLETE)) {
        return true;
    }
    return false;
}