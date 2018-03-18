//
// Created by Firat Agdas on 3/17/18.
//

#include "Logger.h"
#include <stdio.h>

Logger::Logger()
    : m_format("[%s]: %s\n") {
}

void Logger::log(LogType type, const char *message) {
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
            fprintf(stdout, m_format, (const char *) &typeIndicator, message);
            break;

        case Critical:
        case Error:
            fprintf(stderr, m_format, (const char *) &typeIndicator, message);
            break;
    }

    fprintf(stdin, "%s\n", "Logginggggg");
}

Logger Logger::m_sharedInstance;