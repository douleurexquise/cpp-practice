#include "Warning.h"
#include <iostream>

Warning::Warning() : Event() {}

Warning::Warning(string msg) : Event(msg) {}

Warning::~Warning() {}

void Warning::print() {
    cout << "Предупреждение: " << message << endl;
}
