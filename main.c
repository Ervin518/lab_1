#include <stdio.h>
#include <stdlib.h>
#include "LinkedListBidirectional.h"

int main() {
    LinkedList* list = create_list();
    load_list(list, "baza.txt");

    int choice = -1;
    int index;
    char nazwa[100];
    double gestosc;
    char flaga;
    struct Node* temp = NULL;

    while (choice != 0) {
        print_actions();
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                print(list);
                break;
            case 2:
                printf("Podaj: Nazwa Gestosc Flaga (np. Zelazo 7850 Z): ");
                scanf("%99s %lf %c", nazwa, &gestosc, &flaga);
                push(list, create_material(nazwa, gestosc, flaga));
                break;
            case 3:
                temp = pop(list);
                if (temp) {
                    printf("Usunieto: %s\n", temp->material->nazwa);
                    free_node(temp);
                } else printf("Lista jest pusta!\n");
                break;
            case 4:
                printf("Podaj: Index Nazwa Gestosc Flaga: ");
                scanf("%d %99s %lf %c", &index, nazwa, &gestosc, &flaga);
                push_at(list, create_material(nazwa, gestosc, flaga), index);
                break;
            case 5:
                printf("Podaj index do usuniecia: ");
                scanf("%d", &index);
                temp = pop_at(list, index);
                if (temp) {
                    printf("Usunieto: %s\n", temp->material->nazwa);
                    free_node(temp);
                } else printf("Brak elementu.\n");
                break;
            case 6:
                printf("Podaj index do wyszukania: ");
                scanf("%d", &index);
                temp = get_element(list, index);
                if (temp) printf("Znaleziono: %s (%.2lf) [%c]\n", temp->material->nazwa, temp->material->gestosc, temp->material->flaga);
                else printf("Brak elementu.\n");
                break;
            case 7:
                save(list, "baza.txt");
                printf("Zapisano!\n");
                break;
            case 0:
                break;
            default:
                printf("Zly wybor!\n");
        }
    }

    free_list(list);
    return 0;
}
