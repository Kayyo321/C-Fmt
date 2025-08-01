//
// Created by Jessica Bruce on 8/1/25.
//

#include "cstring.h"

#include <ctype.h>

const String null_string = {.data = NULL, .length = 0, .capacity = 0};

String string_new(const char *c_str) {
    const size_t len = strlen(c_str);

    const String s = {.data = malloc(len + 1), .length = len, .capacity = len + 1};
    if (!s.data)
        c_panic("String allocation failed");

    memcpy(s.data, c_str, len + 1);

    return s;
}

String string_from(const String *s) {
    const size_t len = s->length;

    const String s1 = {.data = malloc(len + 1), .length = len, .capacity = len + 1};
    if (!s1.data)
        c_panic("String allocation failed");

    memcpy(s1.data, s->data, len+1);

    return s1;
}

String string_with_capacity(const size_t cap) {
    const String s = {.data = malloc(cap), .length = 0, .capacity = cap};
    if (!s.data)
        c_panic("String allocation failed");

    return s;
}

void string_free(String *s) {
    free(s->data);

    *s = null_string;
}

bool string_equals(const String *a, const String *b) {
    return a->length == b->length && memcmp(a->data, b->data, a->length) == 0;
}

bool string_equals_c_str(const String *a, const char *b) {
    return a->length == strlen(b) && memcmp(a->data, b, a->length) == 0;
}

int string_find(const String *s, const char *substr) {
    if (!s || !s->data || !substr) return -1;

    const char* found = strstr(s->data, substr);
    if (!found) return -1;

    return (int)(found - s->data);
}

bool string_starts_with(const String *s, const char *prefix) {
    if (!s || !s->data || !prefix) return false;

    const size_t prefix_len = strlen(prefix);
    if (prefix_len > s->length) return false;

    return strncmp(s->data, prefix, prefix_len) == 0;
}

bool string_ends_with(const String *s, const char *suffix) {
    if (!s || !s->data || !suffix) return false;

    const size_t suffix_len = strlen(suffix);
    if (suffix_len > s->length) return false;

    return strncmp(s->data + s->length - suffix_len, suffix, suffix_len) == 0;
}

String string_substring(const String *s, size_t start, size_t length) {
    String result = {0};

    if (!s || !s->data || start >= s->length)
        return string_new(""); // return empty string

    const size_t max_len = s->length - start;
    if (length > max_len) length = max_len;

    result.data = malloc(length + 1);
    if (!result.data) return result;

    memcpy(result.data, s->data + start, length);
    result.data[length] = '\0';
    result.length = length;
    result.capacity = length + 1;

    return result;
}

String string_slice(const String *s, ssize_t start, ssize_t end) {
    String result = {0};

    if (!s || !s->data) return string_new("");

    ssize_t len = (ssize_t)s->length;

    // Normalize negative indices
    if (start < 0) start += len;
    if (end < 0) end += len;

    // Clamp to valid range
    if (start < 0) start = 0;
    if (end > len) end = len;

    // If invalid range or empty slice
    if (start >= end) return string_new("");

    size_t slice_len = end - start;
    result.data = malloc(slice_len + 1);
    if (!result.data) return result;

    memcpy(result.data, s->data + start, slice_len);
    result.data[slice_len] = '\0';
    result.length = slice_len;
    result.capacity = slice_len + 1;

    return result;
}

Result string_append(String *s, const String *s1) {
    if (!s || !s1) return err_result("Null input to string_append");

    const size_t new_len = s->length + s1->length;
    char* new_data = malloc(new_len + 1);
    if (!new_data) return err_result("Memory allocation failed");

    memcpy(new_data, s->data, s->length);
    memcpy(new_data + s->length, s1->data, s1->length);
    new_data[new_len] = '\0';

    s->data = new_data;
    s->length = new_len;
    s->capacity = new_len + 1;

    return ok_result(ACStr("Appended the string"));
}

Result string_append_c_str(String *s, const char *c_str) {
    if (!s || !c_str) return err_result("Null input to string_append_c_str");

    const size_t c_str_len = strlen(c_str);
    const size_t new_len = s->length + c_str_len;
    char* new_data = malloc(new_len + 1);
    if (!new_data) return err_result("Memory allocation failed");

    memcpy(new_data, s->data, s->length);
    memcpy(new_data + s->length, c_str, c_str_len);
    new_data[new_len] = '\0';

    s->data = new_data;
    s->length = new_len;
    s->capacity = new_len + 1;

    return ok_result(ACStr("Appended the string"));
}

Result string_pop_back(String *s) {
    if (!s || !s->data || s->length == 0)
        return err_result("Cannot pop from empty string");

    s->data[--s->length] = '\0';
    return ok_result(ACStr("Popped back character"));
}

Result string_pop_front(String *s) {
    if (!s || !s->data || s->length == 0)
        return err_result("Cannot pop from empty string");

    memmove(s->data, s->data + 1, s->length);
    s->data[--s->length] = '\0';
    return ok_result(ACStr("Popped front character"));
}


Result string_pop_at(String *s, const size_t index) {
    if (!s || !s->data)
        return err_result("Null string");

    if (index >= s->length)
        return err_result("Index out of range");

    memmove(s->data + index, s->data + index + 1, s->length - index);
    s->length--;
    s->data[s->length] = '\0';
    return ok_result(ACStr("Popped character at index"));
}

String string_repeat(const char *c_str, const size_t times) {
    if (!c_str || times == 0)
        return string_new("");

    const size_t len = strlen(c_str);
    const size_t total = len * times;

    char data[total+1];

    for (size_t i = 0; i < times; i++)
        memcpy(data + i * len, c_str, len);

    data[total] = '\0';

    return string_new(data);
}

String string_trim(const String *s) {
    if (!s || !s->data || s->length == 0)
        return string_new("");

    size_t start = 0, end = s->length;

    while (start < end && isspace((unsigned char)s->data[start])) start++;
    while (end > start && isspace((unsigned char)s->data[end - 1])) end--;

    return string_substring(s, start, end - start);
}

String string_to_upper(const String *s) {
    if (!s || !s->data)
        return string_new("");

    String result = string_with_capacity(s->length + 1);

    for (size_t i = 0; i < s->length; i++)
        result.data[i] = (char)toupper((unsigned char)s->data[i]);

    result.data[s->length] = '\0';
    result.length = s->length;
    return result;
}

String string_to_lower(const String *s) {
    if (!s || !s->data)
        return string_new("");

    String result = string_with_capacity(s->length + 1);

    for (size_t i = 0; i < s->length; i++)
        result.data[i] = (char)tolower((unsigned char)s->data[i]);

    result.data[s->length] = '\0';
    result.length = s->length;
    return result;
}