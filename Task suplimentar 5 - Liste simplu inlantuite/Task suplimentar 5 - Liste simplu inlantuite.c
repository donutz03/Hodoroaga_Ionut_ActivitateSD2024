/*
Obiectele pe car ele cititi dintr-un fisier le salvati intr-o lista simplu inlantuita.

1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. 
Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea.
2. Implementati o functie care sa insereze elementele in cadrul listei simplu 
inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
3. Implementati o functie care salveaza intr-un vector toate obiectele care indeplinesc o conditie stabilita de voi. 
Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din lista. 
Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.
4. Implementati o functie care primeste lista si doua pozitii. 
In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Librarie Librarie;
typedef struct Nod Nod;

struct Librarie
{
	char* nume;
	int nr_carti;
	float suprafata;

};

struct Nod
{
	Librarie info;
	Nod* next;

};




Librarie initializeazaLibrarie(const char* nume, int nr_carti, float suprafata) {
	Librarie l;
	l.nr_carti = nr_carti;
	l.suprafata = suprafata;
	l.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(l.nume, nume);
	return l;
}

Nod* inserareInceput(Nod* cap, Librarie l)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializeazaLibrarie(l.nume, l.nr_carti, l.suprafata);
	nou->next = cap;
	return nou;
}

void afisareLibrarie(Librarie l) {
	printf("Libraria %s are %d carti si suprafata de %f mp\n", l.nume, l.nr_carti, l.suprafata);
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisareLibrarie(cap->info);
		cap = cap->next;
	}
}

void inserareFinal(Nod** primNod, Librarie l)
{
	if (*primNod != NULL)
	{
		Nod* aux = *primNod;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}

		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = l;
		nou->next = NULL;
		aux->next = nou;
	}
	else 
	{
		*primNod = malloc(sizeof(Nod));
		(*primNod)->info = l;
		(*primNod)->next = NULL;
	}	
}

Nod* citesteListaFisier(const char* numeFisier, Nod* l) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL) {
			char buffer[500];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				Librarie c;
				token = strtok(buffer, delimitator);
				c.nume = (char*)malloc(strlen(token) + 1);
				strcpy(c.nume, token);
				token = strtok(NULL, delimitator);
				c.nr_carti = atoi(token);
				token = strtok(NULL, delimitator);
				c.suprafata = atof(token);
				l = inserareInceput(l, c);
			}
			fclose(f);
		}
	}
	return l;
}

void stergeNod(Nod** cap, int index) {
	if (*cap == NULL) {
		return;
	}

	int lungimeLista = 0;
	Nod* current = *cap;
	while (current != NULL) {
		lungimeLista++;
		current = current->next;
	}

	if (index < 0 || index >= lungimeLista) {
		return;
	}

	if (index == 0) {
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.nume);
		free(temp);
		return;
	}

	Nod* prev = NULL;
	current = *cap;
	int count = 0;
	while (current != NULL && count != index) {
		prev = current;
		current = current->next;
		count++;
	}

	prev->next = current->next;
	free(current->info.nume);
	free(current);
}

void inserareSortata(Nod** cap, Librarie l) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = l;
	nou->next = NULL;
	if (*cap == NULL || (*cap)->info.suprafata >= l.suprafata) {
		nou->next = *cap;
		*cap = nou;
		return;
	}
	Nod* temp = *cap;
	while (temp->next != NULL && temp->next->info.suprafata < l.suprafata) {
		temp = temp->next;
	}
	nou->next = temp->next;
	temp->next = nou;
}

Librarie* salveazaObiecteVector(Nod* cap, int nr_carti_min, float suprafata_min, int* numar_elemente) {
	int count = 0;
	Nod* current = cap;
	while (current != NULL) {
		if (current->info.nr_carti > nr_carti_min && current->info.suprafata > suprafata_min) {
			count++;
		}
		current = current->next;
	}
	Librarie* vector = (Librarie*)malloc(count * sizeof(Librarie));
	if (vector == NULL) {
		*numar_elemente = 0;
		return NULL; 
	}
	int index = 0;
	current = cap;
	while (current != NULL) {
		if (current->info.nr_carti > nr_carti_min && current->info.suprafata > suprafata_min) {
			vector[index].nume = (char*)malloc((strlen(current->info.nume) + 1) * sizeof(char));
			strcpy(vector[index].nume, current->info.nume);
			vector[index].nr_carti = current->info.nr_carti;
			vector[index].suprafata = current->info.suprafata;
			index++;
		}
		current = current->next;
	}
	*numar_elemente = count;
	return vector;
}

void interschimbaElemente(Nod** cap, int pozitie1, int pozitie2) {
	if (pozitie1 == pozitie2) {
		return;
	}
	if (*cap == NULL) {
		return;
	}
	Nod* prev1 = NULL, * current1 = *cap;
	int count1 = 0;
	while (current1 != NULL && count1 != pozitie1) {
		prev1 = current1;
		current1 = current1->next;
		count1++;
	}
	Nod* prev2 = NULL, * current2 = *cap;
	int count2 = 0;
	while (current2 != NULL && count2 != pozitie2) {
		prev2 = current2;
		current2 = current2->next;
		count2++;
	}

	if (current1 == NULL || current2 == NULL) {
		return;
	}
	if (prev1 == NULL) {
		*cap = current2;
	}
	else {
		prev1->next = current2;
	}
	if (prev2 == NULL) {
		*cap = current1;
	}
	else {
		prev2->next = current1;
	}

	Nod* temp = current1->next;
	current1->next = current2->next;
	current2->next = temp;
}



void main() {
	Nod* cap = NULL;
	
	
	cap = citesteListaFisier("Librarii.txt", cap);

	afisareLista(cap);

	printf("\n\n\t se sterge\n\n");
	int pozitieDeSters = 2; 
	stergeNod(&cap, pozitieDeSters);
	afisareLista(cap);
	Librarie l = initializeazaLibrarie("LibrarieNoua", 200, 150.0f);
	inserareSortata(&cap, l);
	printf("\n\n\t Dupa inserarea sortata:\n\n");
	afisareLista(cap);

	int numar_elemente;
	Librarie* vector = salveazaObiecteVector(cap, 20, 30.0f, &numar_elemente);

	printf("\n\nObiectele care indeplinesc au nr carti mai mare de 20 si suprafata mai mare de 30.0 mp:\n");
	for (int i = 0; i < numar_elemente; i++) {
		afisareLibrarie(vector[i]);
	}

	for (int i = 0; i < numar_elemente; i++) {
		free(vector[i].nume);
	}
	free(vector);

	int pozitie1 = 1;
	int pozitie2 = 3;
	printf("\nInterschimbare elemente de pe pozitiile %d si %d:\n", pozitie1, pozitie2);
	interschimbaElemente(&cap, pozitie1, pozitie2);

	printf("\nLista dupa interschimbare:\n");
	afisareLista(cap);

	while (cap) {
		Nod* p = cap->next;
		free(cap->info.nume);
		free(cap);
		cap = p;
	}
}


