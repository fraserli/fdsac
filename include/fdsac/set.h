#ifndef FDSAC_SET_H
#define FDSAC_SET_H

#include "common.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct fds_set_entry {
    void *elem;
    bool occupied;
    bool deleted;
} fds_set_entry;

typedef struct fds_set {
    size_t elem_size;
    fds_hash_func hasher;
    fds_cmp_func elem_cmp;
    fds_free_func elem_free;
    fds_set_entry *entries;
    size_t cap;
    size_t len;
} fds_set;

void fds_set_init(fds_set *set, size_t elem_size, fds_hash_func hasher, fds_cmp_func cmp,
                  fds_free_func f);
void fds_set_destroy(fds_set *set);

void fds_set_insert(fds_set *set, const void *elem);
void fds_set_remove(fds_set *set, const void *elem);
bool fds_set_contains(const fds_set *set, const void *elem);

#endif
