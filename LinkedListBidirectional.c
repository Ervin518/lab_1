#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListBidirectional.h"

struct Material* createMaterial(const char* nazwa, double gestosc, char flaga) {
    struct Material* newMat = (struct Material*)malloc(sizeof(struct Material));
    if (newMat != NULL) {
        strncpy(newMat->nazwa, nazwa, 99);
        newMat->nazwa[99] = '\0';
        newMat->gestosc = gestosc;
        newMat->flaga = flaga;
    }
    return newMat;
}

void freeMaterial(struct Material* mat) {
    if (mat != NULL) free(mat);
}

struct Wezel* createWezel(struct Material* mat) {
    struct Wezel* newWezel = (struct Wezel*)malloc(sizeof(struct Wezel));
    if (newWezel != NULL) {
        newWezel->material = mat;
        newWezel->next = NULL;
        newWezel->prev = NULL;
    }
    return newWezel;
}

void freeWezel(struct Wezel* wezel) {
    if (wezel != NULL) {
        if (wezel->material != NULL) freeMaterial(wezel->material);
        free(wezel);
    }
}

LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void print(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Wezel* current = list->head;
    int i = 0;
    while (current != NULL) {
        printf("[%d] Name: %s, Density: %.2lf, Flag: %c\n",
               i, current->material->nazwa, current->material->gestosc, current->material->flaga);
        current = current->next;
        i++;
    }
}

void save(LinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return;
    struct Wezel* current = list->head;
    while (current != NULL) {
        fprintf(file, "%s:%lf:%c\n", current->material->nazwa, current->material->gestosc, current->material->flaga);
        current = current->next;
    }
    fclose(file);
    printf("Saved to %s\n", filename);
}

void loadList(LinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;
    char nazwa[100]; double gestosc; char flaga;
    while (fscanf(file, "%99[^:]:%lf:%c\n", nazwa, &gestosc, &flaga) == 3) {
        push(list, createMaterial(nazwa, gestosc, flaga));
    }
    fclose(file);
}

void printActions() {
    printf("\n--- MENU ---\n");
    printf("1. Print list\n2. Push (Add to end)\n3. Pop (Remove from end)\n");
    printf("4. PushAt (Insert by index)\n5. PopAt (Remove by index)\n");
    printf("6. getElement (Show element)\n7. Save to file\n0. Exit\nChoice: ");
}

struct Wezel* _pushRec(struct Wezel* current, struct Wezel* newWezel) {
    if (current->next == NULL) {
        current->next = newWezel;
        newWezel->prev = current;
        return newWezel;
    }
    return _pushRec(current->next, newWezel);
}

struct Wezel* push(LinkedList* list, struct Material* mat) {
    struct Wezel* newWezel = createWezel(mat);
    if (list->head == NULL) {
        list->head = newWezel;
        return newWezel;
    }
    return _pushRec(list->head, newWezel);
}

struct Wezel* _popRec(struct Wezel* current) {
    if (current->next == NULL) {
        if (current->prev != NULL) current->prev->next = NULL;
        current->prev = NULL;
        return current;
    }
    return _popRec(current->next);
}

struct Wezel* pop(LinkedList* list) {
    if (list->head == NULL) return NULL;
    if (list->head->next == NULL) {
        struct Wezel* temp = list->head;
        list->head = NULL;
        return temp;
    }
    return _popRec(list->head);
}

struct Wezel* _getElementRec(struct Wezel* current, int index) {
    if (current == NULL) return NULL;
    if (index == 0) return current;
    return _getElementRec(current->next, index - 1);
}

struct Wezel* getElement(LinkedList* list, int index) {
    if (index < 0) return NULL;
    return _getElementRec(list->head, index);
}

struct Wezel* pushAt(LinkedList* list, struct Material* mat, int index) {
    if (index < 0) return NULL;
    struct Wezel* newWezel = createWezel(mat);
    if (index == 0) {
        newWezel->next = list->head;
        if (list->head != NULL) list->head->prev = newWezel;
        list->head = newWezel;
        return newWezel;
    }
    struct Wezel* target = _getElementRec(list->head, index);
    if (target == NULL) {
        freeWezel(newWezel);
        return push(list, mat);
    }
    newWezel->next = target;
    newWezel->prev = target->prev;
    if (target->prev != NULL) target->prev->next = newWezel;
    target->prev = newWezel;
    return newWezel;
}

struct Wezel* popAt(LinkedList* list, int index) {
    if (list->head == NULL || index < 0) return NULL;
    struct Wezel* target = _getElementRec(list->head, index);
    if (target == NULL) return NULL;

    if (target->prev != NULL) target->prev->next = target->next;
    else list->head = target->next;

    if (target->next != NULL) target->next->prev = target->prev;

    target->next = NULL; target->prev = NULL;
    return target;
}

void freeList(LinkedList* list) {
    struct Wezel* current = list->head;
    while (current != NULL) {
        struct Wezel* next = current->next;
        freeWezel(current);
        current = next;
    }
    free(list);
}
