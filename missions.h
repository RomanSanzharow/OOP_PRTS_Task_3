#ifndef TASK_3_MISSIONS_H
#define TASK_3_MISSIONS_H

#include <string>
#include <memory>

class IMission {
public:
    virtual ~IMission() = default;

    virtual bool Run() = 0;

    virtual const std::string &GetMissionData() = 0;
};

class Dive: public IMission {
private:
    int deepSetting; // 0 -  датчик глубины (глубина) ; 1 - эхолот (отстояние)
    int newZ;
    int deepType; // 0 - спираль; 1 - вертикальные движители

    unsigned int currentDeep;

    int maxDeep = 100;
    int minDeep = 0;

    std::string missionData;

public:
    Dive() = delete;

    ~Dive() override = default;

    explicit Dive(int deepSetting, int deepValue, int deepType);

    bool Run() override;

    const std::string &GetMissionData() override;
};

class Lift: public IMission {
private:
    int deepSetting; // 0 -  датчик глубины (глубина) ; 1 - эхолот (отстояние)
    int newZ;
    int deepType; // 0 - спираль; 1 - вертикальные движители

    int maxDeep = 100;
    int minDeep = 0;

    std::string missionData;

public:
    Lift() = delete;

    ~Lift() override = default;

    explicit Lift(int deepSetting, int deepValue, int deepType);

    bool Run() override;

    const std::string &GetMissionData() override;
};

class Move: public IMission {
private:
    int newX;
    int newY;
    int moveType; // 0 - выход в точку; 1 - движение вдоль прямой
    int deepType; // 0 - на постоянной глубине; 1 - на постоянном отстоянии от дна

    int maxX = 5000;
    int minX = -5000;
    int maxY = 5000;
    int minY = -5000;

    int moveAccuracy = 200; // точность выхода

    std::string missionData;

public:
    Move() = delete;

    ~Move() override = default;

    explicit Move(int newX, int newY, int moveType, int deepType);

    bool Run() override;

    const std::string &GetMissionData() override;
};

class Return: public IMission {
private:
    int startX = 0;
    int startY = 0;

    std::string missionData = "Return\nКоордината X: 0;\nКоордината Y: 0\n\n";

public:
    Return() = default;

    ~Return() override = default;

    bool Run() override;

    const std::string &GetMissionData() override;
};

#endif
