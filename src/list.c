#include "list.h"

void fds_list_init(fds_list *list) {
    list->prev = NULL;
    list->next = NULL;
}

void fds_list_insert(fds_list_node *node, fds_list_node *other) {
    other->prev = node;
    other->next = node->next;
    if (node->next != NULL) {
        node->next->prev = other;
    }
    node->next = other;
}

void fds_list_remove(fds_list_node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
}

fds_list_node *fds_list_nth(fds_list *list, size_t n) {
    fds_list_node *node = list;
    for (size_t i = 0; i <= n; i++) {
        if (node->next == NULL) {
            return NULL;
        }

        node = node->next;
    }

    return node;
}

fds_list_node *fds_list_last(fds_list *list) {
    fds_list_node *node = list;
    while (node->next != NULL) {
        node = node->next;
    }

    return node;
}

size_t fds_list_len(const fds_list *list) {
    size_t len = 0;
    const fds_list_node *node = list;

    while ((node = node->next) != NULL) {
        len += 1;
    }

    return len;
}

bool fds_list_cycle(const fds_list *list) {
    const fds_list_node *slow = list;
    const fds_list_node *fast = list;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}
