#include "Error.h"
#include <iostream>

Error::Error() : Event() {}

Error::Error(string msg) : Event(msg) {}

Error::~Error() {}

void Error::print() {
    cout << "Ошибка: " << message << endl;
}
