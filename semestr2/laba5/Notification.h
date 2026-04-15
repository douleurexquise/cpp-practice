#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "Event.h"
class Notification : public Event {
public:
    Notification();
    Notification(string msg);
    ~Notification();

    void print();
};
#endif
