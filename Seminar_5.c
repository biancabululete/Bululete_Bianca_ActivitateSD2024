#include <stdio.h>
#include <malloc.h>

/*
	liste simplu inlantuite:
	- structuri de date in care fiecare nod retine informatia utila si adresa urmatorului nod (ultimul nod retine null)
	- zona de memorie necontigua 
	- lista se identifica prin adresa primului nod (cap)
	- 3 modalitati de inserare in lista (inceput, mijloc, final)
*/

typedef struct CafeneauaMea Cafenea;
typedef struct Nod Nod;

struct CafeneauaMea {
	char* nume;
	int nrLocuri;
	float suprafata;
};


struct Nod {
	Cafenea info; //informatia utila
	Nod* next; //pointer la adresa urmatorului nod;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata)
{
	Cafenea cafenea;
	if (nume != NULL)
	{
		cafenea.nrLocuri = nrLocuri;
		cafenea.suprafata = suprafata;
		cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(cafenea.nume, nume);
	}
	return cafenea;
}

//inserare la inceput
Nod* inserareInceput(Cafenea c, Nod* cap)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->next = cap;
	nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
	return nou;
}

void afisareCafenea(Cafenea c)
{
	printf("\nNume: %s", c.nume);
	printf("\nNr scaune: %d", c.nrLocuri);
	printf("\nSuprafata: %.2f\n", c.suprafata);
}

void afisareCafenele(Nod* lista)
{
	while (lista != NULL)
	{
		afisareCafenea(lista->info);
		lista = lista->next;

	}
}

//numele cafenelei care prezinta densitatea cea mai mica
char* numeCafeneaDesintateMinima(Nod* lista)
{
	if (lista != NULL)
	{
		if (lista->info.suprafata != 0)
		{
			float minim = lista->info.nrLocuri / lista->info.suprafata;
			Nod* adresa = lista;
			lista = lista->next;
			while (lista != NULL)
			{
				if (lista->info.nrLocuri / lista->info.suprafata < minim)
				{
					minim= lista->info.nrLocuri / lista->info.suprafata;
					adresa = lista;
				}
				lista = lista->next;
			}
			char* nume = (char*)malloc(sizeof(char) * (strlen(adresa->info.nume) + 1));
			strcpy(nume, adresa->info.nume);
			return nume;
		}
	}
	return NULL;
}

//stergerea listei
void stergereLista(Nod** nod)
{
	while(*nod != NULL)
	{
		Nod* aux;
		aux = *nod;
		*nod = (*nod)->next;
		free(aux->info.nume);
		free(aux);
	}
	*nod = NULL;
}

//inserare la final
void inserareFinal(Nod** lista, Cafenea c)
{
	if (*lista == NULL) {
		(*lista) = inserareInceput(c, *lista);
	}
	else
	{
		Nod* curent = (*lista);
		while (curent->next != NULL) {
			curent = curent->next;
		}
		Nod* n = (Nod*)malloc(sizeof(Nod));
		n->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
		n->next = NULL;
		curent->next = n;
	}
}

void main()
{
	Nod* cap=NULL;
	Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
	cap = inserareInceput(cafenea, cap);
	Cafenea cafenea2 = initializareCafenea("Teds", 17, 17.3);
	cap = inserareInceput(cafenea2, cap);
	Cafenea cafenea3 = initializareCafenea("Urban", 19, 33);
	cap = inserareInceput(cafenea3, cap);
	inserareFinal(&cap, cafenea2);
	afisareCafenele(cap);

	char* numeMinim = numeCafeneaDesintateMinima(cap);
	printf("\nCafeneaua cu densitate minima: %s\n", numeMinim);


	stergereLista(&cap);
	afisareCafenele(cap);

	free(cafenea.nume);
	cafenea.nume = NULL;

	free(cafenea2.nume);
	cafenea2.nume = NULL;

	free(cafenea3.nume);
	cafenea3.nume = NULL;

}
