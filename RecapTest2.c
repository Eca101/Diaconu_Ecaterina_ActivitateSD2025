#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod
{
	Masina info;
	struct Nod* st;
	struct Nod* dr;
}Nod;

Masina citireMasinaFisier(FILE* file)
{
	char buffer[100];
	char sep[4] = ",\n ";
	char* aux;
	Masina m;
	fgets(buffer, 100, file);
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void addMasinaABC(Nod**arb, Masina m)
{
	if ((*arb) != NULL)
	{
		if (m.id < (*arb)->info.id)
			addMasinaABC(&(*arb)->st, m);
		else
			addMasinaABC(&(*arb)->dr, m);
	}
	else
	{
		(*arb) = (Nod*)malloc(sizeof(Nod));
		(*arb)->dr = NULL;
		(*arb)->st = NULL;
		(*arb)->info = m;
	}
}

Nod* citABCdinFis(const char* numeFis)
{
	FILE* f = fopen(numeFis, "r");
	if (!f)return NULL;
	Nod* nod = NULL;
	while (!feof(f))
	{
		Masina m = citireMasinaFisier(f);
		if (m.model != NULL && m.numeSofer != NULL)
		{
			addMasinaABC(&nod, m);
		}
	}
	fclose(f);
	return nod;
}

void preordine(Nod* nod)
{
	if (nod != NULL)
	{
		afisareMasina(nod->info);
		preordine(nod->st);
		preordine(nod->dr);
	}
}

void dezalocABC(Nod** rad)
{
	if (*rad != NULL)
	{
		dezalocABC(&((*rad)->st));
		dezalocABC(&((*rad)->dr));
		free((*rad)->info.model);
		free((*rad)->info.numeSofer);
		free(*rad);
		*rad = NULL;
	}
}

int main()
{
	Nod* radacina = citABCdinFis("masini.txt");
	printf("Parcurgere in preordine a arborelui de masini:\n");
	preordine(radacina);
	dezalocABC(&radacina);
	return 0;
}