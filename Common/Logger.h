//
// Created by Firat Agdas on 3/17/18.
//

#ifndef OPENGLLEARNINGLIBRARY_LOGGER_H
#define OPENGLLEARNINGLIBRARY_LOGGER_H

#include "Common.h"
#include <string>


class Logger {
public:
    enum LogType {
        Info,
        Debug,
        Verbose,
        Warning,
        Critical,
        Error
    };

    Logger();

    void log(LogType type, const std::string &message) { log(type, message.c_str()); }

    void debug(const std::string &message) { log(Debug, message.c_str()); }

    void info(const std::string &message) { log(Info, message.c_str()); }

    void verbose(const std::string &message) { log(Verbose, message.c_str()); }

    void warning(const std::string &message) { log(Warning, message.c_str()); }

    void critical(const std::string &message) { log(Critical, message.c_str()); }

    void error(const std::string &message) { log(Error, message.c_str()); }

    void log(LogType type, const char *message);

    void debug(const char *message) { log(Debug, message); }

    void info(const char *message) { log(Info, message); }

    void verbose(const char *message) { log(Verbose, message); }

    void warning(const char *message) { log(Warning, message); }

    void critical(const char *message) { log(Critical, message); }

    void error(const char *message) { log(Error, message); }

    static Logger &shared() { return m_sharedInstance; }

private:
    static Logger m_sharedInstance;
    const char *m_format;
};


#endif //OPENGLLEARNINGLIBRARY_LOGGER_H
