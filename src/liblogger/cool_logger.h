#ifndef _COOL_LOGGER_H
#define _COOL_LOGGER_H

#include <string>
#include <string_view>
#include <stdio.h>

enum LogLevel
{
    LogLevel_NONE = -1, /*Not to use with messages*/
    LogLevel_INFO,
    LogLevel_WARN,
    LogLevel_ERROR,
    LogLevel_CRITICAL
};

class CCoolLogger
{
    private:
        LogLevel m_LogLevel;
        FILE* m_pFile;
        const std::string m_csFileActions = "w";
        std::string m_sLogFileName;

        void OpenLogFile();
        std::string_view GetLogLevelString(const LogLevel) const;
        void LogToScreen(const std::string_view&, const std::string&) const;
        void LogToFile(const std::string_view&, const std::string&) const;

    public:
        CCoolLogger();
        CCoolLogger(const std::string&);
        CCoolLogger(const CCoolLogger&) = delete;
        CCoolLogger& operator=(CCoolLogger&) = delete;
        CCoolLogger(CCoolLogger&&) = delete;
        CCoolLogger& operator=(CCoolLogger&&) = delete;
        ~CCoolLogger();

        void SetLeastLogLevel(const LogLevel);
        void LogMsg(LogLevel, const std::string&) const;
};

#endif /*! _COOL_LOGGER_H*/
