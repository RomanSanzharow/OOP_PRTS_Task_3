#include <iostream>
#include "interface.h"
#include "operation.h"

Interface::Interface() {
    operation = std::unique_ptr<Operation>();
}

void Interface::startOperation() {
    std::cout << "Beginning of operation. " << std::endl;
    while (true) {
        std::cout << "Enter task to execute.\n"
                     "1 - Add mission DIVE;\n2 - Add mission LIFT;\n3 - Add mission MOVE;\n"
                     "4 - Add mission RETURN;\n"
                     "5 - Show current operation;\n6 - Swap missions;\n"
                     "7 - Delete task;\n8 - Add new task.\n"
                     "9 - Recover deleted mission" << std::endl;
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
    std::cout << "End of operation.";
}

bool Interface::NewAction(int eventType) {
    bool stop = false;
    if (eventType == SHOW_MISSIONS) {
        operation->ShowOperation();
        return stop;
    } else if (eventType == SWAP_MISSIONS) {
        operation->ShowOperation();
        std::cout << "Select missions to be swapped." << std::endl;
        int index1, index2;
        std::cin >> index1 >> index2;
        operation->SwapMissions(index1, index2);
        return stop;
    } else if (eventType == DELETE_MISSION) {
        operation->ShowOperation();
        std::cout << "Select mission to be deleted." << std::endl;
        int index;
        std::cin >> index;
        operation->DeleteMission(index);
        return stop;
    } else if (eventType == INSERT_MISSION) {
        operation->ShowOperation();
        std::cout << "Select index to insert." << std::endl;
        int index;
        int operationLen = operation->getOperationLen();
        std::cin >> index;
        std::cout << "Select type of mission.\n1 - Add mission DIVE;\n"
                     "2 - Add mission LIFT;\n3 - Add mission MOVE;\n"
                     "4 - Add mission RETURN;\n";
        while (true) {
            std::cin >> eventType;
            if (eventType == 4 && index != operationLen) {
                std::cout << "It's not possible to add RETURN not in the end of mission. Try again" << std::endl;
            }
            if (eventType >= 0 && eventType < 5) {
                operation->InsertMission(index, std::move(NewMission(eventType, stop)));
                return stop;
            } else {
                std::cout << "Incorrect mission type, try again." << std::endl;
            }
        }
    } else if (eventType == PUSH_DELETED_MISSION) {
        int operationLen = operation->getDeletedOperationLen();
        if (operationLen == 0) {
            std::cout << "No deleted data." << std::endl;
            return stop;
        }
        operation->ShowDeletedOperation();
        std::cout << "Select task to be inserted." << std::endl;
        int index;
        std::cin >> index;
        operation->PushDeletedMission(index);
        return stop;
    }
    operation->SetMission(std::move(NewMission(eventType, stop)));
    operation->Do();
    operation->UpdateFileWithOperationData();
    return stop;
}

std::unique_ptr<IMission> Interface::NewMission(int missionType, bool &stop) {
    std::unique_ptr<IMission> mission;
    if (missionType == DIVE_MISSION || missionType == LIFT_MISSION) {
        int deepSetting; // 0 - датчик глубины (глубина) ; 1 - эхолот (отстояние)
        int deepValue;
        int deepType; // 0 - спираль; 1 - вертикальные движители

        std::cout << "Select sensor of depth (0 - depth sensor; 1 - echo sounder): " << std::endl;
        while (true) {
            std::cin >> deepSetting;
            if (deepSetting != 0 && deepSetting != 1) {
                std::cout << "Wrong! Try again." << std::endl;
                std::cin >> deepSetting;
            } else {
                break;
            }
        }

        std::cout << "Enter distance from bottom: " << std::endl;
        std::cin >> deepValue;

        std::cout << "Enter type of diving (0 - spiral; 1 - vertical motors): " << std::endl;
        while (true) {
            std::cin >> deepType;
            if (deepType != 0 && deepType != 1) {
                std::cout << "Wrong! Try again." << std::endl;
                std::cin >> deepType;
            } else {
                break;
            }
        }
        if (missionType == DIVE_MISSION) {
            mission = std::unique_ptr<Dive>(deepSetting, deepValue, deepType);
        } else {
            mission = std::unique_ptr<Lift>(deepSetting, deepValue, deepType);
        }
    } else if (missionType == MOVE_MISSION) {
        int newX;
        int newY;
        int moveType; // 0 - выход в точку; 1 - движение вдоль прямой
        int deepType; // 0 - на постоянной глубине; 1 - на постоянном отстоянии от дна
        std::cout << "Enter type of moving (0 - point; 1 - line): " << std::endl;
        while (true) {
            std::cin >> moveType;
            if (moveType != 0 && moveType != 1) {
                std::cout << "Wrong! Try again." << std::endl;
                std::cin >> moveType;
            } else {
                break;
            }
        }

        std::cout << "Enter type of depth (0 - constant depth; 1 - constant distance): " << std::endl;
        while (true) {
            std::cin >> deepType;
            if (deepType != 0 && deepType != 1) {
                std::cout << "Wrong! Try again." << std::endl;
                std::cin >> deepType;
            } else {
                break;
            }
        }

        std::cout << "Enter X: " << std::endl;
        std::cin >> newX;

        std::cout << "Enter Y: " << std::endl;
        std::cin >> newY;
        mission = std::unique_ptr<Move>(newX, newY, moveType, deepType);
    } else if (missionType == RETURN_MISSION) {
        mission = std::unique_ptr<Return>();
        stop = true;
    }
    return std::move(mission);
}
