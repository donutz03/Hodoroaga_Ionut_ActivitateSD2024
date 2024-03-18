#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Nod {
    int data;
    struct Nod* urmator;
} Nod;



Nod* creare_lista() {

    Nod* prim, * ultim, * curent;
    int n, valoare;


    printf("Introduceti numarul de elemente: ");
    scanf("%d", &n);


    prim = malloc(sizeof(Nod));
    if (prim == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        exit(1);
    }


    printf("Introduceti valoarea primului element: ");
    scanf("%d", &valoare);
    prim->data = valoare;
    prim->urmator = NULL;


    ultim = prim;

    for (int i = 1; i < n; i++) {

        curent = malloc(sizeof(Nod));
        if (curent == NULL) {
            printf("Eroare la alocarea memoriei!\n");
            exit(1);
        }


        printf("Introduceti valoarea elementului %d: ", i);
        scanf("%d", &valoare);
        curent->data = valoare;


        ultim->urmator = curent;
        ultim = curent;
    }

    return prim;
}

void afisare_lista(Nod* lista) {

    Nod* curent = lista;


    while (curent != NULL) {
        printf("%d ", curent->data);
        curent = curent->urmator;
    }


    printf("\n");
}


void sterge_nod(Nod* lista, int poz) {
    Nod* anterior, * curent;
    int i;

    if (poz < 0) {
        printf("Pozitia nu poate fi negativa!\n");
        return;
    }

    anterior = NULL;
    curent = lista;
    for (i = 0; i < poz && curent != NULL; i++) {
        anterior = curent;
        curent = curent->urmator;
    }

    if (curent == NULL) {
        printf("Pozitia %d este invalida!\n", poz);
        return;
    }

    if (anterior == NULL) {
        lista = curent->urmator;
    }
    else {
        anterior->urmator = curent->urmator;
    }

    free(curent);
}

void inserare_sortata(Nod* lista, Nod* nou) {
    Nod* anterior, * curent;

    anterior = NULL;
    curent = lista;
    while (curent != NULL && (curent->data < nou->data)) {
        anterior = curent;
        curent = curent->urmator;
    }

    if (anterior == NULL) {
        nou->urmator = lista;
        lista = nou;
    }
    else {
        anterior->urmator = nou;
        nou->urmator = curent;
    }
}

Nod** salvare_filtrate(Nod* lista, int (*conditie)(Nod*), int* n) {
    Nod* curent;
    Nod** vector;
    int i, count = 0;

    curent = lista;
    while (curent != NULL) {
        if (conditie(curent)) {
            count++;
        }
        curent = curent->urmator;
    }


    *n = count;
    vector = malloc(sizeof(Nod*) * count);


    i = 0;
    curent = lista;
    while (curent != NULL) {
        if (conditie(curent)) {
            vector[i] = malloc(sizeof(Nod));
            memcpy(vector[i], curent, sizeof(Nod));
            i++;
        }
        curent = curent->urmator;
    }

    return vector;
}

void interschimba_elemente(Nod* lista, int poz1, int poz2) {
    Nod* curent1, * anterior1, * curent2, * anterior2;
    Nod* temp;
    int i;

    if (poz1 < 0 || poz2 < 0) {
        printf("Pozitiile nu pot fi negative!\n");
        return;
    }

    anterior1 = NULL;
    curent1 = lista;
    for (i = 0; i < poz1 && curent1 != NULL; i++) {
        anterior1 = curent1;
        curent1 = curent1->urmator;
    }

    anterior2 = NULL;
    curent2 = lista;
    for (i = 0; i < poz2 && curent2 != NULL; i++) {
        anterior2 = curent2;
        curent2 = curent2->urmator;
    }


    if (curent1 == NULL || curent2 == NULL) {
        printf("Pozitiile %d si %d sunt invalide!\n", poz1, poz2);
        return;
    }


    if (anterior1 == NULL) {

        lista = curent2;
    }
    else {
        anterior1->urmator = curent2;
    }

    if (anterior2 == NULL) {

        lista = curent1;
    }
    else {
        anterior2->urmator = curent1;
    }

    temp = curent1->urmator;
    curent1->urmator = curent2->urmator;
    curent2->urmator = temp;
}


int este_par(Nod* nod) {
    return nod->data % 2 == 0;
}

int main() {
    Nod* lista = creare_lista();
    afisare_lista(lista);


    sterge_nod(lista, 2);

    afisare_lista(lista);


    Nod* nou = malloc(sizeof(Nod));
    nou->data = 10;
    nou->urmator = NULL;

    inserare_sortata(lista, nou);

    afisare_lista(lista);

    int n;
    Nod** vector = salvare_filtrate(lista, este_par, &n);

    for (int i = 0; i < n; i++) {
        printf("%d ", vector[i]->data);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(vector[i]);
    }
    free(vector);

    interschimba_elemente(lista, 1, 3);

    afisare_lista(lista);

    return 0;
}
