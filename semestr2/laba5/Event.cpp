#include "Event.h"
#include <iostream>
Event::Event() {
    message = "";
}
Event::Event(string msg) {
    message = msg;
}
Event::~Event() {
}
void Event::setMessage(string msg) {
    message = msg;
}
string Event::getMessage() {
    return message;
}
void Event::print() {
    cout << "Событие: " << message << endl;
}
