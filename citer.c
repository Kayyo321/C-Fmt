#include "citer.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    c_fmt_FormatArg *block;
    size_t size;
    size_t capacity;
} AVector;

struct _VectorPool {
    AVector **pool;
    size_t vector_pool_size;
};

VectorPool *init_vector_pool() {
    VectorPool *vector_pool = malloc(sizeof(VectorPool));

    if (!vector_pool)
        c_panic("Vector pool allocation failed");

    vector_pool->vector_pool_size = VECTOR_POOL_DEFAULT_SIZE;
    vector_pool->pool = calloc(vector_pool->vector_pool_size, sizeof(AVector*));

    return vector_pool;
}

void free_vector_pool(VectorPool *vector_pool) {
    if (!vector_pool)
        return;

    for (size_t i = 0; i < vector_pool->vector_pool_size; ++i) {
        if (vector_pool->pool[i]) {
            free(vector_pool->pool[i]->block);
            free(vector_pool->pool[i]);
        }
    }

    free(vector_pool->pool);
    free(vector_pool);
}

static long find_first_unused_or_negative(const VectorPool *vector_pool) {
    for (size_t i = 0; i < vector_pool->vector_pool_size; i++) {
        if (!vector_pool->pool[i]) {
            return (long)i;
        }
    }

    return -1;
}

long find_a_vector_spot_or_make_space(VectorPool *vector_pool) {
    if (!vector_pool)
        return -1;

    long spot = find_first_unused_or_negative(vector_pool);
    if (spot < 0) {
        vector_pool->vector_pool_size *= 2;
        AVector **tmp = realloc(vector_pool->pool, vector_pool->vector_pool_size * sizeof(AVector*));
        if (tmp)
            vector_pool->pool = tmp;
        else
            return -1;

        spot = find_first_unused_or_negative(vector_pool);
    }

    return spot;
}

CVector make_vector_context(VectorPool *vector_pool) {
    if (!vector_pool)
        c_panic("Vector pool not initialized");

    const long spot_i = find_a_vector_spot_or_make_space(vector_pool);
    if (spot_i < 0)
        c_panic("Vector spot not available");

    AVector *new_vector = malloc(sizeof(AVector));

    new_vector->size = 0;
    new_vector->capacity = 2;
    new_vector->block = calloc(new_vector->capacity, sizeof(c_fmt_FormatArg));

    vector_pool->pool[spot_i] = new_vector;

    return (CVector){ .index = (size_t)spot_i, .vector_pool = vector_pool };
}

void free_vector_context(const CVector context) {
    if (!context.vector_pool)
        return;

    if (context.index >= context.vector_pool->vector_pool_size)
        return;

    AVector *spot = context.vector_pool->pool[context.index];
    free(spot->block);
    free(spot);
    context.vector_pool->pool[context.index] = NULL;
}

Result get_item_at_index(const CVector context, const size_t index) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];
    if (index >= spot->size)
        return err_result("Index out of bounds");

    return ok_result(spot->block[index]);
}

Result set_item_at_index(const CVector context, const size_t index, const c_fmt_FormatArg value) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];
    if (index >= spot->size)
        return err_result("Index out of bounds");

    return ok_result(spot->block[index] = value);
}

c_fmt_FormatArg add_to_a_vector(AVector *a_vector, const c_fmt_FormatArg value) {
    if (a_vector->size >= a_vector->capacity) {
        a_vector->capacity *= 2;
        c_fmt_FormatArg *tmp = realloc(a_vector->block, a_vector->capacity * sizeof(c_fmt_FormatArg));
        if (tmp)
            a_vector->block = tmp;
        else
            c_panic("Vector block reallocation failed");
    }

    a_vector->block[a_vector->size++] = value;

    return value;
}

Result append_item(const CVector context, const c_fmt_FormatArg value) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];

    return ok_result(add_to_a_vector(spot, value));
}

Result remove_item_at_index(const CVector context, const size_t index) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];
    if (index >= spot->size)
        return err_result("Index out of bounds");

    for (size_t i = index; i < spot->size - 1; ++i) {
        spot->block[i] = spot->block[i + 1];
    }

    spot->size--;
    return ok_result(ACStr("Item removed"));
}

Result remove_item(const CVector context, const c_fmt_FormatArg value) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];
    if (!spot)
        return err_result("Vector not allocated");

    for (size_t i = 0; i < spot->size; ++i) {
        if (any_equal(spot->block[i].value, value.value) && spot->block[i].type == value.type) {
            return remove_item_at_index(context, i);
        }
    }

    return err_result("Item not found");
}

Result remove_all_items(const CVector context) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];
    if (!spot)
        return err_result("Vector not allocated");

    spot->size = 0;
    return ok_result(ACStr("All items removed"));
}

Result get_vector_size(const CVector context) {
    VectorPool *vector_pool = context.vector_pool;
    if (!vector_pool)
        return err_result("Vector pool not initialized");

    if (context.index >= vector_pool->vector_pool_size)
        return err_result("Vector out of bounds");

    AVector *spot = vector_pool->pool[context.index];
    if (!spot)
        return err_result("Vector not allocated");

    return ok_result(AInt((int)spot->size));
}

static size_t get_vector_size_unwrapped(CVector ctx) {
    if (!ctx.vector_pool || ctx.index >= ctx.vector_pool->vector_pool_size)
        return 0;

    const AVector *v = ctx.vector_pool->pool[ctx.index];
    return v ? v->size : 0;
}

// Create iterators
VectorIterator start_iterator(CVector context) {
    return (VectorIterator){ context, 0, ItForwards };
}

VectorIterator end_iterator(CVector context) {
    return (VectorIterator){ context, (ssize_t)get_vector_size_unwrapped(context), ItForwards };
}

VectorIterator reverse_start_iterator(CVector context) {
    return (VectorIterator){
        context,
        (ssize_t)get_vector_size_unwrapped(context) - 1,
        ItBackwards
    };
}

VectorIterator reverse_end_iterator(CVector context) {
    return (VectorIterator){ context, -1, ItBackwards };
}

// Iterator comparison
bool iterator_equal(VectorIterator a, VectorIterator b) {
    return a.index == b.index &&
           a.context.index == b.context.index &&
           a.context.vector_pool == b.context.vector_pool &&
           a.direction == b.direction;
}

// Detect ends
bool iterator_at_end(VectorIterator iterator) {
    if (iterator.direction == ItForwards)
        return iterator.index >= (ssize_t)get_vector_size_unwrapped(iterator.context);
    else
        return iterator.index < 0;
}

bool iterator_at_start(VectorIterator iterator) {
    if (iterator.direction == ItForwards)
        return iterator.index == 0;
    else
        return iterator.index == (ssize_t)(get_vector_size_unwrapped(iterator.context) - 1);
}

// Value access
Result get_iterator_value(const VectorIterator iterator) {
    return get_item_at_index(
        iterator.context,
        (size_t)iterator.index
    );
}

// Step forward/backward depending on the direction
Result iterator_next(VectorIterator *iterator) {
    if (!iterator || iterator_at_end(*iterator))
        return err_result("Iterator at end");

    iterator->index += iterator->direction;
    return ok_result(ACStr("Advanced"));
}

// Optional backward-only function
Result iterator_prev(VectorIterator *iterator) {
    if (!iterator || iterator_at_start(*iterator))
        return err_result("Iterator at start");

    iterator->index -= iterator->direction;
    return ok_result(ACStr("Rewound"));
}