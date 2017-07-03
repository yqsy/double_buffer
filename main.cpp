#include "hq_data.h"

#include <thread>
#include <chrono>
#include <iostream>

int main() {

    HqData::instance().StartReading();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    std::cout << HqData::instance().ReadFastHq("518885");

    getchar();
    return 0;
}