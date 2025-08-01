//
// Created by Jessica Bruce on 8/1/25.
//

#include "../coptional.h"

Optional must_be_greater_than_zero(int n) {
    if (n <= 0) {
        /// Return a placeholder which symbolizes the optional having no value!
        return opt_none;
    }

    return opt_some(AInt(n));
}

/// showing off
void sum_cool_macros() {
    Optional x = must_be_greater_than_zero(100);

    /// This will run the block, because x has some value!
    with_some(x, the_val, {
        c_println("the value is: {}!", the_val);
    })

    /// This block will be skipped
    with_some(opt_none, the_val, {
        c_println("the value is: {}!", the_val);
    })
}

/// main example
void use_optionals() {
    Optional twenty = must_be_greater_than_zero(20);
    if (opt_is_some(twenty)) { // will be true
        /// This call will return `err` if optional is none
        Result result = opt_get_some(twenty);
        assert_ok(result);

        c_println("{}", result.value);
    }

    Optional zero = must_be_greater_than_zero(0);
    if (opt_is_some(zero)) { // will be false
        c_println("This will never be printed");
    } else if (opt_is_none(zero)) {
        c_println("This will be printed");
    }

    sum_cool_macros();
}