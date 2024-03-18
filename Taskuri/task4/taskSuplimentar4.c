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

void copiere_matrice(Haina ***matrice, Haina *vector, int numarHaine, int criteriu) {
  *matrice = (Haina **)malloc(numarHaine * sizeof(Haina *));
  for (int i = 0; i < numarHaine; i++) {
    (*matrice)[i] = (Haina *)malloc(sizeof(Haina));
  }

  for (int i = 0; i < numarHaine; i++) {
    int linie;
    switch (criteriu) {
      case 0: 
        linie = cauta_linie_tip(vector[i].tip, *matrice, numarHaine);
        break;
      case 1: 
        linie = cauta_linie_material(vector[i].material, *matrice, numarHaine);
        break;
    }

    (*matrice)[linie] = alocare_si_copiere_haina(&vector[i]);
  }
}

Haina *alocare_si_copiere_haina(const Haina *haina) {
  Haina *hainaNoua = (Haina *)malloc(sizeof(Haina));
  strcpy(hainaNoua->tip, haina->tip);
  hainaNoua->material = (char *)malloc(strlen(haina->material) + 1);
  strcpy(hainaNoua->material, haina->material);
  hainaNoua->pret = haina->pret;
  hainaNoua->marime = haina->marime;
  return hainaNoua;
}

int cauta_linie_tip(const char *tip, Haina **matrice, int numarHaine) {
  for (int i = 0; i < numarHaine; i++) {
    if (strcmp(matrice[i]->tip, tip) == 0) {
      return i;
    }
  }
  return numarHaine;
}

int cauta_linie_material(const char *material, Haina **matrice, int numarHaine) {
  for (int i = 0; i < numarHaine; i++) {
    if (strcmp(matrice[i]->material, material) == 0) {
      return i;
    }
  }
  return numarHaine;
}

void sortareMatriceDupaNumarElemente(Haina ***matrice, int numarLinii) {

  int numarElementePeLinie[numarLinii];
  for (int i = 0; i < numarLinii; i++) {
    numarElementePeLinie[i] = 0;
    for (int j = 0; j < numarLinii; j++) {
      if ((*matrice)[i][j].tip[0] != '\0') {
        numarElementePeLinie[i]++;
      }
    }
  }

  int count[numarLinii + 1];
  for (int i = 0; i <= numarLinii; i++) {
    count[i] = 0;
  }
  for (int i = 0; i < numarLinii; i++) {
    count[numarElementePeLinie[i]]++;
  }

  int indiceSortat = 0;
  for (int i = 0; i <= numarLinii; i++) {
    while (count[i] > 0) {
      Haina *linieTemporara[numarLinii];
      for (int j = 0; j < numarLinii; j++) {
        linieTemporara[j] = (*matrice)[indiceSortat + j];
      }

      for (int j = 0; j < numarLinii; j++) {
        (*matrice)[indiceSortat + j] = linieTemporara[count[i] - 1];
        numarElementePeLinie[i]--;
      }

      indiceSortat += count[i] + 1;
      count[i]--;
    }
  }
}

void afisareMatrice(Haina **matrice, int numarLinii, int numarColoane) {
  for (int i = 0; i < numarLinii; i++) {
    for (int j = 0; j < numarColoane; j++) {
      if (matrice[i][j].tip[0] != '\0') {
        printf("%s (%s, %.2f, %d) ", matrice[i][j].tip, matrice[i][j].material, matrice[i][j].pret, matrice[i][j].marime);
      }
    }
    printf("\n");
  }
}

int main() {
Haina **matrice = NULL; 
    int numarHaine = 0; 
    const char *numeFisier = "Haine.txt"; 

    citireHainaFisier(&matrice, &numarHaine, numeFisier);

    printf("Matricea de haine:\n");
    afisareMatrice(matrice, numarHaine, 4); 
    sortareMatriceDupaNumarElemente(&matrice, numarHaine);

    printf("\nMatricea de haine sortata dupa numarul de elemente:\n");
    afisareMatrice(matrice, numarHaine, 4); 

    for (int i = 0; i < numarHaine; i++) {
        free(matrice[i]->material);
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}
