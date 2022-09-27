#include <fdsac/list.h>

#include <assert.h>
#include <stdlib.h>

typedef struct elem {
    fds_list_node link;
    int value;
} elem;

int main() {
    fds_list list;
    fds_list_init(&list);

    assert(fds_list_len(&list) == 0);
    assert(fds_list_last(&list) == &list);
    assert(fds_list_nth(&list, 2) == NULL);
    assert(fds_list_cycle(&list) == false);

    elem *n1 = calloc(1, sizeof(elem));
    n1->value = 111;

    elem *n2 = calloc(1, sizeof(elem));
    n2->value = 222;

    elem *n3 = calloc(1, sizeof(elem));
    n3->value = 333;

    fds_list_insert(&list, &n1->link);
    fds_list_insert(&n1->link, &n3->link);
    fds_list_insert(&n1->link, &n2->link);

    assert(n3->link.prev == &n2->link);

    assert(fds_container_of(list.next, elem, link) == n1);
    assert(fds_container_of(list.next->next, elem, link) == n2);
    assert(fds_container_of(list.next->next->next, elem, link) == n3);
    assert(fds_container_of(fds_list_last(&list), elem, link) == n3);
    assert(fds_container_of(fds_list_nth(&list, 0), elem, link) == n1);
    assert(fds_container_of(fds_list_nth(&list, 1), elem, link) == n2);
    assert(fds_container_of(fds_list_nth(&list, 2), elem, link) == n3);
    assert(fds_list_nth(&list, 3) == NULL);
    assert(fds_list_len(&list) == 3);

    size_t count = 0;
    struct elem *e;
    fds_list_for_each(list, e, elem, link) {
        count += 1;
    }
    assert(count == 3);

    count = 0;
    fds_list_for_each_reverse(list, e, elem, link) {
        count += 1;
    }
    assert(count == 3);

    assert(fds_list_cycle(&list) == false);
    n3->link.next = &n1->link;
    assert(fds_list_cycle(&list) == true);

    free(n1);
    free(n2);
    free(n3);

    return 0;
}
