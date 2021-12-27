#include <iostream>
#include "interface.h"
#include "operation.h"

interface::interface() {
    operation = std::make_unique<Operation>();
}

void interface::startOperation() {
    std::cout << "START. " << std::endl;
    while (true) {
        std::cout << "Enter task:.\n"
                     "1 - Add Dive;\n2 - Add Lift;\n3 - Add Move;\n"
                     "4 - Add Return;\n"
                     "5 - Show current;\n6 - Swap missions;\n"
                     "7 - Delete;\n8 - Add new task\n"
                     "9 - Recover deleted" << std::endl;
        int MissionType;
        std::cin >> MissionType;
        if (MissionType >= 0 && MissionType < 10) {
            if (NewAction(MissionType)) {
                break;
            }
        } else {
            std::cout << "Incorrect action" << std::endl;
        }
    }
    std::cout << "END.";
}

bool interface::NewAction(int eventType) {
    bool stop = false;
    if (eventType == SHOW_MISSIONS) {
        operation->ShowOperation();
        return stop;
    } else if (eventType == SWAP_MISSIONS) {
        operation->ShowOperation();
        std::cout << "Select two to swap (index)." << std::endl;
        size_t idx1, idx2;
        std::cin >> idx1 >> idx2;
        operation->SwapMissions(idx1, idx2);
        return stop;
    } else if (eventType == DELETE_MISSION) {
        operation->ShowOperation();
        std::cout << "Select to delete (index)." << std::endl;
        size_t idx;
        std::cin >> idx;
        operation->DeleteMission(idx);
        return stop;
    } else if (eventType == INSERT_MISSION) {
        operation->ShowOperation();
        std::cout << "Select new place (index)." << std::endl;
        size_t idx;
        size_t operationLen = operation->getOperationLen();
        std::cin >> idx;
        std::cout << "Select mission.\n1 - Add Dive;\n"
                     "2 - Add Lift;\n - Add Move;\n"
                     "4 - Add Return;\n";
        while (true) {
            std::cin >> eventType;
            if (eventType == 4 && idx != operationLen) {
                std::cout << "Incorrect, try again" << std::endl;
            }
            if (eventType >= 0 && eventType < 5) {
                operation->InsertMission(idx, std::move(NewMission(eventType, stop)));
                return stop;
            } else {
                std::cout << "Incorrect, try again." << std::endl;
            }
        }
    } else if (eventType == PUSH_DELETED_MISSION) {
        size_t operationLen = operation->getDeletedOperationLen();
        if (operationLen == 0) {
            std::cout << "No deleted missions." << std::endl;
            return stop;
        }
        operation->ShowDeletedOperation();
        std::cout << "Select task." << std::endl;
        size_t idx;
        std::cin >> idx;
        operation->PushDeletedMission(idx);
        return stop;
    }
    operation->SetMission(std::move(NewMission(eventType, stop)));
    operation->Do();
    operation->UpdateFileWithOperationData();
    return stop;
}

std::unique_ptr<IMission> interface::NewMission(int missionType, bool &stop) {
    std::unique_ptr<IMission> mission;
    if (missionType == DIVE_MISSION || missionType == LIFT_MISSION) {
        int deepSetting; // 0 - датчик глубины (глубина) ; 1 - эхолот (отстояние)
        int deepValue;
        int deepType; // 0 - спираль; 1 - вертикальные движители

        std::cout << "0 - Depth sensor; 1 - Echo sounder: " << std::endl;
        while (true) {
            std::cin >> deepSetting;
            if (deepSetting != 0 && deepSetting != 1) {
                std::cout << "Incorrect, try again." << std::endl;
                std::cin >> deepSetting;
            } else {
                break;
            }
        }

        std::cout << "Enter depth: " << std::endl;
        std::cin >> deepValue;

        std::cout << "0 - Spiral; 1 - Vertical motors: " << std::endl;
        while (true) {
            std::cin >> deepType;
            if (deepType != 0 && deepType != 1) {
                std::cout << "Incorrect, try again." << std::endl;
                std::cin >> deepType;
            } else {
                break;
            }
        }
        if (missionType == DIVE_MISSION) {
            mission = std::make_unique<Dive>(deepSetting, deepValue, deepType);
        } else {
            mission = std::make_unique<Lift>(deepSetting, deepValue, deepType);
        }
    } else if (missionType == MOVE_MISSION) {
        int newX;
        int newY;
        int moveType; // 0 - выход в точку; 1 - движение вдоль прямой
        int deepType; // 0 - на постоянной глубине; 1 - на постоянном отстоянии от дна
        std::cout << "0 - Go to point ; 1 - Go on line: " << std::endl;
        while (true) {
            std::cin >> moveType;
            if (moveType != 0 && moveType != 1) {
                std::cout << "Incorrect, try again." << std::endl;
                std::cin >> moveType;
            } else {
                break;
            }
        }

        std::cout << "0 - Const depth; 1 - Const distance: " << std::endl;
        while (true) {
            std::cin >> deepType;
            if (deepType != 0 && deepType != 1) {
                std::cout << "Incorrect, try again." << std::endl;
                std::cin >> deepType;
            } else {
                break;
            }
        }

        std::cout << "X: " << std::endl;
        std::cin >> newX;

        std::cout << "Y: " << std::endl;
        std::cin >> newY;
        mission = std::make_unique<Move>(newX, newY, moveType, deepType);
    } else if (missionType == RETURN_MISSION) {
        mission = std::make_unique<Return>();
        stop = true;
    }
    return std::move(mission);
}
