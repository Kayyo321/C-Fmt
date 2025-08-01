//
// Created by Jessica Bruce on 8/1/25.
//

#include "../cfmt.h"
#include "../cstring.h"

/// custom type for AUnique example
typedef struct {
    int id;
    const char *name;
} Person;

/// example
void use_format_funcs() {
    String greeting = string_new("World");
    Person jessica = {42, "Jessica Bruce"};

    // format into heap string
    char *formatted = c_format("Hello, {}, pi: {}, cool? {}, raw: {}\n",
        AStr(&greeting),
        AFloat(3.1415f),
        ABool(true),
        ACStr("inline string")
    );
    fputs(formatted, stdout);
    free(formatted); // must free manually

    // print directly using c_print
    c_println("Int: {}, UInt: {}, Long: {}, Double: {}, Char: '{}'",
        AInt(-123),
        AUInt(456),
        ALong(1000000L),
        ADouble(2.71828),
        AChar('!')
    );

    // custom tagged (AUnique) value printing
    c_println("Meet our guest: {}", AUnique(&jessica, "Person"));

    // format into the existing buffer
    char buffer[256];
    c_format_into(buffer, sizeof(buffer), "Short: {}, UShort: {}",
        AShort((short)-5),
        AUShort((unsigned short)10),
    );
    puts(buffer);

    string_free(&greeting);
}
