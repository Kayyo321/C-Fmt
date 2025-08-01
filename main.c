#include "coptional.h"

int main(void) {
    Optional x = opt_none; //opt_some(ADouble(10.0));
    with_some(x, a_double,
        c_println("{}", a_double);
    )

    return EXIT_SUCCESS;
}