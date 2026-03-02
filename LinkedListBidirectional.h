#ifndef LINKEDLISTBIDIRECTIONAL_H
#define LINKEDLISTBIDIRECTIONAL_H

#include "Wezel.h"

typedef struct {
    struct Node* head;
} LinkedList;

LinkedList* create_list();
void free_list(LinkedList* list);

void print(LinkedList* list);
void save(LinkedList* list, const char* filename);
void load_list(LinkedList* list, const char* filename);
void print_actions();

struct Node* push(LinkedList* list, struct Material* mat);
struct Node* pop(LinkedList* list);
struct Node* pop_at(LinkedList* list, int index);
struct Node* push_at(LinkedList* list, struct Material* mat, int index);
struct Node* get_element(LinkedList* list, int index);

#endif
