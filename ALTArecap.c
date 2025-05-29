#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct StructuraMasina {
	int id;
	float pret;
	char* model;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citMasinaFisier(FILE* file)
{
	char buffer[100];
	char sep[4] = ", \n";
	char* aux;
	Masina m;
	m.id = atoi(strtok(buffer, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc(sizeof(streln(aux) + 1));
	strcpy_s(m.model, streln(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;
}

void afisareMasina(Masina m)
{
	printf("Id:%d\n", m.id);
	printf("Pret:%.2f\n", m.pret);
	printf("Model:%s\n", m.model);
	printf("Serie:%c\n\n", m.serie);
}

typedef struct Nod
{
	Masina info;
	struct Nod* st;
	struct Nod* dr;
}Nod;

void addMasinaArbABC(Nod** nod, Masina m)
{
	if ((*nod) != NULL)
	{
		if (m.id < (*nod)->info.id)
			addMasinaArbABC(&(*nod)->st, m);
		else
			addMasinaArbABC(&(*nod)->dr, m);
	}
	else 
	{
		(*nod) = (Nod*)malloc(sizeof(Nod));
		(*nod)->info = m;
		(*nod)->st = NULL;
		(*nod)->dr = NULL;
	}
}

Nod* citABCdinFis(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	Nod* nou = NULL;
	while (!feof(f)) 
	{
		Masina m = citMasinaFisier(f);
		addMasinaArbABC(&nou, m);
	}
	fclose(f);
	return nou;
}

void dezalocare(Nod** nod)
{
	if ((*nod) != NULL)
	{
		dezalocare(&((*nod)->st));
		dezalocare(&((*nod)->dr));
		free((*nod)->info.model);
		free(*nod);
		(*nod) = NULL;
	}
}

int inaltime(Nod* nod)
{
	if (nod = NULL)
		return 0;
	else
	{
		int st = inaltime(nod->st);
		int dr = inaltime(nod->dr);
		return 1 + (dr > st ? dr : st);
	}
}

int gradEc(Nod* nod)
{
	return inaltime(nod->st) - inaltime(nod->dr);
}

void rotireSt(Nod** nod)
{
	Nod* aux = (*nod)->dr;
	(*nod)->dr = aux->st;
	aux->st = (*nod);
	(*nod) = aux;
}

void rotireDr(Nod** nod)
{
	Nod* aux = (*nod)->st;
	(*nod)->st = aux->dr;
	aux->dr = (*nod);
	(*nod) = aux;
}

void addMasinaAVL(Nod** nod,Masina m)
{
	if ((*nod) != NULL)
	{
		if (m.id < (*nod)->info.id)
			addMasinaAVL(&(*nod)->st, m);
		else
			addMasinaAVL(&(*nod)->dr, m);
		int GE = gradEc(*nod);
		if (GE == 2)
		{
			if (gradEc((*nod)->st) != 1)
				rotireSt(nod);
			rotireDr(nod);
		}
		if (GE == -2)
		{
			if (gradEc((*nod)->dr) == -1)
				rotireDr(nod);
			rotireSt(nod);
		}
	}
	else
	{
		(*nod) = (Nod*)malloc(sizeof(Nod));
		(*nod)->info = m;
		(*nod)->dr = NULL;
		(*nod)->st = NULL;
	}
}