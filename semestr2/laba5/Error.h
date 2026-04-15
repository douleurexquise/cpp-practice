#ifndef ERROR_H
#define ERROR_H

#include "Event.h"

class Error : public Event {
public:
    Error();
    Error(string msg);
    ~Error();

    void print();
};
#endif
