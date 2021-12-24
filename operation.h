#ifndef TASK_3_OPERATION_H
#define TASK_3_OPERATION_H

#include <string>
#include <vector>

#include "missions.h"

class Operation {
private:
    std::vector<std::unique_ptr<IMission>> missionsList;
    std::vector<std::unique_ptr<IMission>> deletedMissionsList;
    std::unique_ptr<IMission> currentMission;
public:
    Operation() = default;
    void Do();
    void UpdateFileWithOperationData() const;
    void SetMission(std::unique_ptr<IMission> mission);
    void ShowOperation() const;
    void ShowDeletedOperation() const;
    int getOperationLen() const;
    int getDeletedOperationLen() const;
    void SwapMissions(size_t idx1, size_t idx2);
    void DeleteMission(size_t idx);
    void InsertMission(size_t idx, std::unique_ptr<IMission> mission);
    void PushDeletedMission(size_t idx);
    ~Operation() = default;
};
#endif
