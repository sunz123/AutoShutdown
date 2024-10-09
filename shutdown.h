#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <tchar.h>

class ShutDown
{
public:
    explicit ShutDown(std::string target);
    void getCurTime();
    void exec();
    int computeSec();
    int getWday();
    int getMon();
private:
    struct tm p;
    std::string target;
};

void AutoPowerOn();
void CanclePowerOn();
