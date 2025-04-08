#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod {
	Masina info;
	Nod* next;
}Nod;

typedef struct LDI {

	Nod* first;
	Nod* prev;
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
	m1.pret= atof(strtok(NULL, sep));
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

void afisareListaMasini(Nod* cap) {
	while (cap)
	{
		afisareMasina(cap->info);
		cap = cap->next;
	}

}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	if (*cap)
	{
		Nod* aux=(*cap);
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		(*cap) = nou;
	}
	nou->next = NULL;
}

void adaugaLaInceputInLista(Nod**cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *cap;
	(*cap) = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) 
{
	FILE* f = fopen(numeFisier, "r");
	Nod* cap = NULL;
	if (f)
	{
		while (!feof(f))
		{
			adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));
		}
	}
	fclose(f);
	return cap;
}

void dezalocareListaMasini(Nod**cap) {
	while (*cap)
	{
		Nod* aux = *cap;
		(*cap) = aux->next;
		if (aux->info.model)
		{
			free(aux->info.model);
		}
		if (aux->info.numeSofer)
		{
			fre(aux->info.numeSofer);
		}
		free(aux);
	}
	
}

float calculeazaPretMediu(Nod*cap) 
{
	float suma = 0;
	int contor = 0;
	while (cap)
	{
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	if (contor > 0)
	{
		return suma / contor;
	}
	return 0;

}
void afisareListaMasini(LDI listaD) 
{
	Nod* p = listaD.first;
	while (p) 
	{
		afisareMasina(p->info);
	}
}



int main() {


	return 0;
}