//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CREADONLY_H
#define CREADONLY_H

#include "cresult.h"

/// Default number of readonly slots in the pool (can be overridden before inclusion).
#ifndef READONLY_POOL_DEFAULT_SIZE
#define READONLY_POOL_DEFAULT_SIZE 64
#endif

/// A handle to an immutable, write-once value stored in the readonly pool.
typedef size_t Readonly;

/// Initializes the global readonly pool with a default capacity.
/// Must be called before using any `Readonly` values.
void init_readonly_pool();

/// Frees all memory associated with the readonly pool.
/// After calling this, all `Readonly` handles become invalid.
void free_readonly_pool();

/// Compares two Readonly handles for equality (identity-based).
/// @return true if both handles refer to the same slot.
bool readonly_equal(Readonly a, Readonly b);

/// Creates a new readonly handle containing the given value.
/// @return A `Readonly` handle to the immutable value.
Readonly make_readonly(c_fmt_FormatArg a_value);

/// Creates an empty readonly handle that can later be initialized with a value using `set_readonly()`.
/// @return A `Readonly` handle in an unset state.
Readonly make_empty_readonly();

/// Sets the value of a previously empty `Readonly` handle.
/// Fails if the handle is already set or invalid.
/// @return `ResultOk` if successful, or an error otherwise.
Result set_readonly(Readonly a_readonly, c_fmt_FormatArg a_value);

/// Retrieves the value stored in the `Readonly` handle.
/// Fails if the handle is invalid or uninitialized.
/// @return A `Result` containing the value, or an error.
Result get_readonly(Readonly a_readonly);

#endif // CREADONLY_H