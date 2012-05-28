#include "errors.h"

void app_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void system_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

