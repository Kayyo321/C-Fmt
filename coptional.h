//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef COPTIONAL_H
#define COPTIONAL_H

#include "cresult.h"

typedef enum {
    HasValue,
    HasNoValue,
} OptionalState;

typedef struct {
    OptionalState state;
    c_fmt_FormatArg value;
} Optional;

Optional opt_some(c_fmt_FormatArg value);

bool opt_is_some(Optional opt);
bool opt_is_none(Optional opt);

Result opt_get_some(Optional opt);

extern const Optional opt_none;

#define with_some(opt, val, ...) \
    do { \
    if (opt_is_some(opt)) { \
        Result __##val = opt_get_some(opt); \
        assert_ok(__##val); \
        c_fmt_FormatArg val = __##val.value; \
        __VA_ARGS__ \
    } \
    } \
    while (0); \


#endif //COPTIONAL_H
