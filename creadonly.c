//
// Created by Jessica Bruce on 7/31/25.
//

#include "creadonly.h"

#include <stdlib.h>

typedef struct {
    c_fmt_FormatArg value;
    size_t tag;
    bool initialized;
} ReadonlyValue;

static ReadonlyValue *readonly_pool = NULL;

static size_t readonly_pool_size = READONLY_POOL_DEFAULT_SIZE;
static size_t readonly_pool_index = 0;

void init_readonly_pool() {
    if (readonly_pool)
        return;

    readonly_pool = calloc(readonly_pool_size, sizeof(Readonly));

    if (!readonly_pool)
        c_panic("Readonly pool allocation failed");
}

void free_readonly_pool() {
    if (!readonly_pool)
        return;

    free(readonly_pool);
    readonly_pool = NULL;
}

bool readonly_values_equ(const ReadonlyValue a, const ReadonlyValue b) {
    return a.value.type == b.value.type && any_equal(a.value.value, b.value.value) && a.tag == b.tag && a.initialized == b.initialized;
}

bool readonly_equal(const Readonly a, const Readonly b) {
    return a == b && readonly_values_equ(readonly_pool[a], readonly_pool[b]);
}

static ReadonlyValue *find_a_readonly_spot_or_make_space() {
    if (!readonly_pool)
        return NULL;

    if (readonly_pool_index >= readonly_pool_size) {
        readonly_pool_size *= 2;
        ReadonlyValue *tmp = realloc(readonly_pool, readonly_pool_size * sizeof(Readonly));

        if (tmp)
            readonly_pool = tmp;
        else
            return NULL;
    }

    return &readonly_pool[readonly_pool_index++];
}

Readonly make_readonly(const c_fmt_FormatArg a_value) {
    if (!readonly_pool)
        err_result("Readonly pool not initialized");

    const ReadonlyValue new_readonly = {
        .value = a_value,
        .tag = readonly_pool_index,
        .initialized = true
    };

    ReadonlyValue *spot = find_a_readonly_spot_or_make_space();
    if (spot) {
        *spot = new_readonly;
    } else {
        c_panic("Readonly spot not available");
    }

    return spot->tag;
}

Readonly make_empty_readonly() {
    if (!readonly_pool)
        err_result("Readonly pool not initialized");

    const ReadonlyValue new_readonly = {
        .value = { .type = Ptr, .value.ptr_val = NULL },
        .tag = readonly_pool_index,
        .initialized = false
    };

    ReadonlyValue *spot = find_a_readonly_spot_or_make_space();
    if (spot) {
        *spot = new_readonly;
    } else {
        c_panic("Readonly spot not available");
    }

    return spot->tag;
}

Result set_readonly(const Readonly a_readonly, const c_fmt_FormatArg a_value) {
    if (!readonly_pool)
        return err_result("Readonly pool not initialized");

    if (a_readonly >= readonly_pool_size)
        return err_result("Readonly out of bounds");

    ReadonlyValue *spot = &readonly_pool[a_readonly];
    if (spot->initialized)
        return err_result("Readonly is already initialized");

    spot->value = a_value;
    spot->initialized = true;

    return ok_result(a_value);
}

Result get_readonly(const Readonly a_readonly) {
    if (!readonly_pool)
        return err_result("Readonly pool not initialized");

    if (a_readonly >= readonly_pool_size)
        return err_result("Readonly out of bounds");

    const ReadonlyValue *spot = &readonly_pool[a_readonly];
    if (!spot->initialized)
        return err_result("Readonly is not initialized");

    return ok_result(spot->value);
}
