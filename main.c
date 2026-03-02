#include <stdio.h>
#include <stdlib.h>
#include "LinkedListBidirectional.h"

int main() {
    LinkedList* list = createList();
    loadList(list, "baza.txt");

    int choice = -1, index;
    char nazwa[100], flaga;
    double gestosc;
    struct Wezel* returnedWezel = NULL;

    while (choice != 0) {
        printActions();
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }

        switch (choice) {
            case 1: print(list); break;
            case 2:
                printf("Name, Density, Flag: ");
                scanf("%99s %lf %c", nazwa, &gestosc, &flaga);
                push(list, createMaterial(nazwa, gestosc, flaga));
                break;
            case 3:
                returnedWezel = pop(list);
                if (returnedWezel) {
                    printf("Removed: %s\n", returnedWezel->material->nazwa);
                    freeWezel(returnedWezel);
                } else {
                    printf("List is empty.\n");
                }
                break;
            case 4:
                printf("Index, Name, Density, Flag: ");
                scanf("%d %99s %lf %c", &index, nazwa, &gestosc, &flaga);
                pushAt(list, createMaterial(nazwa, gestosc, flaga), index);
                break;
            case 5:
                printf("Index: "); scanf("%d", &index);
                returnedWezel = popAt(list, index);
                if (returnedWezel) {
                    printf("Removed: %s\n", returnedWezel->material->nazwa);
                    freeWezel(returnedWezel);
                } else {
                    printf("Failed to remove (incorrect index).\n");
                }
                break;
            case 6:
                printf("Index: "); scanf("%d", &index);
                returnedWezel = getElement(list, index);
                if (returnedWezel) printf("Element: %s\n", returnedWezel->material->nazwa);
                else printf("Element not found.\n");
                break;
            case 7: save(list, "baza.txt"); break;
            case 0: break;
            default: printf("Input error.\n");
        }
    }
    freeList(list);
    return 0;
}
