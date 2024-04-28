/*
Obiectele pe care le cititi dintr-un fisier tecxt le salvati intr-o lista dublu inlantuita.
1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. 
Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea;

2. Implementati o functie care sa insereze elementele in cadrul listei dublu 
inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra;

3. Realizati parcurgerile pentru lista dublu inlantuita, astfel incat sa afiseze 
elementele sortate crescator dar si sortate descrescator;

4. Implementati o functie care salveaza intr-o lista simplu inlantuita toate obiectele 
care indeplinesc o conditie stabilita de voi. Realizati deep copy, astfel incat elementele 
din listasimplu inlantuita sa fie diferite de cele din lista dublu inlantuita. 
Observati diferenta dintre utilizarea de lista inlantuita si vector (task-ul precedent);

5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii. 
In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii 
din lista primita. Interschimbati informatiile utile din cele doua noduri.

*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>
#include<string.h>
#include<stdlib.h>
typedef struct CafeneaMea Cafenea;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;
typedef struct NodSimplu NodSimplu;
typedef struct ListaSimpla ListaSimpla;

struct CafeneaMea
{
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea cafenea;
    Nod* anterior;
    Nod* urmator;
};

struct NodSimplu {
    Cafenea cafenea;
    NodSimplu* urmator;
};

struct ListaDubla {
    Nod* cap;
    Nod* coada;
};

struct ListaSimpla {
    NodSimplu* cap;
};



Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata)
{
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}

ListaDubla inserareInceput(ListaDubla l, Cafenea c)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));

    nou->cafenea = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
    nou->urmator = l.cap;
    nou->anterior = NULL;

    if (l.cap != NULL)
    {
        l.cap->anterior = nou;
        l.cap = nou;		
    }
    else
    {
        l.cap = l.coada = nou;
    }

    return l;
}


void afisareCafenea(Cafenea c)
{
    printf("\nDenumire: %s Nr scaune: %i Suprafata %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareLista(ListaDubla listaDubla) {
    Nod* nod = listaDubla.cap;
    while (nod) {
        afisareCafenea(nod->cafenea);
        nod = nod->urmator;
    }
    printf("\n\n");
}


ListaDubla stergeLista(ListaDubla listaDubla) {
    while (listaDubla.cap != NULL) {
        free(listaDubla.cap->cafenea.nume);
        Nod* temp = listaDubla.cap;
        listaDubla.cap = listaDubla.cap->urmator;
        free(temp);
    }
    listaDubla.cap = NULL;
    listaDubla.coada = NULL;
    return listaDubla;
}


ListaDubla citesteListaDublaFisier(const char* numeFisierStudenti, ListaDubla l) {
    if (numeFisierStudenti != NULL && strlen(numeFisierStudenti) > 0) {
        FILE* f = fopen(numeFisierStudenti, "r");
        if (f != NULL) {
            char buffer[100];
            char delimitator[] = ",\n";
            while (fgets(buffer, 100, f) != NULL) {
                char* token;
                Cafenea c;
                token = strtok(buffer, delimitator);
                c.nume = (char*)malloc(strlen(token) + 1);
                strcpy(c.nume, token);
                token = strtok(NULL, delimitator);
                c.nrLocuri = atoi(token);
                token = strtok(NULL, delimitator);
                c.suprafata = atof(token);
                l = inserareInceput(l, c);
            }
            fclose(f);
        }
    }
    return l;
}

ListaDubla stergeNodPozitie(ListaDubla listaDubla, int pozitie) {
    if (pozitie < 1) {
        return listaDubla;
    }
    if (listaDubla.cap == NULL) {
        return listaDubla;
    }
    Nod* nodCurent = listaDubla.cap;
    int index = 1;
    while (nodCurent != NULL && index < pozitie) {
        nodCurent = nodCurent->urmator;
        index++;
    }
    if (nodCurent == NULL) {
        return listaDubla;
    }
    if (nodCurent->anterior != NULL) {
        nodCurent->anterior->urmator = nodCurent->urmator;
    }
    else {
        listaDubla.cap = nodCurent->urmator;
    }
    if (nodCurent->urmator != NULL) {
        nodCurent->urmator->anterior = nodCurent->anterior;
    }
    else {
        listaDubla.coada = nodCurent->anterior;
    }
    free(nodCurent->cafenea.nume);
    free(nodCurent);
    return listaDubla;
}

ListaDubla inserareSortata(ListaDubla l, Cafenea c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->cafenea = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);

    if (l.cap == NULL) {
        nou->anterior = NULL;
        nou->urmator = NULL;
        l.cap = l.coada = nou;
        return l;
    }

    Nod* nodCurent = l.cap;
    while (nodCurent != NULL && nodCurent->cafenea.nrLocuri < c.nrLocuri) {
        nodCurent = nodCurent->urmator;
    }

    if (nodCurent == l.cap) {
        nou->urmator = l.cap;
        nou->anterior = NULL;
        l.cap->anterior = nou;
        l.cap = nou;
    }
    else if (nodCurent == NULL) {
        nou->urmator = NULL;
        nou->anterior = l.coada;
        l.coada->urmator = nou;
        l.coada = nou;
    }
    else {
        nou->urmator = nodCurent;
        nou->anterior = nodCurent->anterior;
        nodCurent->anterior->urmator = nou;
        nodCurent->anterior = nou;
    }

    return l;
}

void afisareListaSortataCrescator(ListaDubla listaDubla) {
    Nod* nod = listaDubla.cap;
    while (nod != NULL) {
        afisareCafenea(nod->cafenea);
        nod = nod->urmator;
    }
    printf("\n");
}

void afisareListaSortataDescrescator(ListaDubla listaDubla) {
    Nod* nod = listaDubla.coada;
    while (nod != NULL) {
        afisareCafenea(nod->cafenea);
        nod = nod->anterior;
    }
    printf("\n");
}

ListaSimpla inserareSimpla(ListaSimpla lista, Cafenea c) {
    NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
    nou->cafenea = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
    nou->urmator = lista.cap;
    lista.cap = nou;
    return lista;
}

ListaSimpla copiereListaDublaInSimpla(ListaDubla listaDubla, int nrLocuri, float suprafata) {
    ListaSimpla listaSimpla;
    listaSimpla.cap = NULL;

    Nod* nod = listaDubla.cap;
    while (nod != NULL) {
        if (nod->cafenea.nrLocuri > nrLocuri && nod->cafenea.suprafata > suprafata) {
            listaSimpla = inserareSimpla(listaSimpla, nod->cafenea);
        }
        nod = nod->urmator;
    }

    return listaSimpla;
}

void afisareListaSimpla(ListaSimpla listaSimpla) {
    NodSimplu* nod = listaSimpla.cap;
    while (nod) {
        afisareCafenea(nod->cafenea);
        nod = nod->urmator;
    }
    printf("\n\n");
}

void interschimbareNoduri(ListaDubla lista, int pozitie1, int pozitie2) {
    if (pozitie1 == pozitie2) {
        return;
    }

    if (pozitie1 < 1 || pozitie2 < 1) {
        return;
    }

    Nod* nod1 = lista.cap;
    Nod* nod2 = lista.cap;
    int index = 1;

    while (nod1 != NULL && index < pozitie1) {
        nod1 = nod1->urmator;
        index++;
    }

    index = 1;
    while (nod2 != NULL && index < pozitie2) {
        nod2 = nod2->urmator;
        index++;
    }
    if (nod1 == NULL || nod2 == NULL) {
        return;
    }
    Cafenea temp = nod1->cafenea;
    nod1->cafenea = nod2->cafenea;
    nod2->cafenea = temp;
}



void main()
{
    Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea2 = initializareCafenea("Teds", 17, 17.3);
    Cafenea cafenea3 = initializareCafenea("Urban", 65, 33);
    Cafenea sb = initializareCafenea("Sb", 25, 43);
    ListaDubla listaDubla;
    listaDubla.cap = NULL;
    listaDubla.coada = NULL;
    listaDubla = inserareInceput(listaDubla, cafenea);
    listaDubla = inserareInceput(listaDubla, cafenea2);
    listaDubla = inserareInceput(listaDubla, cafenea3);
    listaDubla = inserareInceput(listaDubla, sb);
    afisareLista(listaDubla);
    listaDubla = stergeLista(listaDubla);
    listaDubla = citesteListaDublaFisier("Cafenele.txt", listaDubla);
    afisareLista(listaDubla);
    listaDubla = stergeNodPozitie(listaDubla, 2);
    printf("\n\nAfisare lista dubla dupa stergere nodul de pe pozitia 2 (Urban):\n\n ");
    afisareLista(listaDubla);
    ListaDubla listaDublaSortata;
    listaDublaSortata.cap = NULL;
    listaDublaSortata.coada = NULL;
    listaDublaSortata = inserareSortata(listaDublaSortata, cafenea);
    listaDublaSortata = inserareSortata(listaDublaSortata, cafenea2);
    listaDublaSortata = inserareSortata(listaDublaSortata, cafenea3);
    listaDublaSortata = inserareSortata(listaDublaSortata, sb);
    printf("\n\nLista dubla sortata dupa numarul de locuri este: \n\n");
    afisareLista(listaDublaSortata);

    printf("\n\tAfisare lista sortata crescator");
    afisareListaSortataCrescator(listaDublaSortata);

    printf("\n\tAfisare lista sortata descrescator");
    afisareListaSortataDescrescator(listaDublaSortata);

    ListaSimpla listaSimpla = copiereListaDublaInSimpla(listaDublaSortata, 20,30);
    printf("Lista simpla obtinuta dupa copierea elementelor din lista dubla \ncu nrLocuri > 20 si suprafata >30:\n");
    afisareListaSimpla(listaSimpla);

    printf("\n\nIntereschanbare: \n\n");
    interschimbareNoduri(listaDublaSortata, 2, 3); 
    afisareLista(listaDublaSortata);
}