#include "cool_logger.h"

#include <stdio.h>
#include <iostream>

const char g_cszDefaultFileName[] = "default_log.txt";
const char g_cszBeginFileName[] = "<<<<<<<<<<<<<<<<<<<LOG FILE>>>>>>>>>>>>>>>>>>>>>>";
const char g_cszEndOfLogFile[] = "<<<<<<<<<<<<<<<<<<<!END LOG FILE>>>>>>>>>>>>>>>>>>";

CCoolLogger::CCoolLogger(): m_LogLevel(LogLevel_NONE),
                            m_sLogFileName(g_cszDefaultFileName)
{
    OpenLogFile();
}

CCoolLogger::CCoolLogger(const std::string& csFilename): m_LogLevel(LogLevel_NONE),
                                                       m_sLogFileName(csFilename)
{
    OpenLogFile();
}

CCoolLogger::~CCoolLogger()
{
    if (m_pFile)
    {
        fputs(g_cszEndOfLogFile, m_pFile);
        fclose(m_pFile);
    }
}

void CCoolLogger::OpenLogFile()
{
    m_pFile = fopen(m_sLogFileName.data(), m_csFileActions.data());
    if (!m_pFile)
    {
        std::string_view logLevelStr = GetLogLevelString(LogLevel_CRITICAL);
        LogToScreen(logLevelStr, "Log file was not opened!");
        return;
    }
    fputs(g_cszBeginFileName, m_pFile);
    fputs("\n", m_pFile);
}

void CCoolLogger::SetLeastLogLevel(const LogLevel cLogLevel)
{
    m_LogLevel = cLogLevel;
    std::string_view svLogLevel = GetLogLevelString(cLogLevel);
    LogMsg(LogLevel_CRITICAL, "Log level has changed to: " + std::string(svLogLevel.data()));
}

std::string_view CCoolLogger::GetLogLevelString(const LogLevel cLogLevel) const
{
    switch (cLogLevel)
    {
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

void CCoolLogger::LogToScreen(const std::string_view& csvLogLevel,
                            const std::string& csMessage) const
{
    printf("[%s] %s \n", csvLogLevel.data(), csMessage.data());
}

void CCoolLogger::LogToFile(const std::string_view& csvLogLevel,
                            const std::string& csMessage) const
{
    if (!m_pFile) { return; }
    fprintf(m_pFile, "[%s] %s \n", csvLogLevel.data(), csMessage.data());
}

void CCoolLogger::LogMsg(const LogLevel cMsgLogLevel,
                        const std::string& csMessage) const
{
    //Do not log messages with smaller loglevel than is set in the logger.
    if (cMsgLogLevel < m_LogLevel) { return; }
    
    std::string_view svLogLevel = GetLogLevelString(cMsgLogLevel);
    if (m_pFile)
    {
        LogToFile(svLogLevel, csMessage);
        return;
    }
    LogToScreen(svLogLevel, csMessage);
}