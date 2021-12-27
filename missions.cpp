#include "missions.h"

Dive::Dive(int deepSetting, int deepValue, int deepType)
        : deepSetting(deepSetting), newZ(deepValue), deepType(deepType) {}

const std::string &Dive::GetMissionData() {
    missionData.clear();
    missionData += "Dive\n";
    if (deepSetting == 0) {
        missionData += "Depth sensor;\n";
        missionData = missionData + "Depth: " + std::to_string(newZ) + ";\n";
    } else {
        missionData += "Echo sounder;\n";
        missionData = missionData + "Distance: " + std::to_string(newZ) + ";\n";
    }
    if (deepType == 0) {
        missionData += "Spiral;\n\n";
    } else {
        missionData += "Vertical motors\n\n";
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
    missionData += "Lift\n";
    if (deepSetting == 0) {
        missionData += "Depth sensor;\n";
        missionData = missionData + "Depth: " + std::to_string(newZ) + ";\n";
    } else {
        missionData += "Echo sounder;\n";
        missionData = missionData + "Distance: " + std::to_string(newZ) + ";\n";
    }
    if (deepType == 0) {
        missionData += "Spiral;\n\n";
    } else {
        missionData += "Vertical motors\n\n";
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
    if (newX + moveAccuracy < 5000 && newX + moveAccuracy > -5000) {
        return true;
    }
    return false;
}

const std::string &Move::GetMissionData() {
    missionData.clear();
    missionData += "Move\n";
    if (moveType == 0) {
        missionData += "Go to point;\n";
    } else {
        missionData += "Go on line;\n";
    }
    if (deepType == 0) {
        missionData += "Const depth;\n";
    } else {
        missionData += "Const distance\n";
    }
    missionData = missionData + "X: " + std::to_string(newX) + " +-" + std::to_string(moveAccuracy) + ";\n";
    missionData = missionData + "Y: " + std::to_string(newY) + " +-" + std::to_string(moveAccuracy) + ";\n\n";
    return missionData;
}

bool Return::Run() {
    return true;
}

const std::string &Return::GetMissionData() {
    return missionData;
}
