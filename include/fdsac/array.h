#ifndef FDSAC_ARRAY_H
#define FDSAC_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct fds_array {
    uint8_t *data;
    size_t elem_size;
    size_t cap;
    size_t len;
} fds_array;

void fds_array_init(fds_array *array, size_t elem_size);
void fds_array_init_with_cap(fds_array *array, size_t elem_size, size_t cap);
void fds_array_destroy(fds_array *array);

void fds_array_get(const fds_array *array, size_t index, void *elem);
void fds_array_set(fds_array *array, size_t index, void *elem);

void fds_array_push(fds_array *array, void *elem);

#endif
