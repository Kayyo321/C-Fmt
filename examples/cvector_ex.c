//
// Created by Jessica Bruce on 8/1/25.
//

#include "../citer.h"

void use_vectors() {
    /// Create the environment where our vectors will be generated
    VectorPool *pool = init_vector_pool();

    /// Get a handle to a new generated vector inside of the pool
    CVector my_vector = make_vector_context(pool);

    append_item(my_vector, AInt(1));
    append_item(my_vector, AInt(2));
    append_item(my_vector, ACStr("Hi!"));
    append_item(my_vector, ADouble(3.1415));

    /// format the vector to std out
    c_println("{}", AVec(my_vector));

    CVector my_other_vector = make_vector_context(pool);
    append_item(my_other_vector, AInt(10));

    /// Freed all memory related to my_vector,
    /// my_vector is no longer a valid handle
    free_vector_context(my_vector);

    /// my_other_vector is now freed because as we
    /// free the vector-pool, we go through all of the
    /// existing handles and free them too
    free_vector_pool(pool);
}