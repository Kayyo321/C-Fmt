//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CRESULT_H
#define CRESULT_H

#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "cfmt.h"

#define assert_ok(result) assert(is_ok(result))
#define assert_err(result) assert(is_err(result))
#define assert_eq(a, b) assert((a) == (b))
#define assert_str_eq(a, b) assert(strcmp((a), (b)) == 0)

typedef enum {
    Ok = true,
    Err = false
} ResultTag;

typedef struct {
    ResultTag tag;
    c_fmt_FormatArg value;
} Result;

Result ok_result(c_fmt_FormatArg value);
Result err_result(const char *err_msg);

bool is_ok(Result result);
bool is_err(Result result);

void println_err_result(Result result);

c_fmt_Any result_as(Result result);

#endif //CRESULT_H
