#include <string.h>

#include "cfmt.h"
#include "cstring.h"

typedef struct {
    char *lexeme;
    int len;
} Token;

global_string_enum(A_FLOAT)
global_string_enum(A_TOKEN)

FormatAny get_pi(float value) {
    float *x = malloc(sizeof(float));
    *x = value;

    return AUnique(x, A_FLOAT);
}

FormatAny get_a_token(char *lexeme) {
    Token *t = malloc(sizeof(Token));
    t->lexeme = lexeme;
    t->len = (int)strlen(lexeme);

    return AUnique(t, A_TOKEN);
}

void print_a_unique_float(const FormatAny xyz) {
    with_unique_tag(xyz, A_FLOAT, {
        const float *xyz_as_float_ptr = unique_as(xyz, float*);
        c_println("XYZ = {}", AFloat(*xyz_as_float_ptr));
    })
}

void print_a_unique_token(const FormatAny xyz) {
    with_unique_tag(xyz, A_TOKEN, {
        const Token *xyz_as_token_ptr = unique_as(xyz, Token*);
        c_println("Token('{}' [{}])", ACStr(xyz_as_token_ptr->lexeme), AInt(xyz_as_token_ptr->len));
    })
}

int main(void) {
    c_println("Hello, World!");

    FormatAny pi = get_pi(3.14f);
    FormatAny tok = get_a_token("a_token!");

    print_a_unique_float(pi);
    print_a_unique_token(tok);

    // should do nothing
    print_a_unique_float(tok);

    // should do nothing
    print_a_unique_token(pi);

    return EXIT_SUCCESS;
}