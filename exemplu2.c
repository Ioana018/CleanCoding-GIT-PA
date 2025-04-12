/* Parcurgere graf cu DFS/BFS */
#include <stdlib.h>
#include <stdio.h>

typedef struct Nod {
    int valoare;
    struct Nod *urmator;
} Nod;

typedef struct Graf {
    int varfuri;
    int *vizitat;
    Nod **liste_adiacenta;
} Graf;

Nod* creaza_nod(int v) {
    Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
    if (nod_nou == NULL) {
        printf("Eroare la alocarea memoriei pentru nod\n");
        exit(1);
    }
    nod_nou->valoare = v;
    nod_nou->urmator = NULL;
    return nod_nou;
}

Graf* creaza_graf(int varfuri) {
    Graf* graf = (Graf*)malloc(sizeof(Graf));
    if (graf == NULL) {
        printf("Eroare la alocarea memoriei pentru graf\n");
        exit(1);
    }

    graf->varfuri = varfuri;
    graf->liste_adiacenta = (Nod**)malloc(varfuri * sizeof(Nod*));
    graf->vizitat = (int*)malloc(varfuri * sizeof(int));

    if (graf->liste_adiacenta == NULL || graf->vizitat == NULL) {
        printf("Eroare la alocarea memoriei pentru liste adiacenta\n");
        exit(1);
    }

    for (int i = 0; i < varfuri; i++) {
        graf->liste_adiacenta[i] = NULL;
        graf->vizitat[i] = 0;
    }
    return graf;
}

void adauga_muchie(Graf* graf, int sursa, int destinatie) {
    // Adaugă de la sursa la destinatie
    Nod* nod_nou = creaza_nod(destinatie);
    nod_nou->urmator = graf->liste_adiacenta[sursa];
    graf->liste_adiacenta[sursa] = nod_nou;

    // Adaugă de la destinatie la sursa (graf neorientat)
    nod_nou = creaza_nod(sursa);
    nod_nou->urmator = graf->liste_adiacenta[destinatie];
    graf->liste_adiacenta[destinatie] = nod_nou;
}

void insereaza_muchii(int nr_varfuri, int nr_muchii, Graf* graf) {
    int sursa, destinatie;
    printf("Adaugati %d muchii (intre 0 si %d):\n", nr_muchii, nr_varfuri-1);

    for (int i = 0; i < nr_muchii; i++) {
        printf("Muchia %d: ", i+1);
        scanf("%d %d", &sursa, &destinatie);
        if (sursa >= nr_varfuri || destinatie >= nr_varfuri || sursa < 0 || destinatie < 0) {
            printf("Eroare: Noduri invalide! Trebuie sa fie intre 0 si %d\n", nr_varfuri-1);
            i--; // Repeta aceasta iteratie
            continue;
        }
        adauga_muchie(graf, sursa, destinatie);
    }
}

void reseteaza_vizitate(Graf* graf) {
    for (int i = 0; i < graf->varfuri; i++) {
        graf->vizitat[i] = 0;
    }
}

void DFS(Graf* graf, int varf) {
    Nod* lista_adiacenta = graf->liste_adiacenta[varf];
    graf->vizitat[varf] = 1;
    printf("%d ", varf);

    while (lista_adiacenta != NULL) {
        int varf_adiacent = lista_adiacenta->valoare;
        if (graf->vizitat[varf_adiacent] == 0) {
            DFS(graf, varf_adiacent);
        }
        lista_adiacenta = lista_adiacenta->urmator;
    }
}

void BFS(Graf* graf, int start) {
    // Creare coada
    int* coada = (int*)malloc(graf->varfuri * sizeof(int));
    int inceput = 0, sfarsit = 0;

    graf->vizitat[start] = 1;
    coada[sfarsit] = start;
    sfarsit++;

    while (inceput < sfarsit) {
        int varf = coada[inceput];
        inceput++;
        printf("%d ", varf);

        Nod* temp = graf->liste_adiacenta[varf];
        while (temp != NULL) {
            int varf_adiacent = temp->valoare;
            if (graf->vizitat[varf_adiacent] == 0) {
                graf->vizitat[varf_adiacent] = 1;
                coada[sfarsit] = varf_adiacent;
                sfarsit++;
            }
            temp = temp->urmator;
        }
    }
    free(coada);
}

void elibereaza_graf(Graf* graf) {
    for (int i = 0; i < graf->varfuri; i++) {
        Nod* curent = graf->liste_adiacenta[i];
        while (curent != NULL) {
            Nod* temp = curent;
            curent = curent->urmator;
            free(temp);
        }
    }
    free(graf->liste_adiacenta);
    free(graf->vizitat);
    free(graf);
}

int main() {
    int nr_varfuri, nr_muchii, start;

    printf("Introduceti numarul de varfuri: ");
    scanf("%d", &nr_varfuri);

    printf("Introduceti numarul de muchii: ");
    scanf("%d", &nr_muchii);

    Graf* graf = creaza_graf(nr_varfuri);
    insereaza_muchii(nr_varfuri, nr_muchii, graf);

    printf("\nParcurgere DFS:\n");
    printf("Introduceti nodul de start: ");
    scanf("%d", &start);
    reseteaza_vizitate(graf);
    DFS(graf, start);

    printf("\n\nParcurgere BFS:\n");
    printf("Introduceti nodul de start: ");
    scanf("%d", &start);
    reseteaza_vizitate(graf);
    BFS(graf, start);

    elibereaza_graf(graf);
    return 0;
}// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.