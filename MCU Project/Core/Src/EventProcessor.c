#include "EventProcessor.h"


void processEvents(EventQueue_t *dispatchQueue)
{
    // İf there is any event waiting in queue dispatch it
    if (dispatchQueue->size>0)
    {
        event_t processedEvent=deQueue(dispatchQueue);
        dispatchQueue->event_cb(processedEvent);
    }
}
uint32_t getNofEvents(EventQueue_t *dispatchQueue)
{
    // Returns size of Event in event queue
    return dispatchQueue->size;
}