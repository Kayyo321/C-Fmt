//
// Created by Jessica Bruce on 8/1/25.
//

#include "../citer.h"

void iterate_forwards_and_backwards(CVector vec) {
    /// Simple forwards
    VectorIterator it = start_iterator(vec);

    while (!iterator_at_end(it)) {
        c_println("{}", get_iterator_value(it).value);

        iterator_next(&it);
    }

    /// Simple backwards
    VectorIterator r_it = reverse_start_iterator(vec);

    /// note that now 'end' technically refers to the beginning of the vector
    /// since we're going in reverse
    while (!iterator_at_end(r_it)) {
        c_println("{}", get_iterator_value(r_it).value);

        /// note that next will be going in reverse
        iterator_next(&r_it);
    }
}

void use_cool_macros(CVector vec) {
    /// Go forwards using the same technique, just squished in a macro
    foreach(element, vec) {
        c_println("{}", get_iterator_value(element).value);
    }

    /// Same for reverse
    foreach_reverse(element, vec) {
        c_println("{}", get_iterator_value(element).value);
    }
}

void use_iterators() {
    VectorPool *pool = init_vector_pool();

    CVector a_vector = make_vector_context(pool);
    for (int i = 0; i < 10; i++)
        append_item(a_vector, AInt(i * i));

    iterate_forwards_and_backwards(a_vector);

    use_cool_macros(a_vector);

    free_vector_pool(pool);
}