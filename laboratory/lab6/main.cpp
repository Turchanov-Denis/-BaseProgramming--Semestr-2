#include <iostream>
#include "Logger.hpp"

int main() {

    utils::Logger log;
    log.SetLogFile();
    log.SetLogLevel(utils::Level::DEBUG);
    log.Write("firo");
//    log<< "firo";

    return 0;
}