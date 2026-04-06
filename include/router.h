/**
 * @file    router.h
 * @brief   HTTP Request Router API
 * @version 1.0.0
 */

#ifndef ROUTER_H
#define ROUTER_H

#include "http_server.h"

/* ─── Route Handler Function Pointer ───────────────────────────────────── */
typedef void (*route_handler_fn)(const http_request_t  *req,
                                        http_response_t *resp);

/* ─── Route Entry ───────────────────────────────────────────────────────── */
typedef struct
{
    char              path[HTTP_MAX_URI_LEN];
    http_method_t     method;
    route_handler_fn  handler;
} route_entry_t;

#define MAX_ROUTES (16U)

/* ─── Public API ────────────────────────────────────────────────────────── */

/**
 * @brief  Register a route with its handler function.
 */
void router_register(const char *path, http_method_t method, route_handler_fn handler);

/**
 * @brief  Dispatch an incoming request to the correct handler.
 */
void router_dispatch(const http_request_t *req, http_response_t *resp);

#endif /* ROUTER_H */
