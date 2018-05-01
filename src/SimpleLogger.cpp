/**
 * @file SimpleLogger.cpp
 * @author muecker
 * @date 4/20/2018
**/

#include "SimpleLogger.hpp"
#include <sstream>
#include <iomanip>

namespace SimpleLogging
{
    /**
     * Constructor for the logger.
    **/
    SimpleLogger::SimpleLogger()
    {
        mStartClock = std::clock();
        mElapsedTimeSeconds = 0;
        mLogLevel = LOG_LEVEL::INFO;
    }

    /**
     * De-constructor for the logger.
     *
     * Closes any open streams.
    **/
    SimpleLogger::~SimpleLogger()
    {
        if (mOutfileStream.is_open())
        {
            log("Shutting down logging framework.");
            mOutfileStream.close();
        }
    }

    /**
     * Opens the log file specified and saves its path.
     *
     * @param logFilePath Absolute path to the specified log file.
    **/
    void SimpleLogger::initializeLogFile(std::string logFilePath)
    {
        mOutfileStream.open(logFilePath, std::ofstream::out);
        mFileName = logFilePath;
    }

    /**
     * Sets the log level during runtime.
     *
     * @param lgLvl The log level object to set the current level to.
    **/
    void SimpleLogger::setLogLevel(LOG_LEVEL lgLvl)
    {
        mLogLevel = lgLvl;
    }

    /**
     * Creates a message header from the current log level and a timestamp.
    **/
    std::string SimpleLogger::buildMessageHeader(LOG_LEVEL lgLvl)
    {
        std::stringstream ss;
        ss.str("");

        ss << "[" << LOG_LEVEL_STRINGS[lgLvl] << "]";
        ss << getTimestamp();

        return ss.str();
    }

    /**
     * Obtains the current elapsed time of the application as pulled from the system clock.
     *
     * @return String containing a preformatted timestamp.
     */
    std::string SimpleLogger::getTimestamp()
    {
        std::stringstream ss;
        ss.str("");

        mElapsedTimeSeconds = static_cast<double>((std::clock() - mStartClock) / (double)CLOCKS_PER_SEC);

        ss << std::setprecision(7) << "{" << mElapsedTimeSeconds << "s} ";
        return ss.str();
    }

    /**
     * Logs the message with the given log level.
     *
     * @param message A string message for the log.
     * @param lgLvl The log level, if no argument is used defaults to INFO.
    **/
    void SimpleLogger::log(std::string message, LOG_LEVEL lgLvl)
    {
        if (mOutfileStream.is_open())
        {
            if (lgLvl >= mLogLevel)
            {
                mOutfileStream << buildMessageHeader(lgLvl) << message << std::endl;
            }
        }
    }
}