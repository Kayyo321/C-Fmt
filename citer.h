//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CITER_H
#define CITER_H

#include "creadonly.h"

#ifndef VECTOR_POOL_DEFAULT_SIZE
#define VECTOR_POOL_DEFAULT_SIZE 12
#endif

#include "a_cvector.h"

VectorPool *init_vector_pool();
void free_vector_pool(VectorPool *vector_pool);

CVector make_vector_context(VectorPool *vector_pool);
void free_vector_context(CVector context);

Result get_item_at_index(CVector context, size_t index);
Result set_item_at_index(CVector context, size_t index, c_fmt_FormatArg value);
Result append_item(CVector context, c_fmt_FormatArg value);
Result remove_item_at_index(CVector context, size_t index);
Result remove_item(CVector context, c_fmt_FormatArg value);
Result remove_all_items(CVector context);
Result get_vector_size(CVector context);

typedef enum : int8_t {
    ItForwards = 1,
    ItBackwards = -1
} Direction;

typedef struct {
    CVector context;
    ssize_t index;
    Direction direction; // 1 for forward, -1 for reverse
} VectorIterator;

VectorIterator start_iterator(CVector context);
VectorIterator end_iterator(CVector context);
VectorIterator reverse_start_iterator(CVector context); // points to size - 1
VectorIterator reverse_end_iterator(CVector context);   // points to -1

bool iterator_equal(VectorIterator a, VectorIterator b);
bool iterator_at_end(VectorIterator iterator);
bool iterator_at_start(VectorIterator iterator);

Result get_iterator_value(VectorIterator iterator);
Result iterator_next(VectorIterator *iterator);
Result iterator_prev(VectorIterator *iterator);

#define foreach(it_name, vec) \
    for (VectorIterator it_name = start_iterator(vec); !iterator_at_end(it_name); iterator_next(&it_name))

#define foreach_reverse(it_name, vec) \
    for (VectorIterator it_name = reverse_start_iterator(vec); !iterator_at_end(it_name); iterator_next(&it_name))

#endif //CITER_H
