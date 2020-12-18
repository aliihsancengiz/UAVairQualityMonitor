#ifndef _RELAY_EVENTS_
#define _RELAY_EVENTS_

#include<stdint.h>


// Event definition For  Posting event From Interrupt Service Routine
struct _Event
{
    uint16_t SO2_RawValue;
    uint16_t NO2_RawValue;
    uint16_t CO_RawValue;
    uint16_t CO2_RawValue;
};
typedef struct _Event event_t;


#endif