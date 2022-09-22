#include "array.h"

#include <stdlib.h>
#include <string.h>

void fd_array_init(fd_array *array, size_t elemsize) {
    memset(array, 0, sizeof(fd_array));
    array->elemsize = elemsize;
}

void fd_array_init_with_cap(fd_array *array, size_t elemsize, size_t cap) {
    memset(array, 0, sizeof(fd_array));
    array->elemsize = elemsize;
    array->data = calloc(cap, elemsize);
    array->cap = cap;
}

void fd_array_destroy(fd_array *array) {
    free(array->data);
    memset(array, 0, sizeof(fd_array));
}

void fd_array_get(const fd_array *array, size_t index, void *elem) {
    memcpy(elem, array->data + index * array->elemsize, array->elemsize);
}

void fd_array_set(fd_array *array, size_t index, void *elem) {
    memcpy(array->data + index * array->elemsize, elem, array->elemsize);
}

void fd_array_push(fd_array *array, void *elem) {
    if (array->len >= array->cap) {
        size_t new_cap = array->cap == 0 ? 1 : array->cap * 2;
        uint8_t *new_data = realloc(array->data, new_cap * array->elemsize);
        array->data = new_data;
        array->cap = new_cap;
    }

    fd_array_set(array, array->len, elem);
    array->len += 1;
}
