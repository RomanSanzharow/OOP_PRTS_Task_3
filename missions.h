#ifndef TASK_3_MISSIONS_H
#define TASK_3_MISSIONS_H

#include <string>
#include <memory>

class IMission {
public:
    bool Run();
    const std::string &GetMissionData();
	~IMission();
};

class Dive: public IMission {
private:
    int deepSetting; // 0 -  датчик глубины (глубина) ; 1 - эхолот (отстояние)
    int newZ;
    int deepType; // 0 - спираль; 1 - вертикальные движители
    unsigned int currentDeep;
    const int maxDeep = 100;
    const int minDeep = 0;
    std::string missionData;
public:
    Dive();
    explicit Dive(int deepSetting, int deepValue, int deepType);
    bool Run()  ;
    const std::string &GetMissionData();
    ~Dive();
};

class Lift: public IMission {
private:
    int deepSetting; // 0 -  датчик глубины (глубина) ; 1 - эхолот (отстояние)
    int newZ;
    int deepType; // 0 - спираль; 1 - вертикальные движители
    const int maxDeep = 100;
    const int minDeep = 0;
    std::string missionData;
public:
    Lift();
    explicit Lift(int deepSetting, int deepValue, int deepType);
    bool Run()  ;
    const std::string GetMissionData();
    ~Lift();
};

class Move: public IMission {
private:
    int newX;
    int newY;
    int moveType; // 0 - выход в точку; 1 - движение вдоль прямой
    int deepType; // 0 - на постоянной глубине; 1 - на постоянном отстоянии от дна
    const int maxX = 10000;
    const int minX = 0;
    const int maxY = 10000;
    const int minY = 0;
    int moveAccuracy = 5; // точность выхода
    std::string missionData;
public:
    Move();
    explicit Move(int newX, int newY, int moveType, int deepType);
    bool Run()  ;
    const std::string &GetMissionData();
    ~Move();
};

class Return: public IMission {
private:
    const int startX = 0;
    const int startY = 0;
    std::string missionData = "Return\nX: 0;\nY: 0\n\n";
public:
    Return();
    bool Run();
    const std::string &GetMissionData();
    ~Return();
};

#endif
