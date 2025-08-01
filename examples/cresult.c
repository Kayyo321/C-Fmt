//
// Created by Jessica Bruce on 8/1/25.
//

#include "../cresult.h"

Result divide(int x, int y) {
    if (y == 0) {
        return err_result("Cannot divide by zero");
    }

    return ok_result(AInt(x / y));
}

void use_results() {
    Result result = divide(10, 2);
    /// This code will be ran because this returned an Ok value
    if (is_ok(result)) {
        c_println("{}", result.value);
    }

    Result err = divide(10, 0);
    /// This code will be ran because we have an Err value now
    if (is_err(err)) {
        /// This will print the err-msg to stderr
        println_err_result(err);
    }
}