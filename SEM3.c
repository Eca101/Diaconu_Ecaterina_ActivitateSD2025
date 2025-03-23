//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;//e alias ca sa nu mai punem cu struct
//
//void afisareMasina(Masina masina) {
//	//afiseaza toate atributele unei masini
//	printf("ID:%d\n", masina.id);
//	printf("nrUsi:%d\n", masina.nrUsi);
//	printf("pret:%2f\n", masina.pret);
//	printf("model:%s\n", masina.model);
//	printf("numeSofer:%s\n", masina.numeSofer);
//	printf("serie:%c\n\n", masina.serie);
//
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	//afiseaza toate elemente de tip masina din vector
//	//prin apelarea functiei afisareMasina()
//	for (int i = 0; i < nrMasini; i++)
//	{
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	//adauga in vectorul primit o noua masina pe care o primim ca parametru
//	//ATENTIE - se modifica numarul de masini din vector;
//	Masina* temp;
//	temp = malloc(sizeof(Masina) * ((*nrMasini) + 1));
//	for (int i = 0; i < (*nrMasini); i++)
//	{
//		temp[i] = (*masini)[i];
//	}
//	temp[(*nrMasini)] = masinaNoua;
//	(*nrMasini)++;
//	free(*masini);
//	(*masini) = temp;
//
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	//functia citeste o masina dintr-un strceam deja deschis
//	//masina citita este returnata;
//	char sep[3] = ",\n";
//	char line[101];
//	fgets(line, 100, file);
//	Masina temp;
//	temp.id=atoi(strtok(line,sep));
//	temp.nrUsi = atoi(strtok(NULL, sep));
//	temp.pret = atof(strtok(NULL, sep));
//
//	char* buffer = strtok(NULL, sep);
//	temp.model = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));//strtok nu l pune n heap!!!!!!!!!! chiar daca return char*. Trb sa alocam spatiu in heap^^^^^
//	strcpy_s(temp.model, strlen(buffer) + 1, buffer);
//
//	buffer = strtok(NULL, sep); 
//	temp.numeSofer = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
//	strcpy_s(temp.numeSofer, strlen(buffer) + 1, buffer);
//
//	buffer = strtok(NULL, sep);
//	temp.serie = buffer[0];
//	return temp;
//	
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaFisier()
//	//numarul de masini este determinat prin numarul de citiri din fisier
//	//ATENTIE - la final inchidem fisierul/stream-ul
//
//	FILE* file;
//	file=fopen(numeFisier,"r");
//	Masina* vec;
//	vec = NULL;
//	while (!feof(file)) 
//	{
//		adaugaMasinaInVector(&vec, nrMasiniCitite, citireMasinaFisier(file));
//	}
//	fclose(file);
//	return vec;
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	//este dezalocat intreg vectorul de masini
//	for (int i = 0; i <( *nrMasini); i++) 
//		{
//			free((*vector)[i].model); 
//			free((*vector)[i].numeSofer);
//		}
//	*nrMasini = 0;
//	free(*vector);
//	*vector = NULL;
//}
//
//int main() {
//	int nr = 0;
//	Masina* vectorMasini = NULL;
//	vectorMasini=citireVectorMasiniFisier("masini.txt",&nr );
//	afisareVectorMasini(vectorMasini,nr);
//	return 0;
//}