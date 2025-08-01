//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef A_CVECTOR_H
#define A_CVECTOR_H

#include <stdio.h>

struct _VectorPool;
typedef struct _VectorPool VectorPool;

typedef struct _CVector {
    size_t index;
    VectorPool *vector_pool;
} CVector;

#endif //A_CVECTOR_H
