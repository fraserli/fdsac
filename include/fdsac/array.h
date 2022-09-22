#ifndef FDSAC_ARRAY_H
#define FDSAC_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct fd_array {
    uint8_t *data;
    size_t elemsize;
    size_t cap;
    size_t len;
} fd_array;

void fd_array_init(fd_array *array, size_t elemsize);
void fd_array_init_with_cap(fd_array *array, size_t elemsize, size_t cap);
void fd_array_destroy(fd_array *array);

void fd_array_get(const fd_array *array, size_t index, void *elem);
void fd_array_set(fd_array *array, size_t index, void *elem);

void fd_array_push(fd_array *array, void *elem);

#endif
