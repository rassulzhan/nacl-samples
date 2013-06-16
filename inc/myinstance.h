
#ifndef PPAPI_MY_INSTANCE_H_
#define PPAPI_MY_INSTANCE_H_

#include "shared_queue.h"
#include "custom_events.h"

class MyInstance : public PPAPIInstance {
private:
    LockingQueue<Event*> event_queue_;

public:
    MyInstance(PP_Instance instance, const char *args[]);
    virtual ~MyInstance() {};

// Called by the browser to handle incoming input events.
    virtual bool HandleInputEvent(const pp::InputEvent& event);

    Event* AcquireEvent(bool* was_queue_cancelled);
};

Event* Event_Acquire(bool* was_queue_cancelled);

#endif
