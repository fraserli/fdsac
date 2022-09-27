#ifndef FDSAC_MACROS_H
#define FDSAC_MACROS_H

#include <stdint.h>

#define fds_container_of(ptr, type, member) \
    (type *)((char *)(1 ? ptr : &((type *)0)->member) - offsetof(type, member))

typedef int (*fds_cmp_func)(const void *a, const void *b);
typedef void (*fds_free_func)(void *ptr);
typedef uint64_t (*fds_hash_func)(const void *value);

#endif
