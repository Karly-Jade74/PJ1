// Student Name: [Your Name]
// ASU ID: [Your ASU ID]

#include "list_read.h"
#include "list_write.h"
#include <stdio.h>
#include <stdlib.h>

// Frees all nodes on pLIST and resets the list to empty
void listRelease(LIST *pLIST) {
    NODE *pNODE;
    NODE *pNext;

    if (!pLIST) return;

    pNODE = pLIST->head;
    while (pNODE) {
        pNext = pNODE->next;
        free(pNODE);
        pNODE = pNext;
    }

    pLIST->head   = NULL;
    pLIST->tail   = NULL;
    pLIST->length = 0;
}


// Allocates a new node with the given key and inserts it at the HEAD of pLIST.
// Returns a pointer to the new node, or NULL on failure.
NODE * listInsert(LIST *pLIST, double key) {
    NODE *pNODE;

    if (!pLIST) return NULL;

    pNODE = (NODE *) malloc(sizeof(NODE));
    if (!pNODE) {
        fprintf(stderr, "Error: malloc failed in listInsert\n");
        return NULL;
    }

    pNODE->key  = key;
    pNODE->next = pLIST->head;  // new node points to old head

    pLIST->head = pNODE;        // head is now the new node

    // If list was empty, tail is also the new node
    if (pLIST->length == 0) {
        pLIST->tail = pNODE;
    }

    pLIST->length++;
    return pNODE;
}


// Allocates a new node with the given key and appends it at the TAIL of pLIST.
// Returns a pointer to the new node, or NULL on failure.
NODE * listAppend(LIST *pLIST, double key) {
    NODE *pNODE;

    if (!pLIST) return NULL;

    pNODE = (NODE *) malloc(sizeof(NODE));
    if (!pNODE) {
        fprintf(stderr, "Error: malloc failed in listAppend\n");
        return NULL;
    }

    pNODE->key  = key;
    pNODE->next = NULL;  // new node is always the last node

    if (pLIST->length == 0) {
        // List was empty: both head and tail point to new node
        pLIST->head = pNODE;
        pLIST->tail = pNODE;
    } else {
        // Link old tail to new node, then update tail
        pLIST->tail->next = pNODE;
        pLIST->tail       = pNODE;
    }

    pLIST->length++;
    return pNODE;
}


// Searches for the first node with the given key and removes it from pLIST.
// Returns a pointer to the removed node (caller must free it), or NULL if not found.
NODE * listDelete(LIST *pLIST, double key) {
    NODE *pCurr;
    NODE *pPrev;

    if (!pLIST || pLIST->length == 0) {
        fprintf(stdout, "Warning in listDelete: Key %lf not in list\n", key);
        return NULL;
    }

    pPrev = NULL;
    pCurr = pLIST->head;

    // Walk the list looking for the key
    while (pCurr) {
        if (pCurr->key == key) {
            // Found it — unlink from list
            if (pPrev == NULL) {
                // Deleting the head node
                pLIST->head = pCurr->next;
            } else {
                pPrev->next = pCurr->next;
            }

            // If we deleted the tail, update tail pointer
            if (pCurr->next == NULL) {
                pLIST->tail = pPrev;
            }

            pCurr->next = NULL;
            pLIST->length--;
            return pCurr;
        }
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    // Key was not found
    fprintf(stdout, "Warning in listDelete: Key %lf not in list\n", key);
    return NULL;
}
