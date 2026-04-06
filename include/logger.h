/**
 * @file    logger.h
 * @brief   Simple logging utility
 * @version 1.0.0
 */

#ifndef LOGGER_H
#define LOGGER_H

/* ─── Log Levels ────────────────────────────────────────────────────────── */
typedef enum
{
    LOG_DEBUG = 0,
    LOG_INFO  = 1,
    LOG_WARN  = 2,
    LOG_ERROR = 3
} log_level_t;

/* ─── Macros ────────────────────────────────────────────────────────────── */
#define LOG_INFO_MSG(msg)     logger_write(LOG_INFO,  __FILE__, __LINE__, (msg))
#define LOG_WARN_MSG(msg)     logger_write(LOG_WARN,  __FILE__, __LINE__, (msg))
#define LOG_ERROR_MSG(msg)    logger_write(LOG_ERROR, __FILE__, __LINE__, (msg))
#define LOG_DEBUG_MSG(msg)    logger_write(LOG_DEBUG, __FILE__, __LINE__, (msg))

/* ─── Public API ────────────────────────────────────────────────────────── */
void logger_write(log_level_t level, const char *file, int line, const char *msg);
void logger_set_level(log_level_t level);

#endif /* LOGGER_H */
