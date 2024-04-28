/*
Se considera un arbore binar de cautare. 
Puteti sa folositi codul de la seminar. 

Sa se stearga un nod pentru care se primeste id-ul de cautare. 
Dupa stergere arborele trebuie sa isi pastreze proprietatea de Arbore Binar de Cautare.

Sa se implementeze o functie care pentru o radacina primita ca parametru, 
returneaza radacina subarborelui stang sau drept care are inaltimea mai mare.

Sa se realizeze o functie care pentru un nod radacina primit, 
determina numarul de noduri aflate in subordine.

Sa se realizeze o functie care pentru un nod radacina primit ca parametru, 
returneaza radacina subarborelui stang sau drept care are mai multe noduri in subordine.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema
{
	int id;
	int nrFilme;
	char** listaFilme;
};

struct Nod
{
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema c) {
	if (*radacina)
	{
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod;
	}
}

Cinema citireCinema(FILE* f)
{
	Cinema c;
	fscanf(f, "%d", &c.id);
	fscanf(f, "%d", &c.nrFilme);
	if (c.nrFilme != 0) {
		c.listaFilme = (char**)malloc(sizeof(char*) * c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++) {
			char buffer[100];
			fscanf(f, "%s", &buffer);
			c.listaFilme[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(c.listaFilme[i], buffer);
		}
	}
	else {
		c.listaFilme = NULL;
	}
	return c;
}

Nod* citireDinFisier(const char* fisier)
{
	Nod* radacina = NULL;

	if (fisier != NULL && strlen(fisier) > 0)
	{
		FILE* f = fopen(fisier, "r");
		if (f != NULL)
		{
			int dim;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++)
			{
				Cinema cinema;
				cinema = citireCinema(f);
				inserareInArbore(&radacina, cinema);
			}
		}
	}
	return radacina;
}

void afisareCinema(Cinema c)
{
	printf("Cinematograful cu id-ul %d are in derulare %d filme: ", c.id, c.nrFilme);

	for (int i = 0; i < c.nrFilme; i++)
	{
		printf("%s, ", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad)
{
	if (rad)
	{
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInordine(Nod* rad)
{
	if (rad)
	{
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

int calculNrFilmeRedate(Nod* rad)
{
	if (rad)
	{
		int suma = rad->info.nrFilme;
		suma += calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
	}
	else
	{
		return 0;
	}
}

Nod* gasesteMinim(Nod* rad)
{
	while (rad->st != NULL)
	{
		rad = rad->st;
	}
	return rad;
}

Nod* stergeNod(Nod* rad, int id)
{
	if (rad == NULL)
	{
		return rad;
	}
	if (id < rad->info.id)
	{
		rad->st = stergeNod(rad->st, id);
	}
	else if (id > rad->info.id)
	{
		rad->dr = stergeNod(rad->dr, id);
	}
	else
	{
		if (rad->st == NULL)
		{
			Nod* temp = rad->dr;
			free(rad);
			return temp;
		}
		else if (rad->dr == NULL)
		{
			Nod* temp = rad->st;
			free(rad);
			return temp;
		}

		Nod* temp = gasesteMinim(rad->dr);
		rad->info = temp->info;
		rad->dr = stergeNod(rad->dr, temp->info.id);
	}
	return rad;
}

int inaltimeArbore(Nod* rad) {
	if (rad == NULL) {
		return 0;
	}
	else {
		int inaltimeSt = inaltimeArbore(rad->st);
		int inaltimeDr = inaltimeArbore(rad->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
}

Nod* subarboreCuInaltimeMaxima(Nod* rad) {
	if (rad == NULL) {
		return NULL;
	}

	int inaltimeSt = inaltimeArbore(rad->st);
	int inaltimeDr = inaltimeArbore(rad->dr);

	if (inaltimeSt > inaltimeDr) {
		return rad->st;
	}
	else {
		return rad->dr;
	}
}

int numarNoduriSubordine(Nod* rad) {
	if (rad == NULL) return 0;
	if (rad->st == NULL && rad->dr == NULL) {
		return 2;
	}
	else if (rad->st == NULL) {
		return 1;
	}
	else if (rad->dr == NULL) {
		return 1;
	}
	else {
		Nod* st = rad->st;
		Nod* dr = rad->dr;
		int numarSt = numarNoduriSubordine(st);
		int numarDr = numarNoduriSubordine(dr);
		return numarSt + numarDr;
	}
}

Nod* subarboreCuMaiMulteNoduri(Nod* rad) {
	if (rad == NULL) {
		return NULL;
	}

	int numarNoduriSt = numarNoduriSubordine(rad->st);
	int numarNoduriDr = numarNoduriSubordine(rad->dr);

	if (numarNoduriSt > numarNoduriDr) {
		return rad->st;
	}
	else if (numarNoduriDr > numarNoduriSt) {
		return rad->dr;
	}
	else {
		return NULL;
	}
}

void main()
{
	Nod* arbore = NULL;
	arbore = citireDinFisier("cinema.txt");
	afisareArboreInordine(arbore);
	printf("\n\nNr total filme: %d", calculNrFilmeRedate(arbore));
	
	//arbore = stergeNod(arbore, 8);

	//afisareArboreInordine(arbore);
	//printf("\n\nNr total filme: %d", calculNrFilmeRedate(arbore));

	Nod* subarboreMaxim = subarboreCuInaltimeMaxima(arbore);

	printf("\n\nSubarbore cu inaltimea maxima:\n");
	afisareArboreInordine(subarboreMaxim);

	printf("\n\nNumar total de noduri in subordine: %d", numarNoduriSubordine(arbore));
	printf("\n\nNumar total de noduri in subordine pt subarborele maxim: %d", numarNoduriSubordine(subarboreMaxim));

	Nod* subarboreMaiMulteNoduri = subarboreCuMaiMulteNoduri(arbore);
	printf("\n\nSubarbore cu mai multe noduri in subordine:\n");
	afisareArboreInordine(subarboreMaiMulteNoduri);
}