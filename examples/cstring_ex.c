//
// Created by Jessica Bruce on 8/1/25.
//

#include "../cstring.h"

/// A GlobalString is a representation of a comp-time string like "Hello, World"
/// This macro makes a global variable, in this case MyEnum, which has the value: "MyEnum"
global_string_enum(MyEnum)
global_string_enum(AnotherEnum)

/// ^^^ These will be useful when tagging unique's, as you can pattern match them
/// with enum-like syntax using the global string enum

void use_strings() {
    String a_string = string_new("Hello, World!");

    c_println("{}", AStr(&a_string));

    string_free(&a_string);

    String another_string = string_new("Hello, World!");
    string_append(&another_string, "!");
    c_println("{}", AStr(&another_string));

    if (string_starts_with(&another_string, "Hello")) {
        c_println("Hi!");
    }

    string_free(&another_string);
}