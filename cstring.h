//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef CSTRING_H
#define CSTRING_H

#include "cresult.h"
#include "a_string.h"

/// GlobalString is a constant C string used primarily as a lightweight tag or identifier.
typedef const char * GlobalString;

/// Macro for declaring a global string constant based on the enum name.
/// Example:
/// ```c
/// global_string_enum(MyTag) // expands to: const GlobalString MyTag = "MyTag";
/// ```
#define global_string_enum(enum_name) \
    const GlobalString enum_name = #enum_name;

/// A shared constant empty/null string.
extern const String null_string;

/// Creates a new heap-allocated String from a C-style string.
/// @param c_str A null-terminated C string.
/// @return A new `String` object.
String string_new(const char *c_str);

/// Copies an existing `String`.
/// @param s Pointer to the source `String`.
/// @return A new `String` object with the same contents.
String string_from(const String *s);

/// Creates a new `String` with allocated capacity but empty content.
/// @param cap The number of characters to allocate.
/// @return A `String` object with reserved capacity.
String string_with_capacity(size_t cap);

/// Frees the internal buffer of the `String`.
/// @param s Pointer to the `String` to free.
void string_free(String *s);

/// Compares two `String` objects for equality.
/// @param a First string.
/// @param b Second string.
/// @return true if equal, false otherwise.
bool string_equals(const String *a, const String *b);

/// Compares a `String` with a C string for equality.
/// @param a A `String`.
/// @param b A null-terminated C string.
/// @return true if equal, false otherwise.
bool string_equals_c_str(const String *a, const char *b);

/// Finds the index of a substring in the given string.
/// @param s The string to search.
/// @param substr The C-string substring to search for.
/// @return Index of first match or -1 if not found.
int string_find(const String *s, const char* substr);

/// Checks if the string starts with a specific prefix.
/// @param s The target string.
/// @param prefix The prefix as a C-string.
/// @return true if it starts with prefix, false otherwise.
bool string_starts_with(const String *s, const char *prefix);

/// Checks if the string ends with a specific suffix.
/// @param s The target string.
/// @param suffix The suffix as a C-string.
/// @return true if it ends with suffix, false otherwise.
bool string_ends_with(const String *s, const char *suffix);

/// Extracts a substring starting at `start` for `length` characters.
/// @param s The source string.
/// @param start The start index (0-based).
/// @param length Number of characters to extract.
/// @return A new `String` containing the substring.
String string_substring(const String *s, size_t start, size_t length);

/// Returns a slice of the string from `start` to `end`.
/// Supports negative indices relative to the end.
/// @param s The source string.
/// @param start Start index (can be negative).
/// @param end End index (exclusive, can be negative).
/// @return A new `String` representing the slice.
String string_slice(const String *s, ssize_t start, ssize_t end);

/// Appends another string to the target string.
/// @param s The string to append to.
/// @param s1 The string to append.
/// @return Result indicating success or failure.
Result string_append(String *s, const String *s1);

/// Appends a C string to the target string.
/// @param s The string to append to.
/// @param c_str The C-string to append.
/// @return Result indicating success or failure.
Result string_append_c_str(String *s, const char *c_str);

/// Removes the last character of the string.
/// @param s The string to modify.
/// @return Result with removed character or error.
Result string_pop_back(String *s);

/// Removes the first character of the string.
/// @param s The string to modify.
/// @return Result with removed character or error.
Result string_pop_front(String *s);

/// Removes a character at a specific index.
/// @param s The string to modify.
/// @param index The index of the character to remove.
/// @return Result with removed character or error.
Result string_pop_at(String *s, size_t index);

/// Repeats a C string multiple times to create a new string.
/// @param c_str The base string.
/// @param times Number of repetitions.
/// @return A new `String` with repeated contents.
String string_repeat(const char *c_str, size_t times);

/// Removes leading and trailing whitespace from the string.
/// @param s The string to trim.
/// @return A new `String` without leading/trailing whitespace.
String string_trim(const String *s);

/// Converts the string to uppercase.
/// @param s The input string.
/// @return A new `String` with all characters uppercased.
String string_to_upper(const String *s);

/// Converts the string to lowercase.
/// @param s The input string.
/// @return A new `String` with all characters lowercased.
String string_to_lower(const String *s);

#endif // CSTRING_H
