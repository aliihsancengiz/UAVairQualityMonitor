#ifndef _EVENT_PROCESSOR_
#define _EVENT_PROCESSOR_

#include "EventQueue.h"


// Event Processing Utilities

void processEvents(EventQueue_t *dispatchQueue);
uint32_t getNofEvents(EventQueue_t *dispatchQueue);

#endif