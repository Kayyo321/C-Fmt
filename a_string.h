//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef A_STRING_H
#define A_STRING_H

#include <stdio.h>

typedef struct _String {
    char *data;
    size_t length;
    size_t capacity;
} String;

#endif //A_STRING_H
