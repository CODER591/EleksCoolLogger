#include <filesystem>
#include <iostream>
#include "liblogger/cool_logger.h"


int main()
{
    CCoolLogger logger("cool_file.txt");

    logger.LogMsg(LogLevel_ERROR, "ERROR OMG!");
    logger.SetLeastLogLevel(LogLevel_ERROR);
    logger.LogMsg(LogLevel_INFO, "First Log message");
    logger.SetLeastLogLevel(LogLevel_INFO);
    logger.LogMsg(LogLevel_ERROR, "ERROR2 ERROR2!");
    logger.LogMsg(LogLevel_CRITICAL, "CRITICAL!");
    logger.LogMsg(LogLevel_INFO, "55555");
    logger.LogMsg(LogLevel_INFO, "66666");
    logger.LogMsg(LogLevel_ERROR, "7777");


    return 0;
}