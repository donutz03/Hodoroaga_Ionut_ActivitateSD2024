/*
Se consideră prima literă din numele vostru, și prima literă din prenumele vostru.

Sa se construiască un articol care să conțină cele două litere.



Exemplu: Alin Zamfiroiu ->A si Z. Articolul Magazin:

struct Magazin{

int cod;

char* denumire;

int nrProduse;

float *preturi;

}



Articolul trebuie să aibă logica. Articolul trebuie sa fie un substantiv. 
Articolul trebuie sa aibă cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.

Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de voi. 
Funcția returnează obiectul citit.

Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. 
(o medie sau o suma, un maxim, un minim...sau orice altceva)

Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp. 
noua valoare este primita ca parametru.

Realizați o funcție care afișează un obiect de tipul creat. 
Afișarea se face la console, și sunt afișate toate informațiile.
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
void dezalocareHaina(struct Haina *h) {
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

void main() {
	struct Haina haina1;
	haina1.marime = 33;
	haina1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1));
	strcpy(haina1.marca, "Nike");
	haina1.pret = 45;
	haina1.gender = 'M';

	afiseazaHaina(haina1);
	struct Haina haina2 = initializareHaina(27, "Addidas", 23.6, 'F');

	afiseazaHaina(haina2);
	struct Haina haina3;
	haina3 = citesteHaina();
	afiseazaHaina(haina3);

	struct Haina haine[] = {
		{33, "Nike", 45, 'M'},
		{27, "Adidas", 23.6, 'F'},
		{30, "Puma", 35.8, 'M'}
	};
	int numarHaine = sizeof(haine) / sizeof(haine[0]);

	printf("Pretul total al hainelor este: %.2f\n", calcularePretTotal(haine, numarHaine));

	modificaPret(&haina1, 50.3f);
	printf("\n\nHaina 1 dupa modificare pret:\n");
	afiseazaHaina(haina1);

	dezalocareHaina(&haina1);
	dezalocareHaina(&haina2);
	dezalocareHaina(&haina3);


}
