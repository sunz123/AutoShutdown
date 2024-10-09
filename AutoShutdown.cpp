// AutoShutdown.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "shutdown.h"


int main()
{
    //std::cout << "Hello World!\n";
    ShutDown s("23:47");
    AutoPowerOn();
    return 0;
}
