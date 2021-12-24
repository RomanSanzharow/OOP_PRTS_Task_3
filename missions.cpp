#include "missions.h"

Dive::Dive(int deepSetting, int deepValue, int deepType)
        : deepSetting(deepSetting), newZ(deepValue), deepType(deepType) {}

const std::string &Dive::GetMissionData() {
    missionData.clear();
    missionData += "DIVE\n";
    if (deepSetting == 0) {
        missionData += "Using depth sensor;\n";
        missionData = missionData + "Глубина погружения: " + std::to_string(newZ) + ";\n";
    } else {
        missionData += "Using echo sounder;\n";
        missionData = missionData + "Отстояние: " + std::to_string(newZ) + ";\n";
    }
    if (deepType == 0) {
        missionData += "Diving: spiral;\n\n";
    } else {
        missionData += "Diving: vertical motors\n\n";
    }
    return missionData;
}

bool Dive::Run() {
    if (newZ <= maxDeep && newZ >= 0) {
        return true;
    }
    return false;
}


Lift::Lift(int deepSetting, int deepValue, int deepType)
        : deepSetting(deepSetting), newZ(deepValue), deepType(deepType) {}

const std::string &Lift::GetMissionData() {
    missionData.clear();
    missionData += "LIFT\n";
    if (deepSetting == 0) {
        missionData += "Using depth sensor;\n";
        missionData = missionData + "Depth: " + std::to_string(newZ) + ";\n";
    } else {
        missionData += "Using echo sounder;\n";
        missionData = missionData + "Distance: " + std::to_string(newZ) + ";\n";
    }
    if (deepType == 0) {
        missionData += "Diving: spiral;\n\n";
    } else {
        missionData += "Diving: vertical motors\n\n";
    }
    return missionData;
}

bool Lift::Run() {
    if (newZ <= maxDeep && newZ >= 0) {
        return true;
    }
    return false;
}

Move::Move(int newX, int newY, int moveType, int deepType)
        : newX(newX), newY(newY), moveType(moveType), deepType(deepType) {}

bool Move::Run() {
    if (newX + moveAccuracy < 10000 && newX + moveAccuracy > 0) {
        return true;
    }
    return false;
}

const std::string &Move::GetMissionData() {
    missionData.clear();
    missionData += "MOVE\n";
    if (moveType == 0) {
        missionData += "To point;\n";
    } else {
        missionData += "Line;\n";
    }
    if (deepType == 0) {
        missionData += "Constant depth;\n";
    } else {
        missionData += "Constant distance\n";
    }
    missionData = missionData + "X: " + std::to_string(newX) + " with precision +-" + std::to_string(moveAccuracy) + ";\n";
    missionData = missionData + "Y: " + std::to_string(newY) + " with precision +-" + std::to_string(moveAccuracy) + ";\n\n";
    return missionData;
}

bool Return::Run() {
    return true;
}

const std::string &Return::GetMissionData() {
    return missionData;
}
