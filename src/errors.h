/*
 * Errors.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef ERRORS_H
#define ERRORS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* used for strerror */

/*
 * An error thrown by this program, such as an assertion failing or the
 * state getting into a positions it shouldn't be able to
 *
 * prints the error message, then terminates the program.
 */
void app_error(char *msg);

/*
 * An error occurred during a system call, such as running out of memory
 * on a malloc
 *
 * Prints the error message as well as the erno set by the syscall, then
 * terminates the program.
 */
void system_error(char *msg);

#endif

