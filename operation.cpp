#include <iostream>
#include <fstream>
#include "operation.h"
#include "missions.h"

void Operation::Do() {
    if (currentMission->Run()) {
        missionsList.push_back(std::move(currentMission));
        UpdateFileWithOperationData();
        return;
    }
    std::cout << "Mission impossible. Out of border." << std::endl;
}

void Operation::UpdateFileWithOperationData() const {
    std::string operationData;
    for (const auto& mission : missionsList) {
        operationData += mission->GetMissionData();
    }
    std::ofstream outFile ("operation.txt");
    outFile << operationData << std::endl;
    outFile.close();
}

void Operation::SetMission(std::unique_ptr<IMission> mission) {
    currentMission = std::move(mission);
}

void Operation::ShowOperation() const {
    int missionIndex = 0;
    for (const auto &mission : missionsList) {
        std::cout << "Mission " << missionIndex++ << std::endl;
        std::cout << mission->GetMissionData();
    }
}

void Operation::ShowDeletedOperation() const {
    int missionIndex = 0;
    for (const auto &mission : deletedMissionsList) {
        std::cout << "Mission " << missionIndex++ << std::endl;
        std::cout << mission->GetMissionData();
    }
}

size_t Operation::getOperationLen() const {
    return missionsList.size();
}

size_t Operation::getDeletedOperationLen() const {
    return deletedMissionsList.size();
}

void Operation::SwapMissions(size_t idx1, size_t idx2) {
    size_t operationLen = missionsList.size();
    if (idx1 >= 0 && idx2 >= 0 && idx1 < operationLen && idx2 < operationLen) {
        std::swap(missionsList[idx1], missionsList[idx2]);
        UpdateFileWithOperationData();
        return;
    }
    std::cout << "Incorrect index" << std::endl;
}

void Operation::DeleteMission(size_t idx) {
    if (idx < missionsList.size() && idx >= 0) {
        deletedMissionsList.push_back(std::move(missionsList[idx]));
        missionsList.erase(missionsList.begin() + idx);
        UpdateFileWithOperationData();
        return;
    }
    std::cout << "Incorrect index" << std::endl;
}

void Operation::InsertMission(size_t idx, std::unique_ptr<IMission> mission) {
    if (idx >= 0 && idx < missionsList.size()) {
        if (mission->Run()) {
            missionsList.insert(missionsList.begin() + idx, std::move(mission));
            UpdateFileWithOperationData();
            return;
        }
        std::cout << "Mission impossible. Out of border." << std::endl;
        return;
    }
    std::cout << "Incorrect index" << std::endl;
}

void Operation::PushDeletedMission(size_t idx) {
    if (idx >= 0 && idx < missionsList.size()) {
        missionsList.push_back(std::move(deletedMissionsList[idx]));
        deletedMissionsList.erase(deletedMissionsList.begin() + idx);
        UpdateFileWithOperationData();
        return;
    }
    std::cout << "Incorrect index" << std::endl;
}
