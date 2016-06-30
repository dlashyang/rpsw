#ifndef RPSW_LOG_H
#define RPSW_LOG_H

#include "Poco/Logger.h"

#define rpsw_fatal(logger, msg...) \
    if ((logger).fatal()) (logger).fatal(msg); else (void) 0

#define rpsw_critical(logger, msg...) \
    if ((logger).critical()) (logger).critical(msg); else (void) 0

#define rpsw_error(logger, msg...) \
    if ((logger).error()) (logger).error(msg); else (void) 0

#define rpsw_warning(logger, msg...) \
    if ((logger).warning()) (logger).warning(msg); else (void) 0

#define rpsw_notice(logger, msg...) \
    if ((logger).notice()) (logger).notice(msg); else (void) 0

#define rpsw_info(logger, msg...) \
    if ((logger).information()) (logger).information(msg); else (void) 0

#define rpsw_debug(logger, msg...) \
    if ((logger).debug()) (logger).debug(msg); else (void) 0

#define rpsw_trace(logger, msg...) \
    if ((logger).trace()) (logger).trace(msg); else (void) 0

#endif //#ifndef RPSW_LOG_H
