#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};
struct Masina initializare(int id, int nrKm, char* model, float pret, char tipMotor) {
	struct Masina m;
	m.id = 1;
	m.nrKm = nrKm;
	m.model = (char*)malloc(sizeof(model) + 1);
	strcpy(m.model, model);
	m.pret = pret;
	m.tipMotor = tipMotor;
	//initializare structura 
	return m;
}

void afisare(struct Masina m) {
	printf("Id-ul este %d, nr. de km: %d, modelul este %s, pretul este %f, motorul %c\n", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}
}

struct Masina* copiazaPrimeleElemente(struct Masina* vector, int nrElemente, int* nrElementeCopiate) {
	struct Masina* vectorNou;
	vectorNou = NULL;
	if (vector != NULL && *nrElementeCopiate > 0)
		if (nrElemente < *nrElementeCopiate) {
			*nrElementeCopiate = nrElemente;
		}
	vectorNou = malloc(sizeof(struct Masina) * (*nrElementeCopiate));
	for (int i = 0; i < *nrElementeCopiate; i++) {
		vectorNou[i] = initializare(vector[i].id, vector[i].nrKm, vector[i].model, vector[i].pret, vector[i].tipMotor);
	}
	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < nrElemente; i++) {
		if ((*vector[i]).model != NULL) {
			free((*vector)[i].model);
		}
	}
}

void copiazaMasiniIeftine(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret < prag)
		{
			(*dimensiune)++;
		}
	}
	int k = 0;
	*vectorNou = malloc(sizeof(struct Masina) * (*dimensiune));
	for (int i = 0; i < nrElemente; i++)
	{
		(*vectorNou)[k] = vector[i];
		(*vectorNou)[k].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
		strcpy_s((*vectorNou)[k].model, strlen(vector[i].model) + 1, vector[i].model);
		k++;
	}
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}



int main() {
	int n = 3;
	struct Masina* vec;
	vec = malloc(sizeof(struct Masina) * n);
	vec[0] = initializare(10, 10000, "Logan", 1000.4, 'b');
	vec[1] = initializare(11, 1000, "Passat", 2500.4, 'b');
	vec[2] = initializare(12, 25464, "Cyber Truck", 10000.0, 'e');
	afisareVector(vec, n);
	int nrElemCopiat = 5;
	struct Masina* vecNou = copiazaPrimeleElemente(vec, n, &nrElemCopiat);
	printf("Elemente copiate:\n");
	afisareVector(vecNou, nrElemCopiat);

	return 0;
}