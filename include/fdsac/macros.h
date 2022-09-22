#ifndef FDSAC_MACROS_H
#define FDSAC_MACROS_H

#define fd_container_of(ptr, type, member) \
    (type *)((char *)(1 ? ptr : &((type *)0)->member) - offsetof(type, member))

#endif
