//enunt la final
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Haina {
    char tip[50];
    char *material;
    float pret;
    int marime;
} Haina;

Haina creareHaina(const char *tip, const char *material, float pret, int marime) {
    Haina h;
    strcpy(h.tip, tip);
    h.material = (char *)malloc(strlen(material) + 1);
    strcpy(h.material, material);
    h.pret = pret;
    h.marime = marime;
    return h;
}

void distrugeHaina(Haina *h) {
    free(h->material);
}

Haina copiereHaina(const Haina *h) {
    Haina copie;
    strcpy(copie.tip, h->tip);
    copie.material = (char *)malloc(strlen(h->material) + 1);
    strcpy(copie.material, h->material);
    copie.pret = h->pret;
    copie.marime = h->marime;
    return copie;
}

void afisareHaina(Haina haina) {
    printf("Tip: %s\n", haina.tip);
    printf("Material: %s\n", haina.material);
    printf("Pret: %.2f lei\n", haina.pret);
    printf("Marime: %d\n", haina.marime);
}

void creareVectorHaina(Haina **haine, int *numarHaine) {
    *haine = (Haina *)malloc(5 * sizeof(Haina));
    *numarHaine = 5; 

    (*haine)[0] = creareHaina("Blugi", "Bumbac", 100, 32);
    (*haine)[1] = creareHaina("Rochie", "In", 200, 38);
    (*haine)[2] = creareHaina("Camasa", "Poplin", 50, 34);
    (*haine)[3] = creareHaina("Tricou", "Bumbac", 75, 40);
    (*haine)[4] = creareHaina("Jacheta", "Piele", 300, 42);
}

void filtrareHainaMarime(Haina *haine, int numarHaine, Haina **haineFiltrate, int *numarHaineFiltrate, int marime) {
    *numarHaineFiltrate = 0;
    for (int i = 0; i < numarHaine; i++) {
        if (haine[i].marime == marime)
            (*numarHaineFiltrate)++;
    }
    *haineFiltrate = (Haina *)malloc(*numarHaineFiltrate * sizeof(Haina));

    int contor = 0;
    for (int i = 0; i < numarHaine; i++) {
        if (haine[i].marime == marime)
            (*haineFiltrate)[contor++] = copiereHaina(&haine[i]); 
    }
}

void filtrareHainaTipMaterial(Haina *haine, int numarHaine, Haina **haineFiltrate, int *numarHaineFiltrate, const char *tip, const char *material) {
    *numarHaineFiltrate = 0;
    for (int i = 0; i < numarHaine; i++) {
        if (strcmp(haine[i].tip, tip) == 0 && strcmp(haine[i].material, material) == 0)
            (*numarHaineFiltrate)++;
    }
    *haineFiltrate = (Haina *)malloc(*numarHaineFiltrate * sizeof(Haina));

    int contor = 0;
    for (int i = 0; i < numarHaine; i++) {
        if (strcmp(haine[i].tip, tip) == 0 && strcmp(haine[i].material, material) == 0)
            (*haineFiltrate)[contor++] = copiereHaina(&haine[i]); 
    }
}

void concatenareVectoriHaina(Haina *haine1, int numarHaine1, Haina *haine2, int numarHaine2, Haina **haineConcat, int *numarHaineConcat) {
    *numarHaineConcat = numarHaine1 + numarHaine2;
    *haineConcat = (Haina *)malloc(*numarHaineConcat * sizeof(Haina));

    for (int i = 0; i < numarHaine1; i++)
        (*haineConcat)[i] = copiereHaina(&haine1[i]);

    for (int i = 0; i < numarHaine2; i++)
        (*haineConcat)[numarHaine1 + i] = copiereHaina(&haine2[i]);
}

void afisareVectorHaina(Haina *haine, int numarHaine) {
    for (int i = 0; i < numarHaine; i++) {
        afisareHaina(haine[i]);
        printf("\n");
    }
}

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

void scriereHainaFisier(Haina haina, const char *numeFisier) {
    FILE *fisier = fopen(numeFisier, "a");

    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului %s!\n", numeFisier);
        return;
    }

    fprintf(fisier, "%s %.2f %d %s\n", haina.tip, haina.pret, haina.marime, haina.material);

    fclose(fisier);
}

void scriereVectorHainaFisier(Haina *haine, int numarHaine, const char *numeFisier) {
    FILE *fisier = fopen(numeFisier, "w");

    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului %s!\n", numeFisier);
        return;
    }

    fprintf(fisier, "%d\n", numarHaine);

    for (int i = 0; i < numarHaine; i++) {
        fprintf(fisier, "%s %.2f %d %s\n", haine[i].tip, haine[i].pret, haine[i].marime, haine[i].material);
    }

    fclose(fisier);
}


int main() {
    
    Haina *haine;
    int numarHaine;
    
    haine = (Haina *)malloc(10 * sizeof(Haina)); 

    creareVectorHaina(&haine, &numarHaine);
    printf("Vectorul initial de haine:\n");
    afisareVectorHaina(haine, numarHaine);

    printf("\nHaine cu marimea 40:\n");
    Haina *haineFiltrateMarime;
    int numarHaineFiltrateMarime;
    filtrareHainaMarime(haine, numarHaine, &haineFiltrateMarime, &numarHaineFiltrateMarime, 40);
    afisareVectorHaina(haineFiltrateMarime, numarHaineFiltrateMarime);

    printf("\nHaine de tip tricou din bumbac:\n");
    Haina *haineFiltrateTipMaterial;
    int numarHaineFiltrateTipMaterial;
    filtrareHainaTipMaterial(haine, numarHaine, &haineFiltrateTipMaterial, &numarHaineFiltrateTipMaterial, "Tricou", "Bumbac");
    afisareVectorHaina(haineFiltrateTipMaterial, numarHaineFiltrateTipMaterial);

    printf("\nVectorul rezultat dupa concatenare:\n");
    Haina *haineConcat;
    int numarHaineConcat;
    concatenareVectoriHaina(haine, numarHaine, haineFiltrateMarime, numarHaineFiltrateMarime, &haineConcat, &numarHaineConcat);
    afisareVectorHaina(haineConcat, numarHaineConcat);

    citireHainaFisier(&haine, &numarHaine, "haine.txt");

    for (int i = 0; i < numarHaine; i++) {
        afisareHaina(haine[i]);
        printf("\n");
    }

    Haina hainaNoua = creareHaina("Blugi", "Bumbac", 100, 32);
    scriereHainaFisier(hainaNoua, "haine.txt");

    scriereVectorHainaFisier(haine, numarHaine, "haine_out.txt");

    for (int i = 0; i < numarHaine; i++) 
        distrugeHaina(&haine[i]);
    free(haine); 

    return 0;
}

/*
Considerati codul de la task-ul precedent.

Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create. Asezarea in fisier a elementelor o faceti la libera alegere.

Scrieti intr-un program C functia care sa citeasca obiectele din fisier si sa le salveze intr-un vector.

Scrieti o functie care va salva un obiect  intr-un fisier text.

Scrieti o functie care va salva un vector de obiecte intr-un fisier text.
*/
