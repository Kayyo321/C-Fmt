//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef A_STRING_H
#define A_STRING_H

#include <stdio.h>

/**
 * @brief Represents a dynamic string with associated metadata.
 *
 * The String structure is designed to hold a dynamically allocated
 * null-terminated string, its associated length, and its capacity.
 * It supports various operations, such as initialization, copying,
 * substring creation, and allocation of strings with specific capacity.
 *
 * This structure ensures proper management of memory and provides
 * flexibility for handling strings of varying lengths.
 *
 * @struct String
 * @var data
 * Pointer to the dynamically allocated null-terminated character array,
 * which holds the actual string content.
 * @var length
 * The length of the string (not including the null-terminator).
 * @var capacity
 * The total capacity of the allocated memory for the string, including
 * the null-terminator.
 */
typedef struct _String {
    char *data;
    size_t length;
    size_t capacity;
} String;

#endif //A_STRING_H
