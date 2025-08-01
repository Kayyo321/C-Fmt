//
// Created by Jessica Bruce on 8/1/25.
//

#include "coptional.h"

Optional opt_some(const c_fmt_FormatArg value) {
    return (Optional){.state = HasValue, .value = value};
}

bool opt_is_some(const Optional opt) {
    return opt.state == HasValue;
}

bool opt_is_none(const Optional opt) {
    return opt.state == HasNoValue;
}

Result opt_get_some(const Optional opt) {
    if (opt_is_none(opt)) {
        return err_result("Optional has no value");
    }

    return ok_result(opt.value);
}

const Optional opt_none = {.state = HasNoValue, .value = APtr(NULL)};