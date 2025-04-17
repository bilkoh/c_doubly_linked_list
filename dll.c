/**
 * \file dll.c 
 * \author Bilal Kohgadai
 * \brief Source file for a doubly linked list implementation.
 * \date 2025-03-31
 * 
 */

#include <stdlib.h>
#include "dll.h"

dll_t*
dll_create() {
    dll_t* list = (dll_t*)malloc(sizeof(dll_t));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void
dll_destroy(dll_t* list) {
    if (!list) {
        return;
    }

    dll_node_t* curr = list->head;
    while (curr) {
        dll_node_t* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

bool
dll_is_empty(dll_t* list) {
    return (list->size == 0);
}

int
dll_size(dll_t* list) {
    return list->size;
}

void
dll_insert_head(dll_t* list, int key) {
    dll_node_t* new_node = (dll_node_t*)malloc(sizeof(dll_node_t));

    if (!new_node) {
        return;
    }
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->key = key;

    if (dll_is_empty(list)) {
        list->head = list->tail = new_node;
    } else {
        dll_node_t* old_head = list->head;
        new_node->next = old_head;
        old_head->prev = new_node;
        list->head = new_node;
    }

    list->size++;
}

void
dll_insert_tail(dll_t* list, int key) {
    dll_node_t* new_node = (dll_node_t*)malloc(sizeof(dll_node_t));

    if (!new_node) {
        return;
    }
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->key = key;

    if (dll_is_empty(list)) {
        list->head = list->tail = new_node;
    } else {
        dll_node_t* old_tail = list->tail;

        old_tail->next = new_node;
        new_node->prev = old_tail;
        list->tail = new_node;
    }

    list->size++;
}

void
dll_remove(dll_t* list, int key) {
    if (dll_is_empty(list)) {
        return;
    }

    dll_node_t* found = dll_find(list, key);
    if (!found) {
        return;
    }

    dll_node_t* prev = found->prev;
    dll_node_t* next = found->next;

    if (prev) {
        prev->next = next;
    } else {
        // case: removing head element
        list->head = next;
    }

    if (next) {
        next->prev = prev;
    } else {
        // case removing tail element
        list->tail = prev;
    }

    free(found);
    list->size--;
}

void
dll_move_to_head(dll_t* list, int key) {
    if (dll_is_empty(list)) {
        return;
    }

    dll_node_t* found = dll_find(list, key);
    if (!found || found == list->head) {
        return;
    }

    // repositioning (similar to remove)
    dll_node_t* prev = found->prev;
    dll_node_t* next = found->next;

    if (prev) {
        prev->next = next;
    }

    if (next) {
        next->prev = prev;
    } else {
        // case removing tail element
        list->tail = prev;
        if (list->tail) {
            // case: avoid issues w/ only one node in list
            list->tail->next = NULL;
        }
    }

    // insertion
    found->prev = NULL;
    found->next = list->head;
    if (list->head) {
        list->head->prev = found;
    }
    list->head = found;
}

void
dll_move_to_tail(dll_t* list, int key) {
    if (dll_is_empty(list)) {
        return;
    }

    dll_node_t* found = dll_find(list, key);
    if (!found || found == list->tail) {
        return;
    }

    // repositioning (similar to remove)
    dll_node_t* prev = found->prev;
    dll_node_t* next = found->next;

    if (prev) {
        prev->next = next;
    } else {
        // case removing head element
        list->head = next;
        if (list->head) {
            // case: avoid issues w/ only one node in list
            list->head->prev = NULL;
        }
    }

    if (next) {
        next->prev = prev;
    }

    // insertion
    found->next = NULL;
    found->prev = list->tail;
    if (list->tail) {
        list->tail->next = found;
    }
    list->tail = found;
}

dll_node_t*
dll_find(dll_t* list, int key) {
    dll_node_t* curr = list->head;

    while (curr) {
        if (curr->key == key) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}