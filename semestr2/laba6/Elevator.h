#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>
using namespace std;
class Elevator {
private:
    int floors;
    int currentFloor;
    int lockedFloor;
    bool hasLockedFloor;
    string accessCode;
public:
    Elevator();
    int loadConfig(const string& filename);
    void saveConfig(const string& filename);
    void setConfig(int floors,bool hasLocked, int lockedFloor, const string& code);
    void moveToFloor(int targetFloor);
    bool checkAccess(int floor, const string& code);
};
#endif
