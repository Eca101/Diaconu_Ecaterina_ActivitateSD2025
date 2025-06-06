#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt <3
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

typedef struct nod nod;

struct nod 
{
	Masina info;
	struct nod* next;
	struct nod* prev;
};
//creare structura pentru Lista Dubla 
typedef struct listaDubla listaDubla;
struct listaDubla
{
	struct nod* first;
	struct nod* last;
};


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

void afisareListaMasiniDeLaInceput(listaDubla lista) 
{
	nod* p = lista.first;
	while (p !=NULL)
	{
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasiniDeLaSfarsit(listaDubla lista)
{
	nod* aux = lista.last;
	while (aux != NULL)
	{
		afisareMasina(aux->info);
		aux = aux->prev;
	}
}

void adaugaMasinaInListaLaSfarsit(listaDubla* lista, Masina masinaNoua) 
{
	nod* p = (nod*)malloc(sizeof(nod));
	p->info = masinaNoua;
	p->next = NULL;
	p->prev = lista->last;
	if (lista->last != NULL)
	{
		lista->last->next = p;
	}
	else
	{
		lista->first = p;
	}
	lista->last = p;

}

void adaugaLaInceputInLista(listaDubla* lista, Masina masinaNoua) 
{
	nod* aux= (nod*)malloc(sizeof(nod));
	aux->info = masinaNoua;
	aux->prev = NULL;
	aux->next = lista->first;
	if (lista->first != NULL)
	{
		lista->first->prev = aux;
	}
	else
	{
		lista->last = aux;
	}
	lista->first = aux;
}

listaDubla citireLDMasiniDinFisier(const char* numeFisier) 
{
	FILE* f = fopen(numeFisier, "r");
	listaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	while (!feof(f))
	{
		Masina aux = citireMasinaDinFisier(f);
		adaugaMasinaInListaLaSfarsit(&lista, aux);//shallow copy
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(listaDubla* lista) 
{
	while (lista->first != NULL)
	{
		nod* aux = lista->first;
		free(aux->info.numeSofer);
		free(aux->info.model);
		lista->first = lista->first->next;
		free(aux);
	}
	lista->last = NULL;
}

float calculeazaPretMediu(listaDubla lista) 
{
	float suma=0;
	int k = 0;
	while (lista.first != NULL)
	{
		suma = +lista.first->info.pret;
		k++;
		lista.first = lista.first->next;
	}
	if (k != 0)
	{
		return suma / k;
	}
	else return -1;
}

void stergeMasinaDupaID(listaDubla* lista, int id) 
{
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	nod* temp = lista->first;
	if (temp->info.id == id)
	{
		lista->first = temp->next;
		if (lista->first != NULL)
		{
			lista->first->prev = NULL;
		}
		else
		{
			lista->last = NULL;
		}
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	temp = lista->last;
	if (temp->info.id == id) 
	{
		lista->last = temp->prev;

		if (lista->last != NULL)
		{
			lista->last->next = NULL;
		}
		else
		{
			lista->first = NULL;
		}

		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
}

char* getNumeSoferMasinaScumpa(listaDubla lista) 
{
	if (lista.first != NULL)
	{
		nod* max = lista.first;
		lista.first = lista.first->next;
		while (lista.first != NULL)
		{
			if (lista.first->info.pret > max->info.pret)
				max = lista.first;
			lista.first = lista.first->next;
		}
		char* numeSofer = malloc(strlen(max->info.numeSofer) + 1);
		strcpy_s(numeSofer, strlen(max->info.numeSofer) + 1, max->info.numeSofer);
		return numeSofer;
	}
	else return NULL;
}

int main() {
	listaDubla LD = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(LD);
	printf(".................................\n");
	afisareListaMasiniDeLaSfarsit(LD);
	printf(".................................\n");
	float media = calculeazaPretMediu(LD);
	if (media != -1)
	{
		printf("Pretul mediu al masinilor din lista e %.2f\n", media);
	}
	else
	{
		printf("Nu se poate calcula ptc lista e goala:((");
	}
	dezalocareLDMasini(&LD);
	
	return 0;
}