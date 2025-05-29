#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char* aux;
    Masina m1;
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy_s(m1.model, strlen(aux) + 1, aux);
    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
    m1.serie = *strtok(NULL, sep);
    return m1;
}

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr. usi : %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

struct Stiva {
    Masina info;
    struct Stiva* next;
};
typedef struct Stiva Stiva;

void pushStack(Stiva** nod, Masina masina) {
    Stiva* aux = (Stiva*)malloc(sizeof(Stiva));
    aux->info = masina;
    aux->next = (*nod);
    (*nod) = aux;
}

Masina popStack(Stiva** nod) {
    Masina masina;
    if ((*nod) != NULL) {
        Stiva* aux = (*nod);
        masina = aux->info;
        (*nod) = aux->next;
        free(aux);
    }
    else {
        masina.id = -1;
    }
    return masina;
}

char isEmptyStack(Stiva* nod) {
    return nod == NULL;
}

Stiva* citireStackMasiniDinFisier(const char* numeFisier) {
    Stiva* nod = NULL;
    FILE* f = fopen(numeFisier, "r");
    while (!feof(f)) {
        pushStack(&nod, citireMasinaDinFisier(f));
    }
    fclose(f);
    return nod;
}

void dezalocareStivaDeMasini(Stiva** cap) {
    while (!isEmptyStack(*cap)) {
        Masina m = popStack(cap);
        free(m.model);
        free(m.numeSofer);
    }
}

int size(Stiva* cap) {
    int marime = 0;
    while (cap != NULL) {
        marime++;
        cap = cap->next;
    }
    return marime;
}

// STRUCTURA COADÃ

typedef struct nod Nod;
struct nod {
    Masina info;
    Nod* next;
    Nod* prev;
};

typedef struct coada Coada;
struct coada {
    Nod* first;
    Nod* last;
};

void enqueue(Coada* coada, Masina masina) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masina;
    nou->next = coada->first;
    nou->prev = NULL;
    if (coada->first == NULL) {
        coada->first = coada->last = nou;
    }
    else {
        coada->first->prev = nou;
        coada->first = nou;
    }
}

Masina dequeue(Coada* coada) {
    if (coada->last == NULL) {
        Masina m; m.id = -1;
        return m;
    }
    Masina m = coada->last->info;
    if (coada->last->prev == NULL) {
        free(coada->last);
        coada->first = coada->last = NULL;
    }
    else {
        Nod* ultim = coada->last;
        coada->last = ultim->prev;
        coada->last->next = NULL;
        free(ultim);
    }
    return m;
}

Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) {
    Coada coada = { NULL, NULL };
    FILE* f = fopen(numeFisier, "r");
    while (!feof(f)) {
        Masina m = citireMasinaDinFisier(f);
        enqueue(&coada, m);
    }
    fclose(f);
    return coada;
}

void dezalocareCoadaDeMasini(Coada* coada) {
    while (coada->last != NULL) {
        Masina m = dequeue(coada);
        free(m.model);
        free(m.numeSofer);
    }
}

Masina getMasinaByID_Stiva(Stiva* cap, int id) {
    while (cap != NULL) {
        if (cap->info.id == id)
            return cap->info;
        cap = cap->next;
    }
    Masina m; m.id = -1;
    return m;
}

Masina getMasinaByID_Coada(Coada coada, int id) {
    Nod* p = coada.first;
    while (p != NULL) {
        if (p->info.id == id)
            return p->info;
        p = p->next;
    }
    Masina m; m.id = -1;
    return m;
}

float calculeazaPretTotal_Stiva(Stiva* cap) {
    float total = 0;
    while (cap != NULL) {
        total += cap->info.pret;
        cap = cap->next;
    }
    return total;
}

float calculeazaPretTotal_Coada(Coada coada) {
    float total = 0;
    Nod* p = coada.first;
    while (p != NULL) {
        total += p->info.pret;
        p = p->next;
    }
    return total;
}

int main() {
    Stiva* cap = citireStackMasiniDinFisier("masini.txt");
    printf("--- Masina extrasa din stiva ---\n");
    afisareMasina(popStack(&cap));
    printf("Dimensiunea stivei: %d\n", size(cap));
    printf("Total preturi in stiva: %.2f\n", calculeazaPretTotal_Stiva(cap));
    Coada c = citireCoadaDeMasiniDinFisier("masini.txt");
    printf("--- Total preturi in coada: %.2f\n", calculeazaPretTotal_Coada(c));
    Masina m = getMasinaByID_Coada(c, 3);
    if (m.id != -1)
        afisareMasina(m);
    else
        printf("Masina cu ID 3 nu a fost gasita.\n");
    dezalocareStivaDeMasini(&cap);
    dezalocareCoadaDeMasini(&c);
    return 0;
}
