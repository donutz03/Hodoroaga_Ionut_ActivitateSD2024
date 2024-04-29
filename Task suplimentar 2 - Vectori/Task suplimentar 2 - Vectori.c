/*
Considerati codul de la task-ul precedent.

Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre.

Realizati o functie care va creea un nou vector în care va copia dintr-un vector primit ca parametru 
obiectele care indeplinesc o anumita conditie. Stabiliti voi conditia in functie de un atribut sau doua atribute.

Realizati o functie care muta intr-un nou vector obiectele care indeplinesc o alta conditie fata de cerinta precedenta.

Realizati o functie care concateneaza doi vectori.



Realizati o functie care afiseaza un vector cu obiecte.



Apelati toate aceste functii in main().
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
struct Haina {
	int marime;
	char* marca;
	float pret;
	char gender;
};

struct Haina initializareHaina(int marime, const char* marca, float pret, char gen) {
	struct Haina h;
	h.marime = marime;
	if (marca != NULL && strlen(marca) > 0) {
		h.marca = malloc(strlen(marca) + 1);
		strcpy(h.marca, marca);
	}
	else {
		h.marca = NULL;
	}
	h.pret = pret;
	h.gender = gen;
	return h;
}

void afiseazaHaina(struct Haina h) {
	if (h.marca != NULL) {
		printf("Marca: %s\n", h.marca);
	}
	printf("Marime: %d\n", h.marime);
	printf("Pret: %5.2f\n", h.pret);
	printf("Gen:%c\n\n", h.gender);
}
void dezalocareHaina(struct Haina* h) {
	free(h->marca);
	(*h).marca = NULL;
}

struct Haina citesteHaina() {
	struct Haina h;

	printf("Introduceti marimea: ");
	scanf("%d", &h.marime);
	printf("Introduceti marca: ");
	char marca[100];
	scanf("%s", marca);
	h.marca = malloc(strlen(marca) + 1);
	strcpy(h.marca, marca);
	printf("Introduceti pretul: ");
	scanf("%f", &h.pret);
	printf("Introduceti genul ('M' sau 'F'): ");
	scanf(" %c", &h.gender);
	return h;
}

float calcularePretTotal(struct Haina haine[], int numarHaine) {
	float pretTotal = 0;
	for (int i = 0; i < numarHaine; i++) {
		pretTotal += haine[i].pret;
	}
	return pretTotal;
}

void modificaPret(struct Haina* h, float noulPret) {
	h->pret = noulPret;
}

void inserareHainaLaFinal(struct Haina** vectorHaine, int* dimensiuneVector, struct Haina hainaNoua) {
	struct Haina* nouVector = (struct Haina*)malloc((*dimensiuneVector + 1) * sizeof(struct Haina));
	for (int i = 0; i < *dimensiuneVector; i++) {
		nouVector[i] = (*vectorHaine)[i];
	}
	nouVector[*dimensiuneVector] = hainaNoua;
	free(*vectorHaine);
	*vectorHaine = nouVector;
	(*dimensiuneVector)++;
}


void main() {
	int dimensiuneVector = 5;
	struct Haina* vectorHaine = (struct Haina*)malloc(dimensiuneVector * sizeof(struct Haina));

	struct Haina h1 = initializareHaina(20, "Adidas", 39, 'M');
	struct Haina h2 = initializareHaina(21, "Adidas1", 40, 'F');
	struct Haina h3 = initializareHaina(22, "Adidas2", 41, 'F');
	struct Haina h4 = initializareHaina(23, "Adidas3", 42, 'M');
	struct Haina h5 = initializareHaina(24, "Adidas4", 43, 'F');


	for (int i = 0; i < dimensiuneVector; i++) {
		printf("Introduceti detaliile pentru haina %d:\n", i + 1);
		
	}

	printf("\nHainele introduse sunt:\n");
	for (int i = 0; i < dimensiuneVector; i++) {
		afiseazaHaina(vectorHaine[i]);
	}

	for (int i = 0; i < dimensiuneVector; i++) {
		dezalocareHaina(&vectorHaine[i]);
	}
	free(vectorHaine);


}