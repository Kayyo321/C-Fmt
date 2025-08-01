//
// Created by Jessica Bruce on 8/1/25.
//

#include "../creadonly.h"

void use_readonly() {
    /// Initialize the pool of which we will get readonly handlers
    /// This does not return a reference to a pool, the readonly pool
    /// is a global endevour
    init_readonly_pool();

    Readonly readonly_handler = make_readonly(ACStr("Hello, World!"));
    c_println("{}", get_readonly(readonly_handler).value);

    /// This will give us an err-result.
    /// That readonly has already been initialized!
    Result uh_oh = set_readonly(readonly_handler, ACStr("Uh oh!"));
    if (is_err(uh_oh)) {
        println_err_result(uh_oh);
    }

    /// This gives us a handle to an uninitialized readonly value
    /// This may only be initialized once
    Readonly final = make_empty_readonly();
    set_readonly(final, ACStr("Final!")); // This is the last time we can set the readonly

    c_println("{}", get_readonly(final).value);

    free_readonly_pool();
}