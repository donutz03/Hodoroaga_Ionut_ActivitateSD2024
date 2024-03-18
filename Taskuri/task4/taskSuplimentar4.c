#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Haina {
  char tip[50];
  char *material;
  float pret;
  int marime;
} Haina;

void citireHainaFisier(Haina **haine, int *numarHaine, const char *numeFisier) {
  FILE *fisier = fopen(numeFisier, "r");

  if (fisier == NULL) {
    printf("Eroare la deschiderea fisierului %s!\n", numeFisier);
    return;
  }

  fscanf(fisier, "%d", numarHaine);

  *haine = (Haina *)malloc(*numarHaine * sizeof(Haina));

  for (int i = 0; i < *numarHaine; i++) {
    char tip[50];
    float pret;
    int marime;

    fscanf(fisier, "%s %f %d", tip, &pret, &marime);

    char *material = (char *)malloc(50 * sizeof(char));
    fscanf(fisier, "%s", material);

    (*haine)[i] = creareHaina(tip, material, pret, marime);

    free(material);
  }

  fclose(fisier);
}

int main() {
  Haina *haine;
  int numarHaine;

  citireHainaFisier(&haine, &numarHaine, "haine.txt");

  // Afisarea elementelor din vector
  for (int i = 0; i < numarHaine; i++) {
    afisareHaina(haine[i]);
    printf("\n");
  }

  // Eliberarea memoriei alocate
  for (int i = 0; i < numarHaine; i++) {
    distrugeHaina(&haine[i]);
  }
  free(haine);

  return 0;
}
