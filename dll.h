/**
 * \file dll.h  
 * \author Bilal Kohgadai
 * \brief Header file for doubly linked list implementation.
 * \date 2025-03-31
 * 
 */
#ifndef DLL_H // DLL_H
#define DLL_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct dll_node {
    struct dll_node* next;
    struct dll_node* prev;
    int key;
} dll_node_t;

typedef struct dll {
    dll_node_t* head;
    dll_node_t* tail;
    int size;
} dll_t;

// contrustor and destructor
dll_t* dll_create();
void dll_destroy(dll_t* list);

bool dll_is_empty(dll_t* list);

int dll_size(dll_t* list);

void dll_insert_head(dll_t* list, int key);
void dll_insert_tail(dll_t* list, int key);

void dll_remove(dll_t* list, int key);

void dll_move_to_head(dll_t* list, int key);
void dll_move_to_tail(dll_t* list, int key);

dll_node_t* dll_find(dll_t* list, int key);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // DLL_H
