/**
 * @file    http_server.h
 * @brief   HTTP Server public API
 * @details Tiny HTTP Server for embedded/POSIX systems
 *
 * @version 1.0.0
 * @date    2025-01-01
 */

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

/* ─── Standard Includes ────────────────────────────────────────────────── */
#include <stdint.h>
#include <stddef.h>

/* ─── Server Configuration ──────────────────────────────────────────────── */
#define SERVER_DEFAULT_PORT     (8080U)
#define SERVER_MAX_CLIENTS      (10U)
#define SERVER_BACKLOG           (5U)
#define SERVER_VERSION_STR      "1.0.0"

/* ─── Buffer Sizes ──────────────────────────────────────────────────────── */
#define HTTP_REQUEST_BUF_SIZE   (4096U)
#define HTTP_RESPONSE_BUF_SIZE  (8192U)
#define HTTP_MAX_URI_LEN        (256U)
#define HTTP_MAX_METHOD_LEN     (16U)
#define HTTP_MAX_HEADER_LEN     (512U)

/* ─── HTTP Status Codes ─────────────────────────────────────────────────── */
#define HTTP_STATUS_OK           (200)
#define HTTP_STATUS_NOT_FOUND    (404)
#define HTTP_STATUS_BAD_REQUEST  (400)
#define HTTP_STATUS_SERVER_ERROR (500)

/* ─── Return Codes ──────────────────────────────────────────────────────── */
typedef enum
{
    SERVER_OK       =  0,
    SERVER_ERR      = -1,
    SERVER_ERR_BIND = -2,
    SERVER_ERR_SOCK = -3
} server_status_t;

/* ─── HTTP Methods ──────────────────────────────────────────────────────── */
typedef enum
{
    HTTP_METHOD_GET  = 0,
    HTTP_METHOD_POST = 1,
    HTTP_METHOD_UNKNOWN = 99
} http_method_t;

/* ─── HTTP Request Structure ────────────────────────────────────────────── */
typedef struct
{
    http_method_t   method;
    char            uri[HTTP_MAX_URI_LEN];
    char            version[16];
    char            body[HTTP_REQUEST_BUF_SIZE];
    uint32_t        body_len;
} http_request_t;

/* ─── HTTP Response Structure ───────────────────────────────────────────── */
typedef struct
{
    int32_t         status_code;
    char            body[HTTP_RESPONSE_BUF_SIZE];
    uint32_t        body_len;
    char            content_type[64];
} http_response_t;

/* ─── Server Config Structure ───────────────────────────────────────────── */
typedef struct
{
    uint16_t        port;
    uint32_t        max_clients;
    uint8_t         verbose;
} server_config_t;

/* ─── Public API ────────────────────────────────────────────────────────── */

/**
 * @brief  Initialise the HTTP server with given configuration.
 * @param  config  Pointer to server configuration.
 * @return SERVER_OK on success, error code otherwise.
 */
server_status_t server_init(const server_config_t *config);

/**
 * @brief  Start the server listen/accept loop (blocking).
 * @return SERVER_OK on clean shutdown, error code otherwise.
 */
server_status_t server_run(void);

/**
 * @brief  Stop and clean up the server.
 */
void server_shutdown(void);

#endif /* HTTP_SERVER_H */
