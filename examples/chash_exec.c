//
// Created by Jessica Bruce on 8/1/25.
//

#include "../cfmt.h"
#include "../chash.h"

/// This should go in the header file, creates all of the prototypes for StringIntMap
declare_hashmap(StringIntMap, const char*, int)

/// This contains all the definitions of StringIntMap
/// `hash_str` and `eq_str` are predefined because they're common
/// If you're using a custom type, create a custom function to hash and check equality
define_hashmap(StringIntMap, const char*, int, hash_str, eq_str)

void use_hashmap() {
    StringIntMap map;
    StringIntMap_init(&map);

    // Simulate a list of words (duplicates included)
    const char* words[] = {
        "apple", "banana", "apple", "orange", "banana", "apple", "kiwi"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);

    for (size_t i = 0; i < word_count; ++i) {
        const char* word = words[i];
        int count = 0;
        if (StringIntMap_get(&map, word, &count)) {
            StringIntMap_set(&map, word, count + 1);
        } else {
            StringIntMap_set(&map, word, 1);
        }
    }

    // Print results
    c_println("Word counts");
    for (size_t i = 0; i < map.capacity; ++i) {
        StringIntMap_entry* e = map.buckets[i];
        while (e) {
            c_println("  {}: {}", ACStr(e->key), AInt(e->value));
            e = e->next;
        }
    }

    StringIntMap_free(&map);
}
