#include <stdio.h>
#include <stdlib.h>
#include "LinkedListBidirectional.h"

int main() {
    LinkedList* list = create_list();
    load_list(list, "baza.txt");

    int choice = -1, index;
    char nazwa[100], flaga;
    double gestosc;
    struct Node* returned_node = NULL;

    while (choice != 0) {
        print_actions();
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }

        switch (choice) {
            case 1: print(list); break;
            case 2:
                printf("Nazwa, Gestosc, Flaga: ");
                scanf("%99s %lf %c", nazwa, &gestosc, &flaga);
                push(list, create_material(nazwa, gestosc, flaga));
                break;
            case 3:
                returned_node = pop(list);
                if (returned_node) {
                    printf("Removed: %s\n", returned_node->material->nazwa);
                    free_node(returned_node);
                } else {
                    printf("List is empty.\n");
                }
                break;
            case 4:
                printf("Index, Name, Density, Flag: ");
                scanf("%d %99s %lf %c", &index, nazwa, &gestosc, &flaga);
                push_at(list, create_material(nazwa, gestosc, flaga), index);
                break;
            case 5:
                printf("Index: "); scanf("%d", &index);
                returned_node = pop_at(list, index);
                if (returned_node) {
                    printf("Removed: %s\n", returned_node->material->nazwa);
                    free_node(returned_node);
                } else {
                    printf("Failed to remove (incorrect index).\n");
                }
                break;
            case 6:
                printf("Index: "); scanf("%d", &index);
                returned_node = get_element(list, index);
                if (returned_node) printf("Element: %s\n", returned_node->material->nazwa);
                else printf("Element not found.\n");
                break;
            case 7: save(list, "baza.txt"); break;
            case 0: break;
            default: printf("Input error.\n");
        }
    }
    free_list(list);
    return 0;
}

