//
// Created by Sully on 7/10/25.
//

#ifndef CFMT_H
#define CFMT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "a_string.h"
#include "a_cvector.h"

#ifndef CFMT_DEFAULT_MAX_WRITTEN_BYTES
#define CFMT_DEFAULT_MAX_WRITTEN_BYTES 1024
#endif

typedef enum {
    Vec = 'j',
    Str = 'n',
    CStr = 's',
    Bool = 'b',
    Int = 'i',
    Float = 'f',
    Char = 'c',
    Double = 'd',
    UInt = 'u',
    Short = 'h',
    UShort = 't',
    Long = 'l',
    LongLong = 'v',
    ULongLong = 'm',
    ULong = 'x',
    Ptr = 'p',
    Unique = 'z',
} c_fmt_VariadicType;

/// Represents a tagged union of supported format argument values.
typedef union {
    CVector vec_val;
    String *string_val;
    char ch_val;
    const char* str_val;
    bool bool_val;
    int int_val;
    unsigned int u_int_val;
    short short_val;
    unsigned short u_short_val;
    float float_val;
    double double_val;
    long long_val;
    long long long_long_val;
    unsigned long u_long_val;
    unsigned long long u_long_long_val;
    void *ptr_val;
} c_fmt_Any;

/// Global config for how many max bytes can be written into a format buffer.
extern unsigned long c_fmt_MaxBytesWritten;

/// Represents a single argument to a format call, including its type and optional custom tag (used for Unique).
typedef struct {
    c_fmt_VariadicType type;
    c_fmt_Any value;
    const char *opt_tag;
} c_fmt_FormatArg;

/// Returns true if two c_fmt_Any values are equal (used for testing or comparisons).
bool any_equal(const c_fmt_Any a, const c_fmt_Any b);

/// takes a format string and replaces all placeholders with it's variadic counterpart
/// returns a char* to a heap object that needs to be freed when done with
char *c_fmt_Format(const char *fmt, const c_fmt_FormatArg *fmt_args, int arg_count);

/// writes formatted string into an existing buffer (no heap allocation).
/// ensures null-termination and respects dest_size.
void c_fmt_FormatInto(char *dest, size_t dest_size, const char *fmt, const c_fmt_FormatArg *fmt_args, int arg_count);

/// prints out a new-line character to stdout
void c_newline();

/// helper wrapper for strcmp
bool cstrings_equal(const char *a, const char *b);

#define AVec(v)    (c_fmt_FormatArg){ Vec,    .value.vec_val = v }
#define AStr(s)    (c_fmt_FormatArg){ Str,    .value.string_val = s }
#define AChar(c)   (c_fmt_FormatArg){ Char,   .value.ch_val = (c) }
#define ACStr(s)    (c_fmt_FormatArg){ CStr,    .value.str_val = (s) }
#define ABool(b)   (c_fmt_FormatArg){ Bool,   .value.bool_val = (b) }
#define AInt(i)    (c_fmt_FormatArg){ Int,    .value.int_val = (i) }
#define AUInt(u)   (c_fmt_FormatArg){ UInt,   .value.u_int_val = (u) }
#define AShort(s)  (c_fmt_FormatArg){ Short,  .value.short_val = (s) }
#define AUShort(us) (c_fmt_FormatArg){ UShort, .value.u_short_val = (us) }
#define AFloat(f)  (c_fmt_FormatArg){ Float,  .value.float_val = (f) }
#define ADouble(d) (c_fmt_FormatArg){ Double, .value.double_val = (d) }
#define ALong(l)   (c_fmt_FormatArg){ Long,   .value.long_val = (l) }
#define ALongLong(ll) (c_fmt_FormatArg){ LongLong,   .value.long_long_val = (ll) }
#define AULong(ul) (c_fmt_FormatArg){ ULongLong,  .value.u_long_val = (ul) }
#define AULongLong(ull) (c_fmt_FormatArg){ ULong,  .value.u_long_long_val = (ull) }
#define APtr(p)    (c_fmt_FormatArg){ Ptr,    .value.ptr_val = (p) }
#define AUnique(u, tag) (c_fmt_FormatArg){ Unique, .value.ptr_val = (u), .opt_tag = (tag) }

#define c_format(format, ...) \
    c_fmt_Format(format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg))

#define c_print(format, ...) \
do { \
char _buffer[c_fmt_MaxBytesWritten]; \
c_fmt_FormatInto(_buffer, sizeof(_buffer), format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg)); \
fputs(_buffer, stdout); \
} while (0)

#define c_println(format, ...) \
do { \
char _buffer[c_fmt_MaxBytesWritten]; \
c_fmt_FormatInto(_buffer, sizeof(_buffer), format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg)); \
puts(_buffer); \
} while (0)

#define c_print_stderr(format, ...) \
do { \
char _buffer[c_fmt_MaxBytesWritten]; \
c_fmt_FormatInto(_buffer, sizeof(_buffer), format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg)); \
fputs(_buffer, stderr); \
} while (0)

#define c_panic(format, ...) \
do { \
char _buffer[c_fmt_MaxBytesWritten]; \
c_fmt_FormatInto(_buffer, sizeof(_buffer), format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg)); \
fputs(_buffer, stderr); \
exit(EXIT_FAILURE); \
} while (0)

#define c_print_into(buffer, buffer_size, format, ...) \
c_fmt_FormatInto(buffer, buffer_size, format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg))

#define c_format_into(buffer, buffer_size, format, ...) \
c_fmt_FormatInto(buffer, buffer_size, format, (c_fmt_FormatArg[]){ __VA_ARGS__ }, sizeof((c_fmt_FormatArg[]){ __VA_ARGS__ }) / sizeof(c_fmt_FormatArg))

#endif //CFMT_H
