#ifndef __TRANSMIT_INTERFACE__
#define __TRANSMIT_INTERFACE__

#include <stdint.h>

struct _TransmitInterface
{
    void (*transmit_data)(uint8_t* dataPtr,uint32_t len);
};

typedef struct _TransmitInterface TransmitInterface_t;


#endif


