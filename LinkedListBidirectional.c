#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListBidirectional.h"

struct Material* create_material(const char* n, double g, char f) {
    struct Material* m = malloc(sizeof(struct Material));
    strcpy(m->nazwa, n);
    m->gestosc = g;
    m->flaga = f;
    return m;
}

void free_material(struct Material* m) { free(m); }

struct Node* create_node(struct Material* m) {
    struct Node* n = calloc(1, sizeof(struct Node));
    n->material = m;
    return n;
}

void free_node(struct Node* n) {
    free_material(n->material);
    free(n);
}

LinkedList* create_list() {
    return calloc(1, sizeof(LinkedList));
}

void free_list(LinkedList* l) {
    while (l->head) {
        struct Node* next = l->head->next;
        free_node(l->head);
        l->head = next;
    }
    free(l);
}

void print(LinkedList* l) {
    int i = 0;
    for (struct Node* c = l->head; c != NULL; c = c->next) {
        printf("[%d] %s (%.2lf) [%c]\n", i++, c->material->nazwa, c->material->gestosc, c->material->flaga);
    }
}

void save(LinkedList* l, const char* name) {
    FILE* f = fopen(name, "w");
    if (!f) return;
    for (struct Node* c = l->head; c != NULL; c = c->next) {
        fprintf(f, "%s:%lf:%c\n", c->material->nazwa, c->material->gestosc, c->material->flaga);
    }
    fclose(f);
}

void load_list(LinkedList* l, const char* name) {
    FILE* f = fopen(name, "r");
    if (!f) return;
    char n[100]; double g; char fl;
    while (fscanf(f, "%99[^:]:%lf:%c\n", n, &g, &fl) == 3) {
        push(l, create_material(n, g, fl));
    }
    fclose(f);
}

void print_actions() {
    printf("\n1.Print | 2.Push | 3.Pop | 4.Push_at | 5.Pop_at | 6.Get | 7.Save | 0.Exit\nWybor: ");
}

struct Node* get_element(LinkedList* l, int index) {
    struct Node* curr = l->head;
    while (curr && index > 0) {
        curr = curr->next;
        index--;
    }
    return curr;
}

struct Node* push(LinkedList* l, struct Material* m) {
    struct Node* new_n = create_node(m);
    if (!l->head) { l->head = new_n; return new_n; }

    struct Node* curr = l->head;
    while (curr->next) curr = curr->next;

    curr->next = new_n;
    new_n->prev = curr;
    return new_n;
}

struct Node* pop(LinkedList* l) {
    if (!l->head) return NULL;
    if (!l->head->next) {
        struct Node* n = l->head;
        l->head = NULL;
        return n;
    }

    struct Node* curr = l->head;
    while (curr->next) curr = curr->next;

    curr->prev->next = NULL;
    curr->prev = NULL;
    return curr;
}

struct Node* push_at(LinkedList* l, struct Material* m, int index) {
    if (index == 0 || !l->head) {
        struct Node* new_n = create_node(m);
        new_n->next = l->head;
        if (l->head) l->head->prev = new_n;
        l->head = new_n;
        return new_n;
    }

    struct Node* right = get_element(l, index);
    if (!right) return push(l, m);

    struct Node* new_n = create_node(m);
    struct Node* left = right->prev;

    left->next = new_n; new_n->prev = left;
    new_n->next = right; right->prev = new_n;
    return new_n;
}

struct Node* pop_at(LinkedList* l, int index) {
    struct Node* target = get_element(l, index);
    if (!target) return NULL;

    if (target == l->head) {
        l->head = target->next;
        if (l->head) l->head->prev = NULL;
    } else {
        struct Node* left = target->prev;
        struct Node* right = target->next;

        left->next = right;
        if (right) right->prev = left;
    }

    target->prev = NULL; target->next = NULL;
    return target;
}
