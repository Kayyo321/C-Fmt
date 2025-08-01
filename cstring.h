//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef CSTRING_H
#define CSTRING_H

#include "cresult.h"

#include "a_string.h"

typedef typedef const char * GlobalString;

#define global_string_enum(enum_name) \
    const GlobalString enum_name = #enum_name;

extern const String null_string;

String string_new(const char *c_str);
String string_from(const String *s);
String string_with_capacity(size_t cap);
void string_free(String *s);

bool string_equals(const String *a, const String *b);
bool string_equals_c_str(const String *a, const char *b);

int string_find(const String *s, const char* substr);
bool string_starts_with(const String *s, const char *prefix);
bool string_ends_with(const String *s, const char *suffix);

String string_substring(const String *s, size_t start, size_t length);
String string_slice(const String *s, ssize_t start, ssize_t end);

Result string_append(String *s, const String *s1);
Result string_append_c_str(String *s, const char *c_str);

Result string_pop_back(String *s);
Result string_pop_front(String *s);
Result string_pop_at(String *s, size_t index);

String string_repeat(const char *c_str, size_t times);
String string_trim(const String *s);
String string_to_upper(const String *s);
String string_to_lower(const String *s);

#endif //CSTRING_H
