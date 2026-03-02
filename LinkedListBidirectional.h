#ifndef LINKEDLISTBIDIRECTIONAL_H
#define LINKEDLISTBIDIRECTIONAL_H

#include "Wezel.h"

typedef struct {
    struct Wezel* head;
} LinkedList;

LinkedList* createList();
void freeList(LinkedList* list);

void print(LinkedList* list);
void save(LinkedList* list, const char* filename);
void loadList(LinkedList* list, const char* filename);
void printActions();

struct Wezel* push(LinkedList* list, struct Material* mat);
struct Wezel* pop(LinkedList* list);
struct Wezel* popAt(LinkedList* list, int index);
struct Wezel* pushAt(LinkedList* list, struct Material* mat, int index);
struct Wezel* getElement(LinkedList* list, int index);

#endif
