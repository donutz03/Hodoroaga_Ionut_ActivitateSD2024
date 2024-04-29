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

struct Haina* filtrareHaine(struct Haina haine[], int numarHaine, float pretMaxim, char gen, int* dim) {
	int index = 0;
	for (int i = 0; i < numarHaine; i++) {
		if (haine[i].pret <= pretMaxim && haine[i].gender == gen) {
			index++;
		}
	}
	(*dim) = index;
	index = 0;
	if ((*dim) != 0) {

		struct Haina* haineFiltrate = (struct Haina*)malloc((*dim) * sizeof(struct Haina));

		for (int i = 0;i < numarHaine;i++)
		{

			if (haine[i].pret <= pretMaxim && haine[i].gender == gen) {

				haineFiltrate[index].marime = haine[i].marime;
				haineFiltrate[index].marca = (char*)malloc((strlen(haine[i].marca) + 1) * sizeof(char));
				strcpy(haineFiltrate[index].marca, haine[i].marca);
				haineFiltrate[index].pret = haine[i].pret;
				haineFiltrate[index].gender = haine[i].gender;
				index++;
			}
		}
		return haineFiltrate;

	}
	return NULL;
		
}

struct Avion* copiazaPrimeleNHaine(struct Haina* haine, int nrHaine, int nrHaineCopiate) {
		if (nrHaineCopiate < nrHaine && nrHaineCopiate>0) {
			struct Haina* haineCopiate = (struct Haina*)malloc(sizeof(struct Haina) * nrHaineCopiate);
			for (int i = 0; i < nrHaineCopiate; i++) {
				haineCopiate[i] = initializareHaina(haine[i].marime, haine[i].marca, haine[i].pret, haine[i].gender);
			}
			return haine;
		}
		else {
			return NULL;
		}
}

struct Haina* concatHaine(struct Haina* haine1, int dimensiune1, struct Haina* haine2, int dimensiune2) {
	struct Haina* concatenatedHaine = (struct Haina*)malloc((dimensiune1 + dimensiune2) * sizeof(struct Haina));
	for (int i = 0; i < dimensiune1; i++) {
		concatenatedHaine[i] = initializareHaina(haine1[i].marime, haine1[i].marca, haine1[i].pret, haine1[i].gender);
	}
	for (int i = 0; i < dimensiune2; i++) {
		concatenatedHaine[dimensiune1 + i] = initializareHaina(haine2[i].marime, haine2[i].marca, haine2[i].pret, haine2[i].gender);
	}
	return concatenatedHaine;
}


void main() {
	int dimensiuneVector = 0;
	struct Haina* vectorHaine = (struct Haina*)malloc(dimensiuneVector * sizeof(struct Haina));

	struct Haina h1 = initializareHaina(20, "Adidas", 39, 'M');
	struct Haina h2 = initializareHaina(21, "Adidas1", 40, 'F');
	struct Haina h3 = initializareHaina(22, "Adidas2", 41, 'F');
	struct Haina h4 = initializareHaina(23, "Adidas3", 42, 'M');
	struct Haina h5 = initializareHaina(24, "Adidas4", 43, 'F');


	inserareHainaLaFinal(&vectorHaine, &dimensiuneVector, h1);
	inserareHainaLaFinal(&vectorHaine, &dimensiuneVector, h2);
	inserareHainaLaFinal(&vectorHaine, &dimensiuneVector, h3);
	inserareHainaLaFinal(&vectorHaine, &dimensiuneVector, h4);
	inserareHainaLaFinal(&vectorHaine, &dimensiuneVector, h5);

	printf("\nHainele introduse sunt:\n");
	for (int i = 0; i < dimensiuneVector; i++) {
		afiseazaHaina(vectorHaine[i]);
	}

	float pretMaxim = 41.0f;
	char gen = 'F';
	int dimensiuneFiltrate = 0;

	struct Haina* haineFiltrate = filtrareHaine(vectorHaine, dimensiuneVector, pretMaxim, gen, &dimensiuneFiltrate);
	printf("\n\nAfisare vector haine filtrate dupa pret maxim si gen: \n");
	for (int i = 0; i < dimensiuneFiltrate; i++) {
		afiseazaHaina(haineFiltrate[i]);
	}


	int nrHaineCopiate = 3;

	struct Haina* haineCopiate = copiazaPrimeleNHaine(vectorHaine, dimensiuneVector, nrHaineCopiate);

	printf("\n\nAfisare vector primele 3 haine: \n");

	for (int i = 0;i < nrHaineCopiate;i++)
	{
		afiseazaHaina(haineCopiate[i]);
	}

	printf("\n\nHaine concatenate din vectorii haineCopiate si haineFiltrate:\n\n");
	struct Haina* haineConcatenate = concatHaine(haineCopiate, nrHaineCopiate, haineFiltrate, dimensiuneFiltrate);
	for (int i = 0;i < dimensiuneFiltrate + nrHaineCopiate;i++) {
		afiseazaHaina(haineConcatenate[i]);
	}

	for (int i = 0; i < dimensiuneVector; i++) {
		dezalocareHaina(&vectorHaine[i]);
	}

	for (int i = 0; i < dimensiuneFiltrate; i++) {
		dezalocareHaina(&haineFiltrate[i]);
	}

	for (int i = 0; i < nrHaineCopiate; i++) {
		dezalocareHaina(&haineCopiate[i]);
	}
	free(vectorHaine);
	free(haineFiltrate);
}