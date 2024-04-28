/*
Se doreste gestiunea cladirilor din Bucuresti in funtie de anul construirii. 
Acest lucru va ajuta la stabilire riscului seismic al acestora.

1. Sa se creeze o tabela de dispersie pentru stocarea cladirilor din Bucuresti 
(structura Cladire contine ce atribute vreti voi dar va contine obligatoriu anul construirii si un id unic). 
campul folosit pentru clusterizare este anul construirii cladirii.

2. Implementati o functie care afiseaza cladirile dintr-un cluster (construite intr-un an primit ca parametru).

3. Implementati o functie care sterge o cladire pentru care se primeste id-ul si anul construirii.
4. Implementati o functie care sterge o cladire pentru care se primeste doar id-ul cladirii.

5. Observatii diferenta dintre functia implementata la 4 si functia de la 5.

6. Implementati o functie care salveaza intr-un vector toate  cladirile dintr-un an primit ca parametru. 
Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din tabela de dispersie. 
Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.
7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID. Functia primeste 
ca parametri: id-ul cladirii, vechiul an de constructie si noul an de constructie. 
Aveti grija se modifica valoarea atributului folosit pentru clusterizare.
*/

#include <stdio.h>
#include <malloc.h>
typedef struct Cladire Cladire;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

typedef struct Cladire {
	int id;
	char* nume;
	int anConstruire;
}Cladire;

typedef struct Nod {
	Cladire info;
	Nod* next;
}Nod;

typedef struct HashTable {
	Nod** lista;
	int dimensiune;
}HashTable;

int hash(int anConstruire, int dimensiune) {
	int val = 0;
	
	val = anConstruire % dimensiune;
	return val;
}

Cladire init(int id, const char* nume, int anConstruire) {
	Cladire r;
	r.id = id;
	r.nume = malloc(strlen(nume) + 1);
	strcpy_s(r.nume, strlen(nume) + 1, nume);
	r.anConstruire = anConstruire;
	return r;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable hashTable;
	hashTable.dimensiune = dimensiune;
	hashTable.lista = malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		hashTable.lista[i] = NULL;
	}
	return hashTable;
}

void inserareLaFinalLista(Nod** lista, Cladire c) {
	Nod* nod = malloc(sizeof(Nod));
	nod->info = c;
	nod->next = NULL;
	if ((*lista) == NULL) {
		(*lista) = nod;
	}
	else {
		Nod* aux = (*lista);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
}

void inserareCladireInTabela(HashTable hashTable, Cladire c) {
	int hashCode = hash(c.anConstruire, hashTable.dimensiune);
	if (hashTable.lista[hashCode] == NULL) {
		inserareLaFinalLista(&hashTable.lista[hashCode], c);
	}
	else {
		inserareLaFinalLista(&hashTable.lista[hashCode], c);
	}
}

void afisareCladire(Cladire c) {
	printf("\n\tCladirea cu id-ul %d se numeste %s a fost construita in anul %d.", c.id, c.nume, c.anConstruire);
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dimensiune; i++) {
		Nod* aux = ht.lista[i];
		printf("\n\nPozitia %d:", i);
		while (aux)
		{
			afisareCladire(aux->info);
			aux = aux->next;
		}
	}
}

Cladire cautaCladireDupaAnConstruire(HashTable ht, int anConstruire) {
	int hashCode = hash(anConstruire, ht.dimensiune);
	Nod* aux = ht.lista[hashCode];
	while (aux && aux->info.anConstruire!= anConstruire) {
		aux = aux->next;
	}
	if (aux == NULL)
		return init(-1,"Not Found", 0);
	return init(aux->info.id,aux->info.nume, aux->info.anConstruire);
}
void stergeLista(Nod** n) {
	Nod* aux = *n;
	while (aux) {
		free(aux->info.nume);
		Nod* temp = aux->next;
		free(aux);
		aux = temp;
	}
	*n = NULL;
}
void stergeHashTable(HashTable* ht) {
	for (int i = 0; i < ht->dimensiune; i++) {
		stergeLista(&ht->lista[i]);
	}
	free(ht->lista);
	ht->lista = NULL;
	ht->dimensiune = 0;
}

void afisareCladiriDinAnul(HashTable ht, int anConstruire) {
	printf("\n\nCladirile din anul %d:\n", anConstruire);
	int hashCode = hash(anConstruire, ht.dimensiune);
	Nod* aux = ht.lista[hashCode];
	while (aux) {
		if (aux->info.anConstruire == anConstruire) {
			afisareCladire(aux->info);
		}
		aux = aux->next;
	}
}

