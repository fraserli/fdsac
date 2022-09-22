#include "list.h"

void fd_list_init(fd_list *list) {
    list->prev = NULL;
    list->next = NULL;
}

void fd_list_insert(fd_list_node *node, fd_list_node *other) {
    other->prev = node;
    other->next = node->next;
    if (node->next != NULL) {
        node->next->prev = other;
    }
    node->next = other;
}

void fd_list_remove(fd_list_node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
}

fd_list_node *fd_list_nth(fd_list *list, size_t n) {
    fd_list_node *node = list;
    for (size_t i = 0; i <= n; i++) {
        if (node->next == NULL) {
            return NULL;
        }

        node = node->next;
    }

    return node;
}

fd_list_node *fd_list_last(fd_list *list) {
    fd_list_node *node = list;
    while (node->next != NULL) {
        node = node->next;
    }

    return node;
}

size_t fd_list_len(const fd_list *list) {
    size_t len = 0;
    const fd_list_node *node = list;

    while ((node = node->next) != NULL) {
        len += 1;
    }

    return len;
}

bool fd_list_cycle(const fd_list *list) {
    const fd_list_node *slow = list;
    const fd_list_node *fast = list;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}
