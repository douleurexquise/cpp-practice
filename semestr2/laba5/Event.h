#ifndef EVENT_H
#define EVENT_H
#include <string>
using namespace std;
class Event{
protected:
    string message;
public:
    Event();
    Event(string message);
    virtual ~Event();
    void setMessage(string message);
    string getMessage();
    virtual void print();
};
#endif
