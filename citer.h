//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CITER_H
#define CITER_H

#include "creadonly.h"
#include "a_cvector.h"

#ifndef VECTOR_POOL_DEFAULT_SIZE
#define VECTOR_POOL_DEFAULT_SIZE 12
#endif

/// Initializes and returns a new VectorPool with default size.
VectorPool *init_vector_pool();

/// Frees all memory associated with the given VectorPool.
void free_vector_pool(VectorPool *vector_pool);

/// Allocates and returns a new vector (CVector) from the given pool.
CVector make_vector_context(VectorPool *vector_pool);

/// Frees a CVector context previously created via make_vector_context.
void free_vector_context(CVector context);

/// Gets the item at a given index in the vector.
Result get_item_at_index(CVector context, size_t index);

/// Sets the item at a given index in the vector.
Result set_item_at_index(CVector context, size_t index, c_fmt_FormatArg value);

/// Appends an item to the end of the vector.
Result append_item(CVector context, c_fmt_FormatArg value);

/// Removes the item at the specified index.
Result remove_item_at_index(CVector context, size_t index);

/// Removes the first occurrence of the given value.
Result remove_item(CVector context, c_fmt_FormatArg value);

/// Clears all items in the vector.
Result remove_all_items(CVector context);

/// Returns the number of items in the vector.
Result get_vector_size(CVector context);

/// Direction enum for iteration (forwards or backwards).
typedef enum : int8_t {
    ItForwards = 1,   ///< Iterate from front to back.
    ItBackwards = -1  ///< Iterate from back to front.
} Direction;

/// Iterator for traversing a CVector.
typedef struct {
    CVector context;     ///< The vector being iterated.
    ssize_t index;       ///< Current index position.
    Direction direction; ///< Current direction of iteration.
} VectorIterator;

/// Returns an iterator at the beginning (index 0) of the vector.
VectorIterator start_iterator(CVector context);

/// Returns an iterator one-past-the-end of the vector (index == size).
VectorIterator end_iterator(CVector context);

/// Returns a reverse iterator starting at the last element.
VectorIterator reverse_start_iterator(CVector context); // points to size - 1

/// Returns a reverse iterator one-before-the-start (index == -1).
VectorIterator reverse_end_iterator(CVector context);   // points to -1

/// Returns true if two iterators point to the same location.
bool iterator_equal(VectorIterator a, VectorIterator b);

/// Returns true if the iterator has reached the end of the sequence.
bool iterator_at_end(VectorIterator iterator);

/// Returns true if the iterator has reached the start (beginning for forward, end for reverse).
bool iterator_at_start(VectorIterator iterator);

/// Returns the value at the current iterator position.
Result get_iterator_value(VectorIterator iterator);

/// Moves the iterator to the next element in its direction.
Result iterator_next(VectorIterator *iterator);

/// Moves the iterator to the previous element in its direction.
Result iterator_prev(VectorIterator *iterator);

/// Macro for forward iteration over a vector.
/// Usage:
/// ```c
/// foreach(it, vec) {
///     Result r = get_iterator_value(it);
///     ...
/// }
/// ```
#define foreach(it_name, vec) \
    for (VectorIterator it_name = start_iterator(vec); !iterator_at_end(it_name); iterator_next(&it_name))

/// Macro for reverse iteration over a vector.
/// Usage:
/// ```c
/// foreach_reverse(it, vec) {
///     Result r = get_iterator_value(it);
///     ...
/// }
/// ```
#define foreach_reverse(it_name, vec) \
    for (VectorIterator it_name = reverse_start_iterator(vec); !iterator_at_end(it_name); iterator_next(&it_name))

#endif //CITER_H
