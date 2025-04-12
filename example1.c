#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf


// Pentru simplitate, folosim int-uri pentru a numi restaurantele/locațiile
// Ex: 1 - restaurantul 1 și tot așa

typedef struct Nod{
    int data;
    struct Nod *next;
} NODE;

typedef struct Graf {
    int nr_noduri_graf;
    int *vizitat;
    NODE **array_adiacenta_noduri;
} Graf;

typedef struct {
    int t;
    int scap;
    int *arr;
} STK;

NODE *creeare_nod(int valoare) {
    NODE *nod_nou = malloc(sizeof(NODE));
    nod_nou->data = valoare;
    nod_nou->next = NULL;
    return nod_nou;
}

void creeare_muchie(Graf *graf, int sursa, int destinatie) {
    NODE *nod_nou = creeare_nod(destinatie);
    printf("Adaug muchie de la %d la %d\n", sursa, destinatie);  // Debug pentru verificarea muchiei

    nod_nou->next = graf->array_adiacenta_noduri[sursa];
    graf->array_adiacenta_noduri[sursa] = nod_nou;

    printf("Lista de adiacenta pentru nodul %d dupa adaugarea muchiei: ", sursa);
    NODE *parsare = graf->array_adiacenta_noduri[sursa];
    while (parsare != NULL) {
        printf("%d ", parsare->data);
        parsare = parsare->next;
    }
    printf("\n");

    nod_nou = creeare_nod(sursa);
    nod_nou->next = graf->array_adiacenta_noduri[destinatie];
    graf->array_adiacenta_noduri[destinatie] = nod_nou;

    printf("Lista de adiacenta pentru nodul %d dupa adaugarea muchiei: ", destinatie);
    parsare = graf->array_adiacenta_noduri[destinatie];
    while (parsare != NULL) {
        printf("%d ", parsare->data);
        parsare = parsare->next;
    }
    printf("\n");
}


Graf *creeaza_graf(int nr_noduri) {
    Graf *graf_nou = malloc(sizeof(Graf));
    graf_nou->nr_noduri_graf = nr_noduri;
    graf_nou->array_adiacenta_noduri = malloc(nr_noduri * sizeof(NODE *));
    graf_nou->vizitat = malloc(nr_noduri * sizeof(int));

    int index;
    for (index = 0; index < nr_noduri; index++) {
        graf_nou->array_adiacenta_noduri[index] = NULL;
        graf_nou->vizitat[index] = 0;
    }

    return graf_nou;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s) {
    s->t += 1;
    s->arr[s->t] = pshd;
}

void DFS(Graf *g, STK *s, int v_nr) {
    NODE *auxiliar = g->array_adiacenta_noduri[v_nr];
    g->vizitat[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    while (auxiliar != NULL) {
        int con_ver = auxiliar->data;
        if (g->vizitat[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        auxiliar = auxiliar->next;
    }
}

void adaugare_muchii(Graf *graf, int nr_laturi) {
    int sursa, destinatie;
    printf("Functie adaugare %d muchii:\n", nr_laturi);
    int index;

    for (index = 0; index < nr_laturi; index++) {
        printf("Sursa:"); scanf("%d",&sursa);
        printf("Destinatie:"); scanf("%d",&destinatie);
        printf("\n");
        creeare_muchie(graf, sursa, destinatie);
    }
}

void wipe(Graf *graf) {
    for (int i = 0; i < graf->nr_noduri_graf; i++) {
        graf->vizitat[i] = 0;
    }
}

void afisare_legaturi_graf(Graf *graf) {
    int i;
    for (i = 0; i < graf->nr_noduri_graf; i++) {
        NODE *parsare = graf->array_adiacenta_noduri[i];
        printf("Lista de adiacenta pentru nodul %d: ", i);
        if (parsare == NULL) {
            printf("NULL\n");
        } else {
            while (parsare != NULL) {
                printf("%d ", parsare->data);  // Afișează fiecare nod conectat
                parsare = parsare->next;  // Mergi la următorul nod
            }
            printf("\n");
        }
    }
}

void verificare_drum_direct(Graf *graf, int nod1, int nod2) {

    //verific in lista nodului 1 pentru existenta nodului 2
    //deoarece lucrez cu un graf neorientat, este de ajuns sa verific intr-o singura lista din vectorul de liste

    NODE *parsare = graf->array_adiacenta_noduri[nod1];
    bool este_drum_direct = false;
    while (este_drum_direct == false && parsare != NULL) {
        if (parsare->data == nod2) {
            este_drum_direct = true;
        }
        parsare = parsare->next;
    }

    if (este_drum_direct == true) {
        printf("Intre nodul %d si nodul %d exista drum direct.\n",nod1,nod2);
    }
    else {
        printf("Intre nodul %d si nodul %d nu exista drum direct.\n",nod1,nod2);
    }
}

int main() {
    int numar_noduri, numar_laturi;

    printf("Cate noduri are graful? ");
    scanf("%d", &numar_noduri);

    printf("Cate muchii are graful? ");
    scanf("%d", &numar_laturi);

    Graf *g = creeaza_graf(numar_noduri);

    STK *s1 = create_s(2 * numar_noduri);
    STK *s2 = create_s(2 * numar_noduri);

    adaugare_muchii(g,numar_laturi);

    afisare_legaturi_graf(g);

    verificare_drum_direct(g, 1, 4 );
    verificare_drum_direct(g, 0, 3 );

    return 0;
}
