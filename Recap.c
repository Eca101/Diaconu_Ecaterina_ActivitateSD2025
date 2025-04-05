#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
//sem2 refacut
typedef struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
} Telefon;

 Telefon initializare(int id, int ram,const char* producator, float pret, char serie) {
	 Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(t.producator, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

void afisare( Telefon t) {
	if (t.producator != NULL) {
		printf("%d. Telefonul %s seria %c are %d GB RAM si costa %5.2f RON.\n",t.id, t.producator, t.serie, t.RAM, t.pret);
	}
	else {
		printf("%d. Telefonul din seria %c are %d GB RAM si costa %5.2f RON.\n",t.id, t.serie, t.RAM, t.pret);
	}
}

void afisareVector( Telefon* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

 Telefon* copiazaPrimeleNElemente( Telefon* vector, int nrElemente, int nrElementeCopiate) 
{
	 Telefon* vNou = NULL;
	 vNou= (Telefon*)malloc(sizeof(Telefon) * nrElementeCopiate);
	 for (int i = 0; i < nrElementeCopiate; i++)
	 {
		 vNou[i] = vector[i];
		 vNou[i].producator = (char*)malloc(sizeof(char) * (strlen(vector[i].producator) + 1));
		 strcpy(vNou[i].producator, vector[i].producator);
	 }
	 return vNou;
}
 //!
void dezalocare( Telefon** vector, int* nrElemente) 
{
	for (int i = 0; i < (*nrElemente); i++) {
		if ((*vector)[i].producator != NULL) {
			free((*vector)[i].producator);
		}
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}
//!

void copiazaTelefoaneIeftine( Telefon* vector, char nrElemente, float pretMax,  Telefon** vNou, int* dimensiune) 
{
	(*dimensiune) = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret < pretMax)
			(*dimensiune)++;
	}
	vNou = (Telefon*)malloc(sizeof(Telefon) * (*dimensiune));
	int k = 0;
	for (int i = 0; i <nrElemente; i++)
	{
		if (vector[i].pret < pretMax)
		{
			(*vNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy((*vNou)[k].producator, vector[i].producator);
			k++;
		}
	}
	
}

Telefon getPrimulTelefonByProducator(Telefon* vector, int nrElemente, const char* producator) 
{
	Telefon t;
	t.producator = NULL;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].producator, producator) == 0) {
			t = vector[i];
			t.producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy(t.producator,vector[i].producator);
			return t;
		}
	}
	return t;
}
//.....s3

void adaugaTelInVector(Telefon** vTel, int* nrTel, Telefon telNou) 
{
	Telefon* aux = (Telefon*)malloc(sizeof(Telefon)*((*nrTel) + 1));
	for (int i = 0; i < (*nrTel); i++)
	{
		aux[i] = (*vTel)[i];
	}
	aux[(*nrTel)] = telNou;
	free(*vTel);
	(*vTel) = aux;
	(*nrTel)++;
}
//!!!!
Telefon citireTelFisier(FILE* file) 
{
	Telefon t;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);
	t.id = atoi(strtok(buffer, sep));
	t.RAM = atoi(strtok(NULL,sep));
	t.pret = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	t.producator = (char*)malloc(strlen(aux) + 1);
	strcpy(t.producator, aux);
	t.serie = strtok(NULL, sep)[0];
	return t;

}//!!!!!!!!

Telefon* citireVectorTelFisier(const char* numeFisier, int* nrTelCitite) 
{

	FILE* f = fopen(numeFisier, "r");
	Telefon* vTelefoane = NULL;
	(*nrTelCitite) = 0;
	while (!feof(f))
	{
		adaugaTelInVector(&vTelefoane, nrTelCitite, citireTelFisier(f));//!!
	}
	fclose(f);
	return vTelefoane;
}
//!!!!!!!!!!!!!!!!
void dezalocareVectorTel(Telefon** vector, int* nrTel) 
{
	for (int i = 0; i < (nrTel); i++)
	{
		if ((*vector)[i].producator != NULL)
		{
			free((*vector)[i].producator);
		}
		free((*vector));
		(*vector) = NULL;
		(*nrTel) = 0;
	}
}//!!!!!!!!!!!!!!!!!!!!
//s4

typedef struct Nod 
{
	Telefon info;
	Nod* next;
} Nod ;

void afisareListaTel(Nod* cap) {
	while (cap)
	{
		afisare(cap->info);
		cap = cap->next;
	}
}
void adaugaMasinaInLista(Nod**cap, Telefon telNou) 
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = telNou;
	nou->next = NULL;
	if (*cap == NULL)
	{
		(*cap) = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
}
void adaugaLaInceputInLista(Nod** cap, Telefon telNou) 
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = telNou;
	nou->next = NULL;
	(*cap) = nou;
}

Nod* citireListaTelDinFisier(const char* numeFisier) 
{
	Nod* cap = NULL;
	FILE* f = (numeFisier, "r");
	while (!feof(f))
	{
		adaugaMasinaInLista(&cap, citireTelFisier(f));
	}
	fclose(f);
	return cap;
}
//
void dezalocareListaTel(Nod** cap) 
{
	while (*cap) 
	{
		Nod* aux = *cap;
		*cap = aux->next;
		if (aux->info.producator)
		{
			free(aux->info.producator);
		}
		free(aux);
	}
}


int main() {

	Telefon* telefoane = NULL;
	int nrTelefoane = 3;
	telefoane = (Telefon*)malloc(sizeof(Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 512, "Motorola", 1500, 'M');
	telefoane[2] = initializare(3, 256, "Apple", 2200, 'A');

	afisareVector(telefoane, nrTelefoane);

	Telefon* primeleTelefoane = NULL;
	int nrPrimeleTelefoane = 2;

	primeleTelefoane = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrPrimeleTelefoane);
	printf("\n\nPrimele telefoane:\n");
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);
	dezalocare(&primeleTelefoane, &nrPrimeleTelefoane);
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);

	//copiaza telefoane ieftine
	Telefon* telefoaneIeftine = NULL;
	int nrTelefoaneIeft = 0;
	copiazaTelefoaneIeftine(telefoane, nrTelefoane, 2100, &telefoaneIeftine, &nrTelefoaneIeft);
	printf("\n\nTelefoane Scumpe:\n");
	afisareVector(telefoaneIeftine, nrTelefoaneIeft);
	dezalocare(&telefoaneIeftine, &nrTelefoaneIeft);

	Telefon telefon = getPrimulTelefonByProducator(telefoane, nrTelefoane, "Apple");
	printf("\n\nTelefonul gasit:\n");
	afisare(telefon);
	if (telefon.producator != NULL) {
		free(telefon.producator);
		telefon.producator = NULL;
	}
	dezalocare(&telefoane, &nrTelefoane);
	//..............

	return 0;
}