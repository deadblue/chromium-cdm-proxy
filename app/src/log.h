#ifndef CDM_PROXY_LOG_H
#define CDM_PROXY_LOG_H

#include <stdio.h>
#include <string.h>

#define LOG_PREFIX "[ZeasnLog][%s(%d)] %s - "
#define LOG_NEWLINE "\n"
#define FILE_NAME strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define ZLOG(message, args...) \
    fprintf(stderr, LOG_PREFIX message LOG_NEWLINE, FILE_NAME, __LINE__, __FUNCTION__, ## args)

#endif //CDM_PROXY_LOG_H
