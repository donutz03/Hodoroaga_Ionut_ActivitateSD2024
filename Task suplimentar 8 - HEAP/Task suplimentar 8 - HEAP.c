#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

struct Pacient
{
	int gradUrgenta; 
	char* nume;
};

struct Heap
{
	struct Pacient* pacienti;
	int dimTotala;
	int dimNrelemente;
};

struct Pacient initializarePacient(int gradUrgenta, const char* nume)
{
	struct Pacient m;
	m.gradUrgenta = gradUrgenta; 
	if (nume != NULL)
	{
		m.nume = malloc(strlen(nume) + 1);
		strcpy_s(m.nume, strlen(nume) + 1, nume);
	}

	return m;
}

void afisarePacient(struct Pacient m)
{
	printf("Pacient-ul %s are gradul de urgenta %d\n", m.nume, m.gradUrgenta);
}

struct Heap initializareHeap(int dimensiune)
{
	struct Heap aux;
	aux.dimTotala = dimensiune;
	aux.dimNrelemente = 0;
	aux.pacienti = malloc(sizeof(struct Pacient) * aux.dimTotala);
	return aux;
}
void afiseazaHeapUtilizat(struct Heap list)
{
	for (int i = 0; i < list.dimNrelemente; i++)
	{
		afisarePacient(list.pacienti[i]);
	}
}
void afiseazaHeapTotal(struct Heap list)
{
	for (int i = 0; i < list.dimTotala; i++)
	{
		afisarePacient(list.pacienti[i]);
	}
}

void FiltrareHeap(struct Heap heap, int index) {
	int indexMax = index;
	int indexStang = 2 * index + 1;
	int indexDreapta = 2 * index + 2;

	if (index < heap.dimNrelemente && indexStang < heap.dimNrelemente && heap.pacienti[indexStang].gradUrgenta < heap.pacienti[indexMax].gradUrgenta) {
		indexMax = indexStang;
	}

	if (index < heap.dimNrelemente && indexDreapta < heap.dimNrelemente && heap.pacienti[indexDreapta].gradUrgenta < heap.pacienti[indexMax].gradUrgenta) {
		indexMax = indexDreapta;
	}

	if (index != indexMax) {

		struct Pacient aux = heap.pacienti[index];

		heap.pacienti[index] = heap.pacienti[indexMax];
		heap.pacienti[indexMax] = aux;

		if (2 * indexMax + 1 < heap.dimNrelemente) {
			FiltrareHeap(heap, indexMax);
		}
	}
}

struct Pacient extragePacientPrioritateMare(struct Heap* heap) {
	struct Pacient aux = heap->pacienti[0];
	heap->pacienti[0] = heap->pacienti[heap->dimNrelemente - 1];
	heap->pacienti[heap->dimNrelemente - 1] = aux;
	heap->dimNrelemente--;
	for (int i = (heap->dimNrelemente - 1) / 2; i >= 0; i--)
	{
		FiltrareHeap(*heap, i);
	}
	return aux;
}

int main()
{
	struct Heap heap;
	heap = initializareHeap(6);
	heap.pacienti[0] = initializarePacient(4, "Marcela");
	heap.pacienti[1] = initializarePacient(3, "Ionela");
	heap.pacienti[2] = initializarePacient(8, "Alexandra");
	heap.pacienti[3] = initializarePacient(7, "Andreea");
	heap.pacienti[4] = initializarePacient(6, "Amalia");
	heap.pacienti[5] = initializarePacient(2, "Ana");
	heap.dimNrelemente = 6;

	for (int i = (heap.dimNrelemente - 2) / 2; i >= 0; i--)
	{
		FiltrareHeap(heap, i);
	}
	afiseazaHeapTotal(heap);

	struct Pacient pacient1 = extragePacientPrioritateMare(&heap);
	struct Pacient pacient2 = extragePacientPrioritateMare(&heap);
	extragePacientPrioritateMare(&heap); extragePacientPrioritateMare(&heap); extragePacientPrioritateMare(&heap); extragePacientPrioritateMare(&heap);

	printf("\n\n");
	afiseazaHeapTotal(heap);

}
