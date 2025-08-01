//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef A_CVECTOR_H
#define A_CVECTOR_H

#include <stdio.h>

struct _VectorPool;
typedef struct _VectorPool VectorPool;

/**
 * @typedef CVector
 * @brief Represents a context for managing a vector in a shared vector pool.
 *
 * The `CVector` structure maintains a reference to a vector within a
 * specified vector pool. It is used to allocate, manage, and free
 * specific vector resources stored in a shared vector pool.
 *
 * @var index
 * Index of the vector within the vector pool.
 *
 * @var vector_pool
 * Pointer to the vector pool that manages all allocated vectors.
 */
typedef struct _CVector {
    size_t index;
    VectorPool *vector_pool;
} CVector;

#endif //A_CVECTOR_H
