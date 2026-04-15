#include "Notification.h"
#include <iostream>

Notification::Notification() : Event() {}

Notification::Notification(string msg) : Event(msg) {}

Notification::~Notification() {}

void Notification::print() {
    cout << "Уведомление: " << message << endl;
}
