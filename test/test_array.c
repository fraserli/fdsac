#include <fdsac/array.h>

#include <assert.h>

int main() {
    fd_array arr;
    fd_array_init(&arr, sizeof(int));

    int val = 1;
    fd_array_push(&arr, &val);
    fd_array_push(&arr, &val);
    fd_array_push(&arr, &(int){1234});

    for (size_t i = 0; i < 1000; i++) {
        fd_array_push(&arr, &(int){312231});
    }

    assert(arr.len == 1003);

    int a;
    fd_array_get(&arr, 2, &a);
    assert(a == 1234);

    for (size_t i = 0; i < arr.len; i++) {
        int elem;
        fd_array_get(&arr, i, &elem);
    }

    fd_array_destroy(&arr);

    return 0;
}
