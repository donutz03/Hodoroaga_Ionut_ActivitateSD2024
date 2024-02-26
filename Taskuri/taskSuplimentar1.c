//enuntul de la task in subsol
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Haina {
  char tip[50];
  char material[100];
  float pret;
  int marime;
} Haina;

Haina citireHaina() {
  Haina haina;
  printf("Introduceti tipul hainei: ");
  scanf("%s", haina.tip);
  printf("Introduceti materialul hainei: ");
  scanf("%s", haina.material);
  printf("Introduceti pretul hainei: ");
  scanf("%f", &haina.pret);
  printf("Introduceti marimea hainei: ");
  scanf("%d", &haina.marime);
  return haina;
}

float calculeazaPretCuTva(Haina haina, float tva) {
  return haina.pret * (1 + tva / 100);
}

void modificaMarime(Haina *haina, int nouaMarime) {
  haina->marime = nouaMarime;
}

void afisareHaina(Haina haina) {
  printf("Tip: %s\n", haina.tip);
  printf("Material: %s\n", haina.material);
  printf("Pret: %.2f lei\n", haina.pret);
  printf("Marime: %d\n", haina.marime);
}

int main() {
  Haina haina1 = citireHaina();
  afisareHaina(haina1);

  printf("Pretul cu TVA 19%% este: %.2f lei\n", calculeazaPretCuTva(haina1, 19));

  modificaMarime(&haina1, 42);
  afisareHaina(haina1);

  return 0;
}


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

 

Articolul trebuie să aibă logica. Articolul trebuie sa fie un substantiv. Articolul trebuie sa aibă cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.

Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de voi. Funcția returnează obiectul citit.

Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o medie sau o suma, un maxim, un minim...sau orice altceva)

Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp. noua valoare este primita ca parametru.

Realizați o funcție care afișează un obiect de tipul creat. Afișarea se face la console, și sunt afișate toate informațiile.
*/
