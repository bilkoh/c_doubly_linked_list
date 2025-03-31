#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

static void
test_create_and_empty(void) {
    dll_t* list = dll_create();
    assert(list != NULL);
    assert(dll_is_empty(list));
    assert(dll_size(list) == 0);
    dll_destroy(list);
    printf("test_create_and_empty passed.\n");
}

static void
test_insert_head_tail(void) {
    dll_t* list = dll_create();
    assert(list != NULL);

    // Insert head: list becomes [10]
    dll_insert_head(list, 10);
    assert(!dll_is_empty(list));
    assert(dll_size(list) == 1);
    assert(dll_find(list, 10) != NULL);

    // Insert head: list becomes [20,10]
    dll_insert_head(list, 20);
    assert(dll_size(list) == 2);
    assert(dll_find(list, 20) != NULL);
    assert(dll_find(list, 10) != NULL);

    // Insert tail: list becomes [20,10,30]
    dll_insert_tail(list, 30);
    assert(dll_size(list) == 3);
    assert(dll_find(list, 30) != NULL);

    dll_destroy(list);
    printf("test_insert_head_tail passed.\n");
}

static void
test_remove(void) {
    dll_t* list = dll_create();
    assert(list != NULL);

    // Build list: [3,2,1] using insert_head
    dll_insert_head(list, 1);
    dll_insert_head(list, 2);
    dll_insert_head(list, 3);
    assert(dll_size(list) == 3);

    // Remove middle element (2)
    dll_remove(list, 2);
    assert(dll_size(list) == 2);
    assert(dll_find(list, 2) == NULL);

    // Remove head element (3)
    dll_remove(list, 3);
    assert(dll_size(list) == 1);
    assert(dll_find(list, 3) == NULL);

    // Remove tail element (1)
    dll_remove(list, 1);
    assert(dll_size(list) == 0);
    assert(dll_is_empty(list));

    dll_destroy(list);
    printf("test_remove passed.\n");
}

static void
test_move_to_head(void) {
    dll_t* list = dll_create();
    assert(list != NULL);

    // Build list using insert_tail: [1,2,3]
    dll_insert_tail(list, 1);
    dll_insert_tail(list, 2);
    dll_insert_tail(list, 3);
    assert(dll_size(list) == 3);

    // Move tail element (3) to head.
    dll_move_to_head(list, 3);
    // Remove head (should now be 3) to verify repositioning.
    dll_remove(list, 3);
    assert(dll_find(list, 3) == NULL);
    assert(dll_size(list) == 2);

    dll_destroy(list);
    printf("test_move_to_head passed.\n");
}

static void
test_move_to_tail(void) {
    dll_t* list = dll_create();
    assert(list != NULL);

    // Build list using insert_head: [3,2,1]
    dll_insert_head(list, 1);
    dll_insert_head(list, 2);
    dll_insert_head(list, 3);
    assert(dll_size(list) == 3);

    // Move head element (3) to tail.
    dll_move_to_tail(list, 3);
    // Remove tail (should now be 3) to verify repositioning.
    dll_remove(list, 3);
    assert(dll_find(list, 3) == NULL);
    assert(dll_size(list) == 2);

    dll_destroy(list);
    printf("test_move_to_tail passed.\n");
}

int
main(void) {
    test_create_and_empty();
    test_insert_head_tail();
    test_remove();
    test_move_to_head();
    test_move_to_tail();
    printf("All tests passed.\n");
    return 0;
}