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
void main()
{
	Nod* arbore = NULL;
	arbore = citireDinFisier("cinema.txt");
	afisareArboreInordine(arbore);
	printf("\n\nNr total filme: %d", calculNrFilmeRedate(arbore));
}