#include "set.h"

#include <stdlib.h>
#include <string.h>

static const size_t INITIAL_CAP = 16;
static const float MAX_LOAD_FACTOR = 0.75f;

void fds_set_init(fds_set *set, size_t elem_size, fds_hash_func hasher, fds_cmp_func cmp,
                  fds_free_func f) {
    memset(set, 0, sizeof(fds_set));
    set->elem_size = elem_size;
    set->hasher = hasher;
    set->elem_cmp = cmp;
    set->elem_free = f;
}

void fds_set_destroy(fds_set *set) {
    for (size_t i = 0; i < set->cap; i++) {
        if (set->entries[i].occupied) {
            if (set->elem_free != NULL) {
                set->elem_free(*(void **)set->entries[i].elem);
            }
            free(set->entries[i].elem);
        }
    }
    free(set->entries);
}

void fds_set_insert(fds_set *set, const void *elem) {
    if (fds_set_contains(set, elem)) {
        return;
    }

    if (set->cap == 0 || (float)set->len / (float)set->cap >= MAX_LOAD_FACTOR) {
        size_t new_cap = set->cap == 0 ? INITIAL_CAP : 2 * set->cap;
        fds_set_entry *new_entries = calloc(new_cap, sizeof(fds_set_entry));

        for (size_t i = 0; i < set->cap; i++) {
            if (set->entries[i].occupied) {
                uint64_t hash = set->hasher(set->entries[i].elem);
                size_t location = hash % new_cap;

                while (new_entries[location].occupied) {
                    location = (location + 1) % new_cap;
                }

                new_entries[location].elem = set->entries[i].elem;
                new_entries[location].occupied = true;
            }
        }

        free(set->entries);
        set->entries = new_entries;
        set->cap = new_cap;
    }

    uint64_t hash = set->hasher(elem);
    size_t location = hash % set->cap;

    while (set->entries[location].occupied) {
        location = (location + 1) % set->cap;
    }

    set->entries[location].occupied = true;
    set->entries[location].elem = malloc(set->elem_size);
    memcpy(set->entries[location].elem, elem, set->elem_size);
    set->len += 1;
}

void fds_set_remove(fds_set *set, const void *elem) {
    uint64_t hash = set->hasher(elem);
    size_t location = hash % set->cap;

    for (size_t i = location; i < set->cap; i++) {
        if (set->entries[i].occupied) {
            if (set->elem_cmp != NULL ? set->elem_cmp(set->entries[i].elem, elem) == 0
                                      : memcmp(set->entries[i].elem, elem, set->elem_size) == 0) {
                if (set->elem_free != NULL) {
                    set->elem_free(*(void **)set->entries[i].elem);
                }
                free(set->entries[i].elem);
                set->entries[i].occupied = false;
                set->entries[i].deleted = true;
            }
        } else if (!set->entries[i].occupied && !set->entries[i].deleted) {
            return;
        }
    }
}

bool fds_set_contains(const fds_set *set, const void *elem) {
    if (set->cap == 0) {
        return false;
    }

    uint64_t hash = set->hasher(elem);
    size_t location = hash % set->cap;

    for (size_t i = location; i < set->cap; i++) {
        if (set->entries[i].occupied) {
            if (set->elem_cmp != NULL ? set->elem_cmp(set->entries[i].elem, elem) == 0
                                      : memcmp(set->entries[i].elem, elem, set->elem_size) == 0) {
                return true;
            }
        } else if (!set->entries[i].occupied && !set->entries[i].deleted) {
            return false;
        }
    }

    return false;
}
