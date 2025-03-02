#include<stdio.h>
#include<stdlib.h>

struct Masina
{
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};

struct Masina initializare(int id, int nrKm, const char* model, float pret, char tipMotor)
{
	struct Masina m;
	m.id = id;
	m.nrKm = nrKm;
	m.pret = pret;
	m.tipMotor = tipMotor;
	m.model = (const char*)malloc(strlen(model) * sizeof(const char) + 1);
	strcpy(m.model, model);
	return m;
}

void afisare(struct Masina m)
{
	printf("ID: %d\nNrKm: %d\nModel: %s\nPret: %.2f\nTipMotor: %c\n", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
}

void modifica_Pret(struct Masina* m, float noulPret)
{
	if (noulPret > 0);
	m->pret = noulPret;
}

void dezalocare(struct Masina* m) {
	free(m->model);
	m->model = NULL;
}

int main() {
	struct Masina masina = initializare(1, 1090, "Logan", 5600.50, 'B'); // 'B'
	afisare(masina);
	modifica_Pret(&masina, 100.00);
	afisare(masina);

	dezalocare(&masina);
	afisare(masina);
	return 0;
}