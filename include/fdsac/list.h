#ifndef FDSAC_LIST_H
#define FDSAC_LIST_H

#include "macros.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct fd_list_node {
    struct fd_list_node *prev;
    struct fd_list_node *next;
} fd_list_node;

typedef fd_list_node fd_list;

void fd_list_init(fd_list *list);

void fd_list_insert(fd_list_node *node, fd_list_node *other);
void fd_list_remove(fd_list_node *node);

fd_list_node *fd_list_nth(fd_list *list, size_t n);
fd_list_node *fd_list_last(fd_list *list);
size_t fd_list_len(const fd_list *list);
bool fd_list_cycle(const fd_list *list);

#define fd_list_for_each(list, elemptr, type, member) \
    for (elemptr = fd_container_of(list.next, type, member); elemptr != NULL; \
         elemptr = fd_container_of(elemptr->member.next, type, member))

#define fd_list_for_each_reverse(list, elemptr, type, member) \
    for (elemptr = fd_container_of(fd_list_last(&list), type, member); \
         elemptr->member.prev != NULL; \
         elemptr = fd_container_of(elemptr->member.prev, type, member))

#endif
