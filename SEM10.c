#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina
{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file)
{
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

void afisareMasina(Masina masina)
{
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector
//ALEGEM LSI

struct Stiva
{
	Masina info;
	struct Stiva* next;
};
typedef struct Stiva Stiva;

void pushStack(Stiva** nod, Masina masina)
{
	Stiva* aux = (Stiva*)malloc(sizeof(Stiva));
	aux->info = masina;
	aux->next = (*nod);
	(*nod) = aux;
}

Masina popStack(Stiva** nod)
{
	Masina masina;
	if ((*nod) != NULL)
	{
		Stiva* aux = (*nod);
		masina = aux->info;
		(*nod) = aux->next;
		free(aux);
	}
	else
	{
		masina.id = -1;
	}
	return masina;
}

char isEmptyStack(Stiva* nod)
{
	return nod == NULL;
}

Stiva* citireStackMasiniDinFisier(const char* numeFisier) {
	Stiva* nod = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f))
	{
		pushStack(&nod, citireMasinaDinFisier(f));
	}
	fclose(f);
	return nod;
}

void dezalocareStivaDeMasini(Stiva** cap)
{
	while (!isEmptyStack(*cap))
	{
		Masina m;
		m = popStack(cap);
		free(m.model);
		free(m.numeSofer);
	}
}

int size(Stiva* cap)
{
	int marime = 0;
	while (cap != NULL)
	{
		marime++;
		cap = cap->next;
	}
	return marime;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector

typedef struct nod Nod;
struct nod
{
	Masina info;
	Nod* next;
	Nod* prev;
};

typedef struct coada Coada;
struct coada
{
	Nod* first;
	Nod* last;
};

void enqueue(Coada* coada, Masina masina)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = (*coada).first;
	nou->prev = NULL;

	if ((*coada).first == NULL)
	{
		(*coada).first = nou;
		(*coada).last = nou;
		return;
	}

	(*coada).first->prev = nou;
	(*coada).first = nou;
}

Masina dequeue(Coada* coada)
{
	if (coada->last == NULL)
	{
		Masina m;
		m.id = -1;

		return m;
	}
	else
	{
		Masina m = coada->last->info;

		if (coada->last->prev == NULL)
		{
			coada->first = NULL;
			coada->last = NULL;
		}
		else
		{
			Nod* ultim = coada->last;
			coada->last = ultim->prev;

			ultim->prev->next = NULL;
		}
		return m;
	}
}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(/*stiva sau coada de masini*/int id);

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {
	Stiva* cap;

	cap = citireStackMasiniDinFisier("masini.txt");
	afisareMasina(popStack(&cap));

	printf("%d", size(cap));

	return 0;
}