# C-Fmt

A dynamic library that implements modern C++/Rust features in C. 

I would like to think of this project as a package of things that I've 
found the most interesting when researching ways to push the limits of
C. 

Almost all of the packages are built off of the `cfmt.h` core, given 
a handle for a tagged union representing the `any` type, (`c_fmt_FormatArg`),
and much more that is helpful (and needed) throughout the project.

Examples of each package can be found inside the `./examples/` directory.
Those will walk you through how to interact with the package as a whole.
I suggest starting with reading `cfmt_ex.c`, as it is the starting node that many
of the other examples rely heavily on.

If you want documentation for functions that aren't included in the examples,
(like the tons of really cool string manip. functions in cstring.h), comments are inside
of the header files to provide documentation.

Some basic examples that will sort-of teach you how this package works can be found below.

### Formatting

Formatting is all inside the `cfmt.h` library. well, how do we use it?

here are some examples:

```C
c_println("Hello, World!");
```

This prints 'Hello, World!', with a newline character.

```C
c_println("{} + {} = {}", AInt(1), AInt(4), AInt(1+4))
```

This prints out '1 + 4 = 5'. 
- Wrapping is necessary when formatting values.

### Vectors & Iterators

Vectors require an environment to be built in, like an arena structure, you have to define a `VectorPool` where you can make `CVector` (which stands for a vector-context).

```C
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

/// Freed all memory related to my_vector,
/// my_vector is no longer a valid handle
free_vector_context(my_vector);

free_vector_pool(pool);
```

You can use normal indexing through functions within the library,
But if you want to iterate through the vector, you can by using the `VectorIterator`

```C
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
```

## More...

Tons of more cool stuff is in here and plenty of other useful things like 
`Optional`, `Result`, and even `Readonly`. 

Please check out the `examples` for more info.