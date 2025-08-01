//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CRESULT_H
#define CRESULT_H

#include <stdbool.h>
#include <assert.h>
#include "cfmt.h"

/// Asserts that a Result is Ok.
#define assert_ok(result) assert(is_ok(result))

/// Asserts that a Result is Err.
#define assert_err(result) assert(is_err(result))

/// Asserts that two values are equal.
#define assert_eq(a, b) assert((a) == (b))

/// Asserts that two strings are equal.
#define assert_str_eq(a, b) assert(strcmp((a), (b)) == 0)

/// Enum representing success (Ok) or failure (Err) of a Result.
typedef enum {
    Ok = true,
    Err = false
} ResultTag;

/// Represents a tagged union result which can be either Ok (with a value) or Err (with an error message).
typedef struct {
    ResultTag tag;          ///< Ok or Err
    c_fmt_FormatArg value;  ///< Success value or error message
} Result;

/// Constructs a Result tagged as Ok with a value.
/// @param value The value to store in the Result.
/// @return A Result tagged Ok.
Result ok_result(c_fmt_FormatArg value);

/// Constructs a Result tagged as Err with a string error message.
/// @param err_msg The error message (copied into a c_fmt_FormatArg).
/// @return A Result tagged Err.
Result err_result(const char *err_msg);

/// Checks whether the Result is Ok.
/// @param result The result to inspect.
/// @return true if Ok, false otherwise.
bool is_ok(Result result);

/// Checks whether the Result is Err.
/// @param result The result to inspect.
/// @return true if Err, false otherwise.
bool is_err(Result result);

/// If the Result is an Err, prints the error message to stdout (or stderr depending on `c_fmt` config).
/// Safe to call regardless of whether the result is Ok or Err.
void println_err_result(Result result);

/// Interprets the Result’s value as a general `c_fmt_Any`.
/// This is mostly useful for formatting or inspection.
/// @param result The result whose value will be converted.
/// @return A `c_fmt_Any` view of the result’s value.
c_fmt_Any result_as(Result result);

#endif // CRESULT_H