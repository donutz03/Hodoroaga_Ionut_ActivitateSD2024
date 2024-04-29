/*
Considerati codul de la task-ul precedent.

Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create. 
Asezarea in fisier a elementelor o faceti la libera alegere.

Scrieti intr-un program C functia care sa citeasca obiectele din fisier si sa le salveze intr-un vector.

Creati o functie care sa copieze (deep copy) elementele din vector intr-o matrice alocată dinamic. 
Asezarea in matrice pe linii a obiectelor o faceti dupa un criteriu aplicat unui atribut. 
Astfel veti obține mai multe clustere reprezentate de liniile matricei.

Scrieti o functie care muta liniile din matrice, astfel incat acestea sa fie sortate dupa numarul de elemente de pe linie.

Scrieti o functie care sa afiseze elementele dintr-o matrice.
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <malloc.h>
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
void afiseazaHainaMatrice(struct Haina h) {
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

struct Haina* copiazaPrimeleNHaine(struct Haina* haine, int nrHaine, int nrHaineCopiate) {
	if (nrHaineCopiate < nrHaine && nrHaineCopiate>0) {
		struct Haina* haineCopiate = (struct Haina*)malloc(sizeof(struct Haina) * nrHaineCopiate);
		for (int i = 0; i < nrHaineCopiate; i++) {
			haineCopiate[i] = initializareHaina(haine[i].marime, haine[i].marca, haine[i].pret, haine[i].gender);
		}
		return haineCopiate;
	}
	else {
		return NULL;
	}
}

struct Haina* concatHaine(struct Haina* haine1, int dimensiune1, struct Haina* haine2, int dimensiune2) {
	struct Haina* haineConcatenate = (struct Haina*)malloc((dimensiune1 + dimensiune2) * sizeof(struct Haina));
	for (int i = 0; i < dimensiune1; i++) {
		haineConcatenate[i] = initializareHaina(haine1[i].marime, haine1[i].marca, haine1[i].pret, haine1[i].gender);
	}
	for (int i = 0; i < dimensiune2; i++) {
		haineConcatenate[dimensiune1 + i] = initializareHaina(haine2[i].marime, haine2[i].marca, haine2[i].pret, haine2[i].gender);
	}
	return haineConcatenate;
}
void citesteFisier(const char* nume_fisier, struct Haina** vector, int* dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator);
				struct Haina haina;
				haina.marime = atoi(token);
				token = strtok(NULL, delimitator);
				haina.marca = (char*)malloc(strlen(token) + 1);
				strcpy(haina.marca, token);
				token = strtok(NULL, delimitator);
				haina.pret = atof(token);
				token = strtok(NULL, delimitator);
				haina.gender = token[0];
				inserareHainaLaFinal(vector, dim, haina);
			}
			fclose(f);
		}
	}
}

void salveazaHaina(const struct Haina h, const char* nume_fisier) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "a");
		if (f != NULL) {
			fprintf(f, "%d,%s,%.2f,%c\n", h.marime, h.marca, h.pret, h.gender);
			fclose(f);
		}
		else {
			printf("Eroare la deschiderea fisierului\n");
		}
	}
	else {
		printf("Numele fisierului invalid\n");
	}
}

void salveazaVectorHaine(struct Haina* vector, int dimensiune, const char* nume_fisier) {
	if (vector != NULL && dimensiune > 0 && nume_fisier != NULL && strlen(nume_fisier) > 0) {
		for (int i = 0; i < dimensiune; i++) {
			salveazaHaina(vector[i], nume_fisier);
		}
	}
	else {
		printf("Vectorul sau numele fisierului sunt invalide\n");
	}
}
struct Haina** copiazaVectorInMatrice(struct Haina* vector, int dimensiune, int* dimLinii, int** dimColoane) {
	char** marciDistincte = (char**)malloc(dimensiune * sizeof(char*));
	if (marciDistincte == NULL) {
		return NULL;
	}

	int numarMarciDistincte = 0;

	for (int i = 0; i < dimensiune; i++) {
		int marcaNoua = 1;
		for (int j = 0; j < numarMarciDistincte; j++) {
			if (strcmp(vector[i].marca, marciDistincte[j]) == 0) {
				marcaNoua = 0;
				break;
			}
		}
		if (marcaNoua) {
			marciDistincte[numarMarciDistincte] = malloc(strlen(vector[i].marca) + 1);
			if (marciDistincte[numarMarciDistincte] == NULL) {
				for (int k = 0; k < numarMarciDistincte; k++) {
					free(marciDistincte[k]);
				}
				free(marciDistincte);
				return NULL;
			}
			strcpy(marciDistincte[numarMarciDistincte], vector[i].marca);
			numarMarciDistincte++;
		}
	}

	*dimLinii = numarMarciDistincte;
	*dimColoane = (int*)malloc(numarMarciDistincte * sizeof(int));
	if (*dimColoane == NULL) {
		for (int k = 0; k < numarMarciDistincte; k++) {
			free(marciDistincte[k]);
		}
		free(marciDistincte);
		return NULL;
	}

	for (int i = 0; i < numarMarciDistincte; i++) {
		(*dimColoane)[i] = 0;
	}
	for (int i = 0; i < dimensiune; i++) {
		for (int j = 0; j < numarMarciDistincte; j++) {
			if (strcmp(vector[i].marca, marciDistincte[j]) == 0) {
				(*dimColoane)[j]++;
				break;
			}
		}
	}

	struct Haina** matrice = (struct Haina**)malloc(numarMarciDistincte * sizeof(struct Haina*));
	if (matrice == NULL) {
		for (int k = 0; k < numarMarciDistincte; k++) {
			free(marciDistincte[k]);
		}
		free(marciDistincte);
		free(*dimColoane);
		return NULL;
	}
	for (int i = 0; i < numarMarciDistincte; i++) {
		matrice[i] = (struct Haina*)malloc((*dimColoane)[i] * sizeof(struct Haina));
		if (matrice[i] == NULL) {
			for (int k = 0; k < numarMarciDistincte; k++) {
				free(marciDistincte[k]);
			}
			free(marciDistincte);
			free(*dimColoane);
			for (int j = 0; j < i; j++) {
				free(matrice[j]);
			}
			free(matrice);
			return NULL;
		}
	}

	for (int i = 0; i < numarMarciDistincte; i++) {
		int indexMatrice = 0;
		for (int j = 0; j < dimensiune; j++) {
			if (strcmp(vector[j].marca, marciDistincte[i]) == 0) {
				matrice[i][indexMatrice++] = vector[j];
			}
		}
	}
	for (int i = 0; i < numarMarciDistincte; i++) {
		free(marciDistincte[i]);
	}
	free(marciDistincte);

	return matrice;
}



void afiseazaMatrice(struct Haina** matrice, int dimLinii, int* dimColoane) {
	for (int i = 0; i < dimLinii; i++) {
		printf("Marca: %s\n", matrice[i][0].marca);
		for (int j = 0; j < dimColoane[i]; j++) {
			afiseazaHainaMatrice(matrice[i][j]);
		}
		printf("\n");
	}
}
void dezalocaMatrice(struct Haina** matrice, int dimLinii) {
	for (int i = 0; i < dimLinii; i++) {
		free(matrice[i]);
	}
	free(matrice);
}

void interschimbaLinii(struct Haina** matrice, int linie1, int linie2) {
	struct Haina* temp = matrice[linie1];
	matrice[linie1] = matrice[linie2];
	matrice[linie2] = temp;
}
void sortareMatrice(struct Haina** matrice, int dimLinii, int* dimColoane) {
	for (int i = 0; i < dimLinii - 1; i++) {
		for (int j = 0; j < dimLinii - i - 1; j++) {
			if (dimColoane[j] > dimColoane[j + 1]) {
				interschimbaLinii(matrice, j, j + 1);
				int temp = dimColoane[j];
				dimColoane[j] = dimColoane[j + 1];
				dimColoane[j + 1] = temp;
			}
		}
	}
}


void main() {
	int dimensiuneVector = 0;
	struct Haina* vectorHaine = (struct Haina*)malloc(dimensiuneVector * sizeof(struct Haina));
	citesteFisier("Haine.txt", &vectorHaine, &dimensiuneVector);
	printf("\nHainele introduse sunt:\n");
	for (int i = 0; i < dimensiuneVector; i++) {
		afiseazaHaina(vectorHaine[i]);
	}

	int dimLinii;
	int* dimColoane;

	struct Haina** matriceHaine = copiazaVectorInMatrice(vectorHaine, dimensiuneVector, &dimLinii, &dimColoane);
	
	printf("Afisare matrice (pe fiecare linie se afla toate hainele de la o marca\n");
	afiseazaMatrice(matriceHaine, dimLinii, dimColoane);

	sortareMatrice(matriceHaine, dimLinii, dimColoane);
	printf("\n\tmatricea dupa ce a fost sortata dupa numarul de elemente de pe fiecare linie: \n");
	afiseazaMatrice(matriceHaine, dimLinii, dimColoane);
	for (int i = 0; i < dimensiuneVector; i++) {
		dezalocareHaina(&vectorHaine[i]);
	}
	dezalocaMatrice(matriceHaine, dimLinii);


	free(vectorHaine);
}