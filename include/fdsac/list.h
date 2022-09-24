#ifndef FDSAC_LIST_H
#define FDSAC_LIST_H

#include "macros.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct fds_list_node {
    struct fds_list_node *prev;
    struct fds_list_node *next;
} fds_list_node;

typedef fds_list_node fds_list;

void fds_list_init(fds_list *list);

void fds_list_insert(fds_list_node *node, fds_list_node *other);
void fds_list_remove(fds_list_node *node);

fds_list_node *fds_list_nth(fds_list *list, size_t n);
fds_list_node *fds_list_last(fds_list *list);
size_t fds_list_len(const fds_list *list);
bool fds_list_cycle(const fds_list *list);

#define fds_list_for_each(list, elemptr, type, member) \
    for (elemptr = fds_container_of(list.next, type, member); elemptr != NULL; \
         elemptr = fds_container_of(elemptr->member.next, type, member))

#define fds_list_for_each_reverse(list, elemptr, type, member) \
    for (elemptr = fds_container_of(fds_list_last(&list), type, member); \
         elemptr->member.prev != NULL; \
         elemptr = fds_container_of(elemptr->member.prev, type, member))

#endif
