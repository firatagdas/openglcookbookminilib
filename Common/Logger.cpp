//
// Created by Firat Agdas on 3/17/18.
//

#include "Logger.h"
#include <stdio.h>

Logger::Logger()
    : m_format("[%s]: %s\n") {
}

void Logger::log(LogType type, const char *message, ...) {
    va_list args;
    va_start(args, message);

    char buffer[2048];

    vsnprintf(buffer, 2048, message, args);
    va_end(args);

    print(m_format, type, buffer);
}

void Logger::log(const char *category, LogType type, const char *message, ...) {
    va_list args;
    va_start(args, message);

    char buffer[2048];

    vsnprintf(buffer, 2048, message, args);
    va_end(args);

    std::string tmp;
    tmp.append("[");
    tmp.append(category);
    tmp.append("]: ");
    tmp.append(buffer);

    print(m_format, type, tmp.c_str());
}

void Logger::print(const char *format, LogType type, const char *message) {
    char typeIndicator[2];

    switch (type) {
        case Debug:
            typeIndicator[0] = 'D';
            break;

        case Info:
            typeIndicator[0] = 'I';
            break;

        case Verbose:
            typeIndicator[0] = 'V';
            break;

        case Warning:
            typeIndicator[0] = 'W';
            break;

        case Critical:
            typeIndicator[0] = 'C';
            break;

        case Error:
            typeIndicator[0] = 'E';
            break;
    }
    typeIndicator[1] = '\0';

    switch (type) {
        case Debug:
        case Info:
        case Verbose:
        case Warning:
            fprintf(stdout, format, (const char *) &typeIndicator, message);
            break;

        case Critical:
        case Error:
            fprintf(stderr, format, (const char *) &typeIndicator, message);
            break;
    }
}

Logger Logger::m_sharedInstance;