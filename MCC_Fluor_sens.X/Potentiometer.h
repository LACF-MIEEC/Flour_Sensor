/* 
 * File:   Potentiometer.h
 * Author: Luis Ferreira
 *
 * Created on July 26, 2018, 4:13 PM
 */

#ifndef POTENTIOMETER_H
#define	POTENTIOMETER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define POTENTIOMETER_ADDRESS 0x002C
    
#define POTENTIOMETER_MIDSCALE_RESET 0x40
#define POTENTIOMETER_SHUTDOWN 0x20
    
typedef enum{
    POTENTIOMETER_SLAVE_TIMEOUT = 0xB1,
    POTENTIOMETER_RETRY_TIMEOUT_ADDRESS = 0xB2,
    POTENTIOMETER_RETRY_TIMEOUT_DATA = 0xB3,
    POTENTIOMETER_FAIL = 0xB4,
    POTENTIOMETER_OK = 0xB0
}POTENTIOMETER_STATUS;
    
bool POTENTIOMETER_Configure(POTENTIOMETER_STATUS *potentiometerStatus);

#ifdef	__cplusplus
}
#endif

#endif	/* POTENTIOMETER_H */

