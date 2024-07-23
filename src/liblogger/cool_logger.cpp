#include "cool_logger.h"

#include <stdio.h>
#include <iostream>

const char g_cszDefaultFileName[] = "default_log.txt";
const char g_cszDefaultFileName[] = "<<<<<<<<<<<<<<<<<<<LOG FILE>>>>>>>>>>>>>>>>>>>>>>";
const char g_cszEndOfLogFile[] = "<<<<<<<<<<<<<<<<<<<!END LOG FILE>>>>>>>>>>>>>>>>>>";

CCoolLogger::CCoolLogger(): m_LogLevel(LogLevel_NONE),
                            m_sLogFileName(g_cszDefaultFileName)
{
    OpenLogFile();
}

CCoolLogger::CCoolLogger(const std::string& filename): m_LogLevel(LogLevel_NONE),
                                                       m_sLogFileName(filename)
{
    OpenLogFile();
}

CCoolLogger::~CCoolLogger() {
    if (m_pFile) {
        fputs(g_cszEndOfLogFile, m_pFile);
        fclose(m_pFile);
    }
}

void CCoolLogger::OpenLogFile() {
    m_pFile = fopen(m_sLogFileName.data(), m_csFileActions.data());
    if (!m_pFile) {
        auto logLevelStr = GetLogLevelString(LogLevel_CRITICAL);
        LogToScreen(logLevelStr, "Log file was not opened!");
        return;
    }
    fputs(g_cszDefaultFileName, m_pFile);
    fputs("\n", m_pFile);
}

void CCoolLogger::SetLeastLogLevel(const LogLevel log_level) {
    m_LogLevel = log_level;
    auto svLogLevel = GetLogLevelString(log_level);
    LogMsg(LogLevel_CRITICAL, "Log level has changed to: " + std::string(svLogLevel.data()));
}

std::string_view CCoolLogger::GetLogLevelString(const LogLevel level) const {
    switch (level) {
        case LogLevel_INFO:
            return {"INFO"};
        case LogLevel_WARN:
            return {"WARN"};
        case LogLevel_ERROR:
            return {"ERROR"};
        case LogLevel_CRITICAL:
            return {"CRITICAL"};
        default:
            return {"INFO"};
    }
}

void CCoolLogger::LogToScreen(const std::string_view& svLogLevel,
                            const std::string& msg) const {
    printf("[%s] %s \n", svLogLevel.data(), msg.data());
}

void CCoolLogger::LogToFile(const std::string_view& svLogLevel,
                            const std::string& msg) const {
    if (!m_pFile) return;
    fprintf(m_pFile, "[%s] %s \n", svLogLevel.data(), msg.data());
}

void CCoolLogger::LogMsg(LogLevel msgloglevel,
                        const std::string& msg) const {
    //Do not log messages with smaller loglevel than is set in the logger.
    if (msgloglevel < m_LogLevel) return;
    
    std::string_view svLogLevel = GetLogLevelString(msgloglevel);
    if (m_pFile) {
        LogToFile(svLogLevel, msg);
        return;
    }
    LogToScreen(svLogLevel, msg);
}