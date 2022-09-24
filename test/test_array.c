#include <fdsac/array.h>

#include <assert.h>

int main() {
    fds_array arr;
    fds_array_init(&arr, sizeof(int));

    int val = 1;
    fds_array_push(&arr, &val);
    fds_array_push(&arr, &val);
    fds_array_push(&arr, &(int){1234});

    for (size_t i = 0; i < 1000; i++) {
        fds_array_push(&arr, &(int){312231});
    }

    assert(arr.len == 1003);

    int a;
    fds_array_get(&arr, 2, &a);
    assert(a == 1234);

    for (size_t i = 0; i < arr.len; i++) {
        int elem;
        fds_array_get(&arr, i, &elem);
    }

    fds_array_destroy(&arr);

    return 0;
}
