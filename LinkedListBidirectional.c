#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListBidirectional.h"

struct Material* create_material(const char* nazwa, double gestosc, char flaga) {
    struct Material* new_mat = (struct Material*)malloc(sizeof(struct Material));
    if (new_mat != NULL) {
        strncpy(new_mat->nazwa, nazwa, 99);
        new_mat->nazwa[99] = '\0';
        new_mat->gestosc = gestosc;
        new_mat->flaga = flaga;
    }
    return new_mat;
}

void free_material(struct Material* mat) {
    if (mat != NULL) free(mat);
}

struct Node* create_node(struct Material* mat) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node != NULL) {
        new_node->material = mat;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
}

void free_node(struct Node* node) {
    if (node != NULL) {
        if (node->material != NULL) free_material(node->material);
        free(node);
    }
}

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void print(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = list->head;
    int i = 0;
    while (current != NULL) {
        printf("[%d] Nazwa: %s, Gestosc: %.2lf, Flaga: %c\n",
               i, current->material->nazwa, current->material->gestosc, current->material->flaga);
        current = current->next;
        i++;
    }
}

void save(LinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return;
    struct Node* current = list->head;
    while (current != NULL) {
        fprintf(file, "%s:%lf:%c\n", current->material->nazwa, current->material->gestosc, current->material->flaga);
        current = current->next;
    }
    fclose(file);
    printf("Saved to %s\n", filename);
}

void load_list(LinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;
    char nazwa[100]; double gestosc; char flaga;
    while (fscanf(file, "%99[^:]:%lf:%c\n", nazwa, &gestosc, &flaga) == 3) {
        push(list, create_material(nazwa, gestosc, flaga));
    }
    fclose(file);
}

void print_actions() {
    printf("\n--- MENU ---\n");
    printf("1. Print list\n2. Push (Add to end)\n3. Pop (Remove from end)\n4. Push_at (Insert by index)\n5. Pop_at (Remove by index)\n6. Get_element (Show element)\n7. Save to file\n0. Exit\nChoice: ");
}

struct Node* _push_rec(struct Node* current, struct Node* new_node) {
    if (current->next == NULL) {
        current->next = new_node;
        new_node->prev = current;
        return new_node;
    }
    return _push_rec(current->next, new_node);
}

struct Node* push(LinkedList* list, struct Material* mat) {
    struct Node* new_node = create_node(mat);
    if (list->head == NULL) {
        list->head = new_node;
        return new_node;
    }
    return _push_rec(list->head, new_node);
}

struct Node* _pop_rec(struct Node* current) {
    if (current->next == NULL) {
        if (current->prev != NULL) current->prev->next = NULL;
        current->prev = NULL;
        return current;
    }
    return _pop_rec(current->next);
}

struct Node* pop(LinkedList* list) {
    if (list->head == NULL) return NULL;
    if (list->head->next == NULL) {
        struct Node* temp = list->head;
        list->head = NULL;
        return temp;
    }
    return _pop_rec(list->head);
}

struct Node* _get_element_rec(struct Node* current, int index) {
    if (current == NULL) return NULL;
    if (index == 0) return current;
    return _get_element_rec(current->next, index - 1);
}

struct Node* get_element(LinkedList* list, int index) {
    if (index < 0) return NULL;
    return _get_element_rec(list->head, index);
}

struct Node* push_at(LinkedList* list, struct Material* mat, int index) {
    if (index < 0) return NULL;
    struct Node* new_node = create_node(mat);
    if (index == 0) {
        new_node->next = list->head;
        if (list->head != NULL) list->head->prev = new_node;
        list->head = new_node;
        return new_node;
    }
    struct Node* target = _get_element_rec(list->head, index);
    if (target == NULL) {
        free_node(new_node);
        return push(list, mat);
    }
    new_node->next = target;
    new_node->prev = target->prev;
    if (target->prev != NULL) target->prev->next = new_node;
    target->prev = new_node;
    return new_node;
}

struct Node* pop_at(LinkedList* list, int index) {
    if (list->head == NULL || index < 0) return NULL;
    struct Node* target = _get_element_rec(list->head, index);
    if (target == NULL) return NULL;

    if (target->prev != NULL) target->prev->next = target->next;
    else list->head = target->next;

    if (target->next != NULL) target->next->prev = target->prev;

    target->next = NULL; target->prev = NULL;
    return target;
}

void free_list(LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* next = current->next;
        free_node(current);
        current = next;
    }
    free(list);
}

