/**
 * @file    http_parser.h
 * @brief   HTTP Request Parser API
 * @version 1.0.0
 */

#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "http_server.h"

/* ─── Return Codes ──────────────────────────────────────────────────────── */
typedef enum
{
    PARSE_OK        =  0,
    PARSE_ERR       = -1,
    PARSE_MALFORMED = -2
} parse_status_t;

/* ─── Public API ────────────────────────────────────────────────────────── */

/**
 * @brief  Parse a raw HTTP request buffer into an http_request_t struct.
 * @param  raw_buf  Raw request string received from socket.
 * @param  buf_len  Length of raw_buf.
 * @param  out_req  Output parsed request struct.
 * @return PARSE_OK on success, error code otherwise.
 */
parse_status_t http_parse_request(const char    *raw_buf,
                                  uint32_t       buf_len,
                                  http_request_t *out_req);

/**
 * @brief  Build an HTTP response string from an http_response_t struct.
 * @param  resp     Populated response struct.
 * @param  out_buf  Output buffer to write response into.
 * @param  buf_size Size of out_buf.
 * @return Number of bytes written, or -1 on error.
 */
int32_t http_build_response(const http_response_t *resp,
                            char                  *out_buf,
                            uint32_t               buf_size);

#endif /* HTTP_PARSER_H */
