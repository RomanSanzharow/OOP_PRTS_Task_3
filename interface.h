#ifndef TASK_3_INTERFACE_H
#define TASK_3_INTERFACE_H

#include <memory>

#define DIVE_MISSION 1
#define LIFT_MISSION 2
#define MOVE_MISSION 3
#define RETURN_MISSION 4
#define SHOW_MISSIONS 5
#define SWAP_MISSIONS 6
#define DELETE_MISSION 7
#define INSERT_MISSION 8
#define PUSH_DELETED_MISSION 9

class Operation;
class IMission;

class Interface {
private:
    std::unique_ptr<Operation> operation;
    bool NewAction(int missionType);
    static std::unique_ptr<IMission> NewMission(int missionType, bool& stop);
public:
    Interface();
    void startOperation();
};
#endif
