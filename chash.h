//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CHASH_H
#define CHASH_H

#include <stdlib.h>
#include <string.h>

static inline unsigned hash_int(const int* x) {
    return (unsigned)(*x);
}

static inline int eq_int(const int* a, const int* b) {
    return *a == *b;
}

static inline unsigned hash_str(const char** s) {
    unsigned h = 5381;
    for (const char* p = *s; *p; p++) h = ((h << 5) + h) + *p;
    return h;
}

static inline int eq_str(const char** a, const char** b) {
    return strcmp(*a, *b) == 0;
}

#define declare_hashmap(MapTypeName, K, V) \
typedef struct MapTypeName##_entry { \
unsigned hash; \
K key; \
V value; \
struct MapTypeName##_entry* next; \
} MapTypeName##_entry; \
\
typedef struct { \
MapTypeName##_entry** buckets; \
size_t capacity; \
size_t size; \
} MapTypeName; \
\
void MapTypeName##_init(MapTypeName* map); \
void MapTypeName##_free(MapTypeName* map); \
int MapTypeName##_set(MapTypeName* map, K key, V value); \
int MapTypeName##_get(MapTypeName* map, K key, V* out); \
int MapTypeName##_has(MapTypeName* map, K key);

#define define_hashmap(MapTypeName, K, V, hash_fn, eq_fn) \
void MapTypeName##_init(MapTypeName* map) { \
    map->capacity = 16; \
    map->size = 0; \
    map->buckets = calloc(map->capacity, sizeof(*map->buckets)); \
} \
\
void MapTypeName##_free(MapTypeName* map) { \
    for (size_t i = 0; i < map->capacity; ++i) { \
        MapTypeName##_entry* e = map->buckets[i]; \
        while (e) { \
            MapTypeName##_entry* next = e->next; \
            free(e); \
            e = next; \
        } \
    } \
    free(map->buckets); \
    map->buckets = NULL; \
    map->capacity = 0; \
    map->size = 0; \
} \
\
static void MapTypeName##_resize(MapTypeName* map); \
\
int MapTypeName##_set(MapTypeName* map, K key, V value) { \
    if ((map->size * 3) / 2 > map->capacity) { \
        MapTypeName##_resize(map); \
    } \
    unsigned h = hash_fn(&key); \
    size_t idx = h % map->capacity; \
    MapTypeName##_entry* e = map->buckets[idx]; \
    while (e) { \
        if (e->hash == h && eq_fn(&e->key, &key)) { \
            e->value = value; \
            return 0; /* updated */ \
        } \
        e = e->next; \
    } \
    e = malloc(sizeof(*e)); \
    e->hash = h; \
    e->key = key; \
    e->value = value; \
    e->next = map->buckets[idx]; \
    map->buckets[idx] = e; \
    map->size++; \
    return 1; /* inserted */ \
} \
\
int MapTypeName##_get(MapTypeName* map, K key, V* out) { \
    unsigned h = hash_fn(&key); \
    size_t idx = h % map->capacity; \
    MapTypeName##_entry* e = map->buckets[idx]; \
    while (e) { \
        if (e->hash == h && eq_fn(&e->key, &key)) { \
            *out = e->value; \
            return 1; \
        } \
        e = e->next; \
    } \
    return 0; \
} \
\
int MapTypeName##_has(MapTypeName* map, K key) { \
    unsigned h = hash_fn(&key); \
    size_t idx = h % map->capacity; \
    MapTypeName##_entry* e = map->buckets[idx]; \
    while (e) { \
        if (e->hash == h && eq_fn(&e->key, &key)) { \
            return 1; \
        } \
        e = e->next; \
    } \
    return 0; \
} \
\
static void MapTypeName##_resize(MapTypeName* map) { \
    size_t new_cap = map->capacity * 2; \
    MapTypeName##_entry** new_buckets = calloc(new_cap, sizeof(*new_buckets)); \
    for (size_t i = 0; i < map->capacity; ++i) { \
        MapTypeName##_entry* e = map->buckets[i]; \
        while (e) { \
            MapTypeName##_entry* next = e->next; \
            size_t idx = e->hash % new_cap; \
            e->next = new_buckets[idx]; \
            new_buckets[idx] = e; \
            e = next; \
        } \
    } \
    free(map->buckets); \
    map->buckets = new_buckets; \
    map->capacity = new_cap; \
}

#endif //CHASH_H
