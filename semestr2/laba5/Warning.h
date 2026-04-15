#ifndef WARNING_H
#define WARNING_H

#include "Event.h"

class Warning : public Event {
public:
    Warning();
    Warning(string msg);
    ~Warning();

    void print();
};
#endif
