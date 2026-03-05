#ifndef LINKEDLISTBIDIRECTIONAL_H
#define LINKEDLISTBIDIRECTIONAL_H
#include "Node.h"

struct LinkedList {
    struct Node* head;
};

struct LinkedList* create_list();
void free_list(struct LinkedList* list);

void print(struct LinkedList* list);
void save(struct LinkedList* list, const char* filename);
void load_list(struct LinkedList* list, const char* filename);
void print_actions();

struct Node* push(struct LinkedList* list, struct Material* mat);
struct Node* pop(struct LinkedList* list);
struct Node* push_at(struct LinkedList* list, struct Material* mat, int index);
struct Node* pop_at(struct LinkedList* list, int index);
struct Node* get_element(struct LinkedList* list, int index);

#endif
