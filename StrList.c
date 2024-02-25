#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

struct _Node {
    char* data;
    struct _Node* next;
};

struct _StrList {
    struct _Node* head;
    struct _Node* tail;
};

// Helper function to create a new node
static struct _Node* createNode(const char* data) {
    struct _Node* newNode = (struct _Node*)malloc(sizeof(struct _Node));
    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

// Helper function to free the nodes in the list
static void freeNodes(struct _Node* head) {
    while (head != NULL) {
        struct _Node* next = head->next;
        free(head->data);
        free(head);
        head = next;
    }
}

// Allocates a new empty StrList
StrList* StrList_alloc() {
    StrList* newList = (StrList*)malloc(sizeof(StrList));
    if (newList != NULL) {
        newList->head = NULL;
        newList->tail = NULL;
    }
    return newList;
}

// Frees the memory and resources allocated to StrList
void StrList_free(StrList* list) {
    if (list != NULL) {
        freeNodes(list->head);
        free(list);
    }
}

// Returns the number of elements in the StrList
size_t StrList_size(const StrList* list) {
    size_t size = 0;
    struct _Node* current = list->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

// Inserts an element at the end of the StrList
void StrList_insertLast(StrList* list, const char* data) {
    struct _Node* newNode = createNode(data);

    if (list->tail == NULL) {
        // Empty list
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Inserts an element at a given index
void StrList_insertAt(StrList* list, const char* data, int index) {
    struct _Node* newNode = createNode(data);

    if (index <= 0 || list->head == NULL) {
        // Insert at the beginning
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == NULL) {
            // Empty list
            list->tail = newNode;
        }
    } else {
        // Insert at a non-zero index
        struct _Node* current = list->head;
        for (int i = 0; i < index - 1 && current != NULL; i++) {
            current = current->next;
        }

        if (current != NULL) {
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == NULL) {
                // Update tail if the new node is the last node
                list->tail = newNode;
            }
        } else {
            // Index out of bounds, append to the end
            StrList_insertLast(list, data);
        }
    }
}

// Returns the StrList first data
char* StrList_firstData(const StrList* list) {
    if (list->head != NULL) {
        return list->head->data;
    }
    return NULL;
}

// Prints the StrList to the standard output
void StrList_print(const StrList* list) {
    struct _Node* current = list->head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Prints the word at the given index to the standard output
void StrList_printAt(const StrList* list, int index) {
    struct _Node* current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }

    if (current != NULL) {
        printf("%s\n", current->data);
    } else {
        printf("Index out of bounds\n");
    }
}


// Given a string, return the number of times it exists in the list
int StrList_count(StrList* list, const char* data) {
    int count = 0;
    struct _Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Given a string and a list, remove all occurrences of this string in the list
void StrList_remove(StrList* list, const char* data) {
    struct _Node* current = list->head;
    struct _Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev != NULL) {
                // Remove a node that is not the head
                prev->next = current->next;
                free(current->data);
                free(current);
                current = prev->next;
            } else {
                // Remove the head node
                struct _Node* next = current->next;
                free(current->data);
                free(current);
                list->head = next;
                current = list->head;
                if (current == NULL) {
                    // The list is now empty, update the tail
                    list->tail = NULL;
                }
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Given an index and a list, remove the string at that index
void StrList_removeAt(StrList* list, int index) {
    struct _Node* current = list->head;
    struct _Node* prev = NULL;

    for (int i = 0; i < index && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL) {
            // Remove a node that is not the head
            prev->next = current->next;
            free(current->data);
            free(current);
            if (prev->next == NULL) {
                // Update the tail if the removed node was the last one
                list->tail = prev;
            }
        } else {
            // Remove the head node
            struct _Node* next = current->next;
            free(current->data);
            free(current);
            list->head = next;
            if (next == NULL) {
                // The list is now empty, update the tail
                list->tail = NULL;
            }
        }
    } else {
        printf("Index out of bounds\n");
    }
}

// Checks if two StrLists have the same elements
int StrList_isEqual(const StrList* list1, const StrList* list2) {
    struct _Node* current1 = list1->head;
    struct _Node* current2 = list2->head;

    while (current1 != NULL && current2 != NULL) {
        if (strcmp(current1->data, current2->data) != 0) {
            return 0;  // Not equal
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    // Lists are equal if both are at the end
    return (current1 == NULL && current2 == NULL);
}

// Clones the given StrList
StrList* StrList_clone(const StrList* list) {
    StrList* newList = StrList_alloc();

    if (newList != NULL) {
        struct _Node* current = list->head;
        while (current != NULL) {
            StrList_insertLast(newList, current->data);
            current = current->next;
        }
    }

    return newList;
}

// Checks if the given list is sorted in lexicographical order
int StrList_isSortedLexicographically(StrList* list) {
    struct _Node* current = list->head;

    while (current != NULL && current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;  // Not sorted lexicographically
        }
        current = current->next;
    }

    return 1;  // Sorted lexicographically
}

// Reverses the given StrList
void StrList_reverse(StrList* list) {
    struct _Node* prev = NULL;
    struct _Node* current = list->head;
    struct _Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // Update head and tail after reversing
    list->tail = list->head;
    list->head = prev;
}

// Sorts the given list in lexicographical order
void StrList_sort(StrList* list) {
    // Implementation of sorting is left to the user
    // This can be done using a sorting algorithm of choice
    // For simplicity, let's use a simple bubble sort in this example

    int swapped;
    struct _Node* ptr1 = NULL;
    struct _Node* lptr = NULL;

    if (list->head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                // Swap nodes if they are in the wrong order
                char* temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Checks if the given list is sorted in lexicographical order
int StrList_isSorted(StrList* list) {
    struct _Node* current = list->head;

    while (current != NULL && current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;  // Not sorted
        }
        current = current->next;
    }

    return 1;  // Sorted
}

// Return the amount of chars in the list.
int StrList_printLen(const StrList* list) {
    struct _Node* current = list->head;
    int totalLength = 0;

    while (current != NULL) {
        totalLength += strlen(current->data);
        current = current->next;
    }

    return totalLength;
}
