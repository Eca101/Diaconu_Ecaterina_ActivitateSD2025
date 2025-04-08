#define _CRT_SECURE_NO_WARNINGS
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

typedef struct
{
	Masina info;
	Nod* next;
	Nod* prev;
}Nod;

typedef struct
{
	Nod* first;
	Nod* last;
	int nrNoduri;
}LDI;

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

void afisareListaMasini(LDI lista) {
	Nod* p = lista.first;
	while (p)
	{
		afisareMasina(p->info);
		p = p->next;
	}
}

void adaugaMasinaInLista(LDI* lista, Masina masinaNoua) 
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last)
	{
		lista->last->next = nou;
	}
	else
	{
		lista->first = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}

LDI citireLDMasiniDinFisier(const char* numeFisier) 
{
	
	FILE* f = fopen(numeFisier, "r");
	LDI lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	while (!feof(f))
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(LDI* lista) 
{
	Nod* p = lista->first;
	while (p)
	{
		Nod* aux = p;
		p = p->next;
		if (aux->info.model)
		{
			free(aux->info.model);
		}
		if (aux->info.numeSofer)
			free(aux->info.numeSofer);
		free(aux);
	}
	free(lista->first);
	free(lista->last);
	lista->nrNoduri = 0;

}

int main() {


	return 0;
}