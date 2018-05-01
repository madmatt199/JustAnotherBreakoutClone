#ifndef SIMPLELOGGER_HPP
#define SIMPLELOGGER_HPP

/**
 * @file SimpleLogger.hpp
 * @author muecker
 * @date 4/20/2018
**/

#include <string>
#include <map>
#include <ctime>
#include <fstream>

namespace SimpleLogging
{
    enum LOG_LEVEL
    {
        TRACE = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4
    };

    class SimpleLogger
    {
    private:
        // Members
        std::clock_t mStartClock;
        double mElapsedTimeSeconds;
        std::ofstream mOutfileStream;
        std::string mFileName;
        LOG_LEVEL mLogLevel;

        // Constants
        const std::string DEFAULT_FILE_NAME = "./logs/Default.log";
        std::map<LOG_LEVEL, std::string> LOG_LEVEL_STRINGS = {
            { LOG_LEVEL::TRACE, "TRA" },
            { LOG_LEVEL::DEBUG, "DBG" },
            { LOG_LEVEL::INFO, "INF" },
            { LOG_LEVEL::WARN, "WAR" },
            { LOG_LEVEL::ERROR, "ERR" }
        };

        // Functions
        std::string getTimestamp();
        std::string buildMessageHeader(LOG_LEVEL lgLvl);

    public:
        SimpleLogger();
        ~SimpleLogger();
        void initializeLogFile(std::string logFilePath);
        void setLogLevel(LOG_LEVEL lgLvl);
        void log(std::string message, LOG_LEVEL lgLvl = LOG_LEVEL::INFO);
    };
}

#endif
