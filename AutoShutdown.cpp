// AutoShutdown.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "shutdown.h"


int main()
{
    //std::cout << "Hello World!\n";
    std::string str = "23:45";
    ShutDown s(str);
    AutoPowerOn();
    return 0;
}
