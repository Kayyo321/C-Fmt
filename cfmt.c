//
// Created by Sully on 7/10/25.
//

#include "cfmt.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cstring.h"
#include "citer.h"

unsigned long c_fmt_MaxBytesWritten = CFMT_DEFAULT_MAX_WRITTEN_BYTES;

bool any_equal(const c_fmt_Any a, const c_fmt_Any b) {
    return a.str_val == b.str_val &&
        a.bool_val == b.bool_val &&
        a.int_val == b.int_val &&
        a.u_int_val == b.u_int_val &&
        a.float_val == b.float_val &&
        a.double_val == b.double_val &&
        a.long_val == b.long_val &&
        a.u_long_val == b.u_long_val &&
        a.ptr_val == b.ptr_val;
}

// Central formatting helper
static void c_fmt_FormatArgToString(char *dest, size_t max_len, const c_fmt_FormatArg *arg) {
    switch (arg->type) {
        case Str:
            snprintf(dest, max_len, "%s", arg->value.string_val->data);
            break;
        case CStr:
            snprintf(dest, max_len, "%s", arg->value.str_val);
            break;
        case Bool:
            snprintf(dest, max_len, "%s", arg->value.bool_val ? "true" : "false");
            break;
        case Int:
            snprintf(dest, max_len, "%d", arg->value.int_val);
            break;
        case UInt:
            snprintf(dest, max_len, "%u", arg->value.u_int_val);
            break;
        case Float:
            snprintf(dest, max_len, "%f", arg->value.float_val);
            break;
        case Double:
            snprintf(dest, max_len, "%lf", arg->value.double_val);
            break;
        case Long:
            snprintf(dest, max_len, "%ld", arg->value.long_val);
            break;
        case ULong:
            snprintf(dest, max_len, "%lu", arg->value.u_long_val);
            break;
        case Char:
            snprintf(dest, max_len, "%c", arg->value.ch_val);
            break;
        case Short:
            snprintf(dest, max_len, "%hd", arg->value.short_val);
            break;
        case UShort:
            snprintf(dest, max_len, "%hu", arg->value.u_short_val);
            break;
        case LongLong:
            snprintf(dest, max_len, "%lld", arg->value.long_long_val);
            break;
        case ULongLong:
            snprintf(dest, max_len, "%llu", arg->value.u_long_long_val);
            break;
        case Ptr:
            snprintf(dest, max_len, "%p", arg->value.ptr_val);
            break;
        case Unique:
            snprintf(dest, max_len, "{'%s': <%p>}", arg->opt_tag, arg->value.ptr_val);
            break;
        case Vec: {
            size_t written = 0;

            written += snprintf(dest + written, max_len - written, "[");
            CVector vec = arg->value.vec_val;

            size_t i = 0;
            foreach(element, vec) {
                if (i > 0 && written < max_len - 1) {
                    written += snprintf(dest + written, max_len - written, ", ");
                }

                char item_buf[128] = {0};

                if (written < max_len - 1) {
                    const Result item = get_iterator_value(element);
                    if (is_err(item)) {
                        c_panic("Couldn't fetch item from iterator");
                    }

                    const c_fmt_FormatArg *item_arg = &item.value;

                    c_fmt_FormatArgToString(item_buf, sizeof(item_buf), item_arg);
                    written += snprintf(dest + written, max_len - written, "%s", item_buf);
                }

                ++i;
            }
            snprintf(dest + written, max_len - written, "]");
            break;
        }
        default:
            snprintf(dest, max_len, "<unknown>");
            break;
    }
}

char *c_fmt_Format(const char *fmt, const c_fmt_FormatArg *fmt_args, int arg_count) {
    char buffer[c_fmt_MaxBytesWritten];
    size_t buf_pos = 0;

    const char *p = fmt;
    size_t arg_index = 0;

    buffer[0] = '\0';

    while (*p && buf_pos < c_fmt_MaxBytesWritten - 1) {
        if (*p == '{' && *(p + 1) == '}') {
            if (arg_index >= arg_count) break;

            char temp[256] = {0};
            c_fmt_FormatArgToString(temp, sizeof(temp), &fmt_args[arg_index]);
            strncat(buffer, temp, c_fmt_MaxBytesWritten - strlen(buffer) - 1);
            buf_pos = strlen(buffer);
            p += 2;
            arg_index++;
        } else {
            buffer[buf_pos++] = *p++;
            buffer[buf_pos] = '\0';
        }
    }

    char *result = calloc(strlen(buffer) + 1, sizeof(char));
    if (result) strcpy(result, buffer);
    return result;
}

void c_fmt_FormatInto(char *dest, const size_t dest_size, const char *fmt, const c_fmt_FormatArg *fmt_args, int arg_count) {
    if (!dest || dest_size == 0) return;

    size_t buf_pos = 0;
    dest[0] = '\0';

    const char *p = fmt;
    size_t arg_index = 0;

    while (*p && buf_pos < dest_size - 1) {
        if (*p == '{' && *(p + 1) == '}') {
            if (arg_index >= arg_count) break;

            char temp[256] = {0};
            c_fmt_FormatArgToString(temp, sizeof(temp), &fmt_args[arg_index]);
            strncat(dest, temp, dest_size - strlen(dest) - 1);
            buf_pos = strlen(dest);
            p += 2;
            arg_index++;
        } else {
            dest[buf_pos++] = *p++;
            dest[buf_pos] = '\0';
        }
    }

    dest[dest_size - 1] = '\0';
}

void c_newline() {
    putchar('\n');
}

bool cstrings_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}