#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct CafeneaMea Cafenea;

struct CafeneaMea
{
    char* nume;
    int nrLocuri;
    float suprafata;
};

typedef struct Nod Nod;

struct Nod
{
    Cafenea info;
    Nod* next;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea c;
    c.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(c.nume, nume);
    c.nrLocuri = nrLocuri;
    c.suprafata = suprafata;
    return c;
}

Nod* inserareInceput(Cafenea c, Nod* cap) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
    return nou;
}

void afisareCafenea(Cafenea c) {
    printf("\nCafeneaua se numeste %s, are %d locuri si are o suprafata de %5.2f", c.nume, c.nrLocuri, c.suprafata);
}

void afisareCafenele(Nod* cap) {
    while (cap != NULL) {
        afisareCafenea(cap->info);
        cap = cap->next;
    }
}

//numele cafenelei cu densitatea cea mai mica
char* numeCafeneaDensitateMinima(Nod* cap) {

    if (cap != NULL) {
        float minimDensitate = cap->info.nrLocuri / cap->info.suprafata;
        char* numeMinimDensitate = (char*)malloc(sizeof(char) * (strlen(cap->info.nume) + 1));
        strcpy(numeMinimDensitate, cap->info.nume);
        float densitate;
        cap = cap->next;
        while (cap != NULL) {
            if (cap->info.suprafata != 0) {
                densitate = cap->info.nrLocuri / cap->info.suprafata;
                if (densitate < minimDensitate)
                {
                    minimDensitate = densitate;
                    free(numeMinimDensitate);
                    numeMinimDensitate = (char*)malloc(sizeof(char) * (strlen(cap->info.nume) + 1));
                    strcpy(numeMinimDensitate, cap->info.nume);
                }

            }
            cap = cap->next;
        }
        return numeMinimDensitate;
    }
}

void stergeLista(Nod** nod) {


    while ((*nod) != NULL) {
        Nod* aux = *nod;
        (*nod) = (*nod)->next;
        free(aux->info.nume);
        free(aux);

    }
    (*nod) = NULL;
}

void inserareFinal(Nod** lista, Cafenea c) {
    if ((*lista) == NULL) {
        (*lista) = inserareInceput(c,*lista);
    }
    else {
        Nod* curent = (*lista);
        while (curent->next!=NULL) {
            curent = curent->next;
        }
        Nod* n = (Nod*)malloc(sizeof(Nod));
        n->info = initializareCafenea(c.nume,c.nrLocuri,c.suprafata);
        n->next = NULL;
        curent->next = n;
    }
}
void main()
{
    Nod* cap = NULL;
    Cafenea c = initializareCafenea("Maria", 10, 2.0);
    Cafenea c2 = initializareCafenea("Marcela", 9, 3.0);


    Cafenea c3 = initializareCafenea("Miruna", 8, 4.0);
    cap = inserareInceput(c, cap);
    cap = inserareInceput(c2, cap);
    cap = inserareInceput(c3, cap);
    printf("\nAfisare cafenea individuala: \n");
    afisareCafenea(c);
    printf("\nAfisare lista cafenele: \n");
    afisareCafenele(cap);
    char* numeMinim = numeCafeneaDensitateMinima(cap);
    printf("\nCafenea cu densitate minima: %s", numeMinim);
    stergeLista(&cap);
    afisareCafenele(cap);
    inserareFinal(&cap, c);
    printf("\nAfisare dupa inserare final: \n");
    afisareCafenele(cap);

    stergeLista(&cap);
    printf("\ndupa stergere lista: \n");
    afisareCafenele(cap);

    free(c.nume);
    c.nume = NULL;
    
    free(c2.nume);
    c2.nume = NULL;
    
    free(c3.nume);
    c3.nume = NULL;
    
    free(numeMinim);
    numeMinim = NULL;
}
