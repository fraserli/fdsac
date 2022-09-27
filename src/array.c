#include "array.h"

#include <stdlib.h>
#include <string.h>

void fds_array_init(fds_array *array, size_t elemsize) {
    memset(array, 0, sizeof(fds_array));
    array->elem_size = elemsize;
}

void fds_array_init_with_cap(fds_array *array, size_t elemsize, size_t cap) {
    memset(array, 0, sizeof(fds_array));
    array->elem_size = elemsize;
    array->data = calloc(cap, elemsize);
    array->cap = cap;
}

void fds_array_destroy(fds_array *array) {
    free(array->data);
    memset(array, 0, sizeof(fds_array));
}

void fds_array_get(const fds_array *array, size_t index, void *elem) {
    memcpy(elem, array->data + index * array->elem_size, array->elem_size);
}

void fds_array_set(fds_array *array, size_t index, void *elem) {
    memcpy(array->data + index * array->elem_size, elem, array->elem_size);
}

void fds_array_push(fds_array *array, void *elem) {
    if (array->len >= array->cap) {
        size_t new_cap = array->cap == 0 ? 1 : array->cap * 2;
        uint8_t *new_data = realloc(array->data, new_cap * array->elem_size);
        array->data = new_data;
        array->cap = new_cap;
    }

    fds_array_set(array, array->len, elem);
    array->len += 1;
}
