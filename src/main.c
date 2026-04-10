/**
 * @file    main.c
 * @brief   Entry point — configure and start the HTTP server
 *
 * @note    INTENTIONAL MISRA-C:2012 VIOLATIONS (for educational purposes):
 *          See comments marked [MISRA VIOLATION] throughout this file.
 *
 * @version 1.0.0
 */

/* ─── System Includes ───────────────────────────────────────────────────── */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>

/* ─── Project Includes ──────────────────────────────────────────────────── */
#include "http_server.h"
#include "logger.h"

/* ─── Portability Issue Functions ───────────────────────────────────────── */

/* [PORTABILITY ISSUE] Using sizeof() for type checking on platforms */
void check_integer_sizes(void)
{
    /* [PORTABILITY ISSUE] Assuming sizes without checking - non-portable */
    if (sizeof(long) == 4) {
        printf("32-bit long detected\n");
    }
    
    /* [PORTABILITY ISSUE] Using long long without portable checks */
    long long big_number = 9223372036854775807LL;
    (void)printf("Big number: %lld\n", big_number);
}

/* [PORTABILITY ISSUE] Using uninitialized variable - behavior is platform-dependent */
void portability_issue_function(void)
{
    char buffer[32];
    int value = 12345;
    int uninitialized_var;  /* [PORTABILITY ISSUE] Variable not initialized */
    
    /* Platform-dependent behavior due to uninitialized variable */
    if (uninitialized_var > 0) {  /* [PORTABILITY ISSUE] Using uninitialized variable */
        printf("Uninitialized value: %d\n", uninitialized_var);
    }
    
    /* [PORTABILITY ISSUE] Using platform-specific printf format specifiers */
    printf("Value: %d, Size: %zu\n", value, sizeof(int));
    
    /* [PORTABILITY ISSUE] Array size determination - assumes 4-byte int */
    int array_size = 100;
    int *platform_array = (int *)malloc(array_size * sizeof(int));
    
    if (platform_array != NULL) {
        platform_array[0] = 42;
        free(platform_array);
    }
}

/* ─── Signal Handler ────────────────────────────────────────────────────── */

/* [MISRA VIOLATION] Rule 21.5 — use of signal() not recommended in
 * safety-critical code; behaviour is implementation-defined */
static void sig_handler(int sig)  /* MISRA Rule 21.5 */
{
    (void)sig;
    printf("\n[MAIN] Signal received — shutting down...\n"); /* MISRA Rule 21.6 */
    server_shutdown();
}

/* ─── main ──────────────────────────────────────────────────────────────── */

int main(void)
{
    server_config_t  config;
    server_status_t  status;

    /* [MISRA VIOLATION] Rule 21.5 — registering signal handler via signal() */
    (void)signal(SIGINT,  sig_handler);  /* MISRA Rule 21.5 */
    (void)signal(SIGTERM, sig_handler);  /* MISRA Rule 21.5 */
    
    /* Call portability issue function to enable analysis */
    check_integer_sizes();
    portability_issue_function();

    printf("===========================================\n");  /* MISRA Rule 21.6 */
    printf("  Simple Webserver v%s\n", SERVER_VERSION_STR);   /* MISRA Rule 21.6 */
    printf("===========================================\n");  /* MISRA Rule 21.6 */

    /* Build server config */
    config.port        = SERVER_DEFAULT_PORT;
    config.max_clients = SERVER_MAX_CLIENTS;
    config.verbose     = 1U;

    LOG_INFO_MSG("Initialising server...");

    /* Initialise server */
    status = server_init(&config);

    if (status != SERVER_OK)
    {
        LOG_ERROR_MSG("server_init() failed — exiting.");

        /* [MISRA VIOLATION] Rule 21.8 — use of exit() not allowed in
         * MISRA-compliant embedded code; prefer returning from main */
        exit(EXIT_FAILURE);  /* MISRA Rule 21.8 */
    }

    LOG_INFO_MSG("Server initialised successfully.");

    /* Start blocking run loop */
    status = server_run();

    if (status != SERVER_OK)
    {
        LOG_ERROR_MSG("server_run() returned error.");
        return EXIT_FAILURE;
    }

    LOG_INFO_MSG("Goodbye!");

    return EXIT_SUCCESS;
}
