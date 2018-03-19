//
// Created by Firat Agdas on 3/17/18.
//

#ifndef OPENGLLEARNINGLIBRARY_LOGGER_H
#define OPENGLLEARNINGLIBRARY_LOGGER_H

#include "Common.h"
#include <string>

#define MAX_VARIADIC_ARG_COUNT 10

#define logDebug(M) Logger::shared().log(Logger::Debug, (M))
#define logInfo(M) Logger::shared().log(Logger::Info, (M))
#define logVerbose(M) Logger::shared().log(Logger::Verbose, (M))
#define logWarning(M) Logger::shared().log(Logger::Warning, (M))
#define logCritical(M) Logger::shared().log(Logger::Critical, (M))
#define logError(M) Logger::shared().log(Logger::Error, (M))


#define logDebugV(M, ...) Logger::shared().log(Logger::Debug, (M), __VA_ARGS__)
#define logInfoV(M, ...) Logger::shared().log(Logger::Info, (M), __VA_ARGS__)
#define logVerboseV(M, ...) Logger::shared().log(Logger::Verbose, (M), __VA_ARGS__)
#define logWarningV(M, ...) Logger::shared().log(Logger::Warning, (M), __VA_ARGS__)
#define logCriticalV(M, ...) Logger::shared().log(Logger::Critical, (M), __VA_ARGS__)
#define logErrorV(M, ...) Logger::shared().log(Logger::Error, (M), __VA_ARGS__)

#define logCDebug(C, M) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Debug, (M))
#define logCInfo(C, M) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Info, (M))
#define logCVerbose(C, M) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Verbose, (M))
#define logCWarning(C, M) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Warning, (M))
#define logCCritical(C, M) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Critical,(M))
#define logCError(C, M) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Error, (M))

#define logCDebugV(C, M, ...) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Debug, (M), __VA_ARGS__)
#define logCInfoV(C, M, ...) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Info, (M), __VA_ARGS__)
#define logCVerboseV(C, M, ...) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Verbose, (M), __VA_ARGS__ )
#define logCWarningV(C, M, ...) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Warning, (M), __VA_ARGS__ )
#define logCCriticalV(C, M, ...) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Critical,(M), __VA_ARGS__)
#define logCErrorV(C, M, ...) Logger::shared().log(Logger_Category_ ## C ::categoryName, Logger::Error, (M), __VA_ARGS__)

#define LOGGER_DECLARE_CATEGORY(A) \
    class Logger_Category_ ## A { \
    public: \
        static const char *categoryName; \
    };

#define LOGGER_CATEGORY(A, B) const char *Logger_Category_ ## A ::categoryName = B;

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

    void log(LogType type, const char *message, ...);

    void log(const char *category, LogType type, const char *message, ...);

    static Logger &shared() { return m_sharedInstance; }

private:
    void print(const char *format, LogType type, const char *message);

private:
    static Logger m_sharedInstance;
    const char *m_format;
};


#endif //OPENGLLEARNINGLIBRARY_LOGGER_H
