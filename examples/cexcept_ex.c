//
// Created by Jessica Bruce on 8/1/25.
//

#include "../cexcept.h"

double safe_divide(double x, double y) {
    if (y == 0) {
        Throw(ACStr("Division by zero"));
    }

    return x / y;
}

void use_exceptions() {
    double x = 10.0, y = 0.0, result = 0.0;

    Try {
        result = safe_divide(x, y);
        c_println("Result: {}", ADouble(result));
    } Catch (ex) {
        c_print_stderr("Caught exception: {}\n", ex);
    } Finally {
        printf("Cleanup or final steps here.\n");
    } Finish;
}