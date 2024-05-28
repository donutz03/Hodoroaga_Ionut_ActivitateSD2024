#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema {
	int id;
	int nrFilme;
	char** filme;
};
struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};

//Cinema initCinema(int id, )


Cinema citesteCinema(FILE* f) {
	Cinema c;
	fscanf(f, "%d%d", &c.id, &c.nrFilme);
	if (c.nrFilme > 0) {
		c.filme = (char*)malloc(c.nrFilme * sizeof(char));
		for (int j = 0; j < c.nrFilme; j++) {
			char buffer[100];
			fscanf(f, "%s", &buffer);
			c.filme[j] = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(c.filme[j], buffer);
		}
	}
	else {
		c.filme = NULL;
	}
	return c;

}

void afisareCinema(Cinema c) {
	printf("Cinematograful cu ID ul %d are in derulare %d filme: ", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++)
		printf("%s, ", c.filme[i]);
	printf("\n");
}

void afisarePreOrdine(Nod* rad) {
	if (rad) {
		afisareCinema(rad->info);
		afisarePreOrdine(rad->st);
		afisarePreOrdine(rad->dr);
	}
}
void afisareInOrdine(Nod* rad) {
	if (rad) {
		afisareInOrdine(rad->st);
		afisareCinema(rad->info);
		afisareInOrdine(rad->dr);
	}
}
void afisarePostOrdine(Nod* rad) {
	if (rad) {
		afisarePostOrdine(rad->st);
		afisarePostOrdine(rad->dr);
		afisareCinema(rad->info);
	}
}

int nrTotalFilme(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		suma += nrTotalFilme(rad->st);
		suma += nrTotalFilme(rad->dr);
		return suma;
	}
	return 0;
}

Nod* rotireDreapta(Nod* rad) {
	if(rad)
	{
		Nod* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;
		return aux;
	}
	else {
		return rad;
	}
}

Nod* rotireStanga(Nod* rad) {
	if (rad) {
		Nod* aux = rad->dr;
		rad->dr = aux->st;
		aux->st = rad;
		return aux;
	}
	else {
		return rad;
	}
}

int calculInatlime(Nod* rad) {
	if (rad != NULL)
	{
		int inaltimeSt = calculInatlime(rad->st);
		int inaltimeDr = calculInatlime(rad->dr);
		if (inaltimeSt > inaltimeDr) {
			return 1+inaltimeSt;
		}
		return 1+inaltimeDr;
	}
	else
		return 0;
}

int calculGradEchilibru(Nod* rad) {
	int inaltimeSubarboreStang = calculInatlime(rad->st);
	int inaltimeSubarboreDrept = calculInatlime(rad->dr);
	return inaltimeSubarboreStang - inaltimeSubarboreDrept;
}

void insertArbore(Nod** radacina, Cinema c) {
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			insertArbore(&((*radacina)->st), c);
		}
		else {
			insertArbore(&((*radacina)->dr), c);
		}
		int grad = calculGradEchilibru(*(radacina));
		if (grad == 2) {
			int gradCopil = calculGradEchilibru((*radacina)->st);
			if (gradCopil==-1) { //situatia complexa
				(*radacina)->st = rotireDreapta((*radacina)->st);
			}
			*radacina = rotireDreapta((*radacina));
		}
		else if (grad == -2) {
			int gradCopil = calculGradEchilibru((*radacina)->st);
			if (gradCopil == -1) { //situatia complexa
				(*radacina)->st = rotireDreapta((*radacina)->st);
			}
			*radacina = rotireStanga((*radacina));
		}
	}
	else {
		Nod* nou = malloc(sizeof(Nod));
		nou->info = c;
		nou->st = NULL;
		nou->dr = NULL;
		*radacina = nou;
	}
}

Nod* citesteFisier(const char* fisier) {
	Nod* radacina = NULL;
	if (fisier != NULL && strlen(fisier) > 0) {
		FILE* f = fopen(fisier, "r");
		if (f != NULL) {
			int dim = 0;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++) {
				Cinema c;
				c = citesteCinema(f);
				insertArbore(&radacina, c);
			}
		}
	}
	return radacina;
}

void stergereArbore(Nod** rad) {
	if (*rad) {
		stergereArbore(&((*rad)->st));
		stergereArbore(&((*rad)->dr));
		if ((*rad)->info.filme)
			for (int i = 0; i < (*rad)->info.nrFilme; i++) {
				free((*rad)->info.filme[i]);
			}
			free((*rad)->info.filme);
			free((*rad));
		(*rad) = NULL;
	}
}

Cinema calculCinemaCuNrMax(Nod* rad) {
	if (rad) {
		Cinema cinemaStanga = calculCinemaCuNrMax(rad->st);
		Cinema cinemaDreapta = calculCinemaCuNrMax(rad->dr);
		Cinema max;
		if (rad->info.nrFilme > cinemaStanga.nrFilme && rad->info.nrFilme > cinemaDreapta.nrFilme) {
			max = rad->info;
		}
		else if (cinemaStanga.nrFilme > cinemaDreapta.nrFilme) {
			max = cinemaStanga;
		}
		else {
			max = cinemaDreapta;
		}
		return max;
	}
	else {
		Cinema c;
		c.filme = NULL;
		c.nrFilme = 0;
		c.id = -1;
		return c;
	}
}

void main() {
	Nod* arbore = NULL;
	arbore = citesteFisier("cinema.txt");
	printf("AFISARE PRE ORDINE\n");
	afisarePreOrdine(arbore);
	printf("\n\n");
	printf("AFISARE IN ORDINE\n");
	afisareInOrdine(arbore);
	printf("\n\n");
	printf("AFISARE POST ORDINE\n");
	afisarePostOrdine(arbore);
	printf("\n\n");

	printf("%d\n", nrTotalFilme(arbore));
}