void stergeCladire(HashTable* ht, int id, int anConstruire) {
	int hashCode = hash(anConstruire, ht->dimensiune);
	Nod* prev = NULL;
	Nod* current = ht->lista[hashCode];
	while (current != NULL) {
		if (current->info.id == id && current->info.anConstruire == anConstruire) {
			if (prev == NULL) { 
				ht->lista[hashCode] = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current->info.nume);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void stergeCladireDupaId(HashTable* ht, int id) {
	for (int i = 0; i < ht->dimensiune; i++) {
		Nod* prev = NULL;
		Nod* current = ht->lista[i];
		while (current != NULL) {
			if (current->info.id == id) {
				if (prev == NULL) {
					ht->lista[i] = current->next;
				}
				else {
					prev->next = current->next;
				}
				free(current->info.nume);
				free(current);
				return;
			}
			prev = current;
			current = current->next;
		}
	}
}

Cladire copiereCladire(const Cladire* sursa) {
	Cladire copie;
	copie.id = sursa->id;
	copie.nume = malloc(strlen(sursa->nume) + 1);
	strcpy(copie.nume, sursa->nume);
	copie.anConstruire = sursa->anConstruire;
	return copie;
}

Cladire* salveazaCladiriDinAnul(HashTable ht, int anConstruire, int* numarCladiri) {
	int hashCode = hash(anConstruire, ht.dimensiune);
	Nod* aux = ht.lista[hashCode];
	int count = 0;
	while (aux) {
		if (aux->info.anConstruire == anConstruire) {
			count++;
		}
		aux = aux->next;
	}

	*numarCladiri = count;
	Cladire* vectorCladiri = malloc(count * sizeof(Cladire));

	int index = 0;
	aux = ht.lista[hashCode];
	while (aux) {
		if (aux->info.anConstruire == anConstruire) {
			vectorCladiri[index] = copiereCladire(&(aux->info));
			index++;
		}
		aux = aux->next;
	}

	return vectorCladiri;
}

void modificaAnConstruire(HashTable* ht, int id, int vechiulAn, int noulAn) {
	for (int i = 0; i < ht->dimensiune; i++) {
		Nod* current = ht->lista[i];
		while (current != NULL) {
			if (current->info.id == id && current->info.anConstruire == vechiulAn) {
				current->info.anConstruire = noulAn;
				return;
			}
			current = current->next;
		}
	}
}

void main() {
	HashTable hashTable = initializareHashTable(5);
	inserareCladireInTabela(hashTable, init(1,"Burj Khalifa", 2000));
	inserareCladireInTabela(hashTable, init(2,"One Business Tower", 2005));
	inserareCladireInTabela(hashTable, init(3,"Cladirea Virgil Madgearu", 1921));
	inserareCladireInTabela(hashTable, init(4,"Turnul Eiffel", 1788));
	inserareCladireInTabela(hashTable, init(5,"Palatul Parlamentului", 1980));
	inserareCladireInTabela(hashTable, init(6,"Mall Afi", 2011));
	afisareHashTable(hashTable);

	printf("\n");

	Cladire c = cautaCladireDupaAnConstruire(hashTable, 2000);
	afisareCladire(c);

	afisareCladiriDinAnul(hashTable, 2005);

	stergeCladire(&hashTable, 1, 2000); 

	printf("\n\nTabela dupa stergere dupa id si anul construirii:\n");
	afisareHashTable(hashTable);

	stergeCladireDupaId(&hashTable, 6);

	printf("\n\nTabela dupa stergere dupa id:\n");
	afisareHashTable(hashTable);

	inserareCladireInTabela(hashTable, init(10, "Turnul Eiffel2", 1788));
	inserareCladireInTabela(hashTable, init(11, "Palatul Parlamentului2", 1980));
	inserareCladireInTabela(hashTable, init(12, "Mall Afi2", 2011));

	int numarCladiri = 0;
	Cladire* cladiri = salveazaCladiriDinAnul(hashTable, 1788, &numarCladiri);
	printf("Numarul de cladiri din anul 1788: %d\n", numarCladiri);
	for (int i = 0; i < numarCladiri; i++) {
		afisareCladire(cladiri[i]);
	}
	free(cladiri);

	modificaAnConstruire(&hashTable, 4, 1788, 2000);
	afisareHashTable(hashTable);
	stergeHashTable(&hashTable);
	printf("\n\nDimensiune tabela dupa stergere: %d", hashTable.dimensiune);
}