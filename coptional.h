//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef COPTIONAL_H
#define COPTIONAL_H

#include "cresult.h"

/// Represents the presence or absence of a value in an Optional.
typedef enum {
    HasValue,
    HasNoValue,
} OptionalState;

/// A value wrapper that may or may not contain a c_fmt_FormatArg.
typedef struct {
    OptionalState state;
    c_fmt_FormatArg value;
} Optional;

/// Constructs an Optional that contains the given value.
Optional opt_some(c_fmt_FormatArg value);

/// Returns true if the Optional contains a value.
bool opt_is_some(Optional opt);

/// Returns true if the Optional is empty.
bool opt_is_none(Optional opt);

/// Returns the value inside the Optional.
/// Returns an Err result if the Optional is empty.
Result opt_get_some(Optional opt);

/// A constant representing an empty Optional.
extern const Optional opt_none;

/// Executes a block only if the Optional contains a value.
/// The value is unwrapped and available as `val` within the block.
///
/// Usage:
/// ```c
/// with_some(opt, x, {
///     use(x); // x is of type c_fmt_FormatArg
/// });
/// ```
#define with_some(opt, val, ...) \
do { \
if (opt_is_some(opt)) { \
Result __##val = opt_get_some(opt); \
assert_ok(__##val); \
c_fmt_FormatArg val = __##val.value; \
__VA_ARGS__ \
} \
} while (0);

#endif // COPTIONAL_H
