//
// Created by Jessica Bruce on 7/31/25.
//

#include "cresult.h"

Result ok_result(const c_fmt_FormatArg value) {
    return (Result){.tag=Ok, .value=value};
}

Result err_result(const char *err_msg) {
    return (Result){.tag=Err, .value=ACStr(err_msg)};
}

bool is_ok(const Result result) {
    return result.tag == Ok;
}

bool is_err(const Result result) {
    return result.tag == Err;
}

void println_err_result(const Result result) {
    if (!is_err(result))
        return;

    c_print_stderr("{}\n", result.value);
}

c_fmt_Any result_as(const Result result) {
    return result.value.value;
}


