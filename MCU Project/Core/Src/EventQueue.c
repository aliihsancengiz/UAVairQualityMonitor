#include "EventQueue.h"


// Initialize Queue and allocate memory for event queue
EventQueue_t *Queue_Init(uint32_t m_capacity)
{
    if (m_capacity > 0)
    {
        EventQueue_t *m_ptr=malloc(sizeof(EventQueue_t));
        m_ptr->capacity=m_capacity;
        m_ptr->size=m_ptr->front=0;
        m_ptr->rear=m_capacity-1;
        m_ptr->events=malloc(sizeof(event_t)*m_capacity);
        return m_ptr;
    }
    return NULL;
}


// Deinitialize the EventQueue
void Queue_Deinit(EventQueue_t *self)
{
    free(self->events);
    self->events=NULL;
    free(self);
    self=NULL;
}

// Return true if Queue is full
bool isFull(EventQueue_t *self)
{
    return (self->size==self->capacity);
}

// Return true if Queue is empty
bool isEmpty(EventQueue_t *self)
{
    return (self->size==0);
}

// Enqueue event into event queue
void enQueue(EventQueue_t *self,event_t ev)
{
    if(isFull(self))
    {
        return;
    }
    else
    {
        self->rear =(self->rear +1) % self->capacity;
        self->events[self->rear]=ev;
        self->size+=1;
    }
}

// Dequeue event from event queue
event_t deQueue(EventQueue_t *self)
{
    if(isEmpty(self))
    {
        event_t temp={0,0,0,0};
        return temp;
    }
    event_t p_event=self->events[self->front];
    self->front=(self->front+1) % self->capacity;
    self->size-=1;
    return p_event;
}
