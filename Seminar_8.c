#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Quiz Quiz;
typedef struct Heap Heap;

struct Quiz {
	char* materie;
	int grileGresite;
};

struct Heap {
	Quiz* vector;
	int dimensiune;
	int dimensiuneTotala;
};

Heap initializareHeap(int nr) 
{
	Heap heap;
	heap.vector = malloc(nr * sizeof(Quiz));
	heap.dimensiuneTotala = nr;
	heap.dimensiune = 0;
	return heap;
}

Heap adaugareQuizInHeap(Quiz quiz, Heap heap) 
{
	if (heap.dimensiune < heap.dimensiuneTotala) {
		heap.vector[heap.dimensiune] = quiz;
		heap.dimensiune++;
	}
	return heap;
}

Quiz initializareQuiz(const char* materie, int grileGresite) 
{
	Quiz q;
	q.materie = (char*)malloc(strlen(materie) + 1);
	strcpy(q.materie, materie);
	q.grileGresite = grileGresite;
	return q;
}

void afisareQuiz(Quiz quiz) 
{
	printf("Materia: %s\n", quiz.materie);
	printf("Numarul de grile gresite: %d\n", quiz.grileGresite);
	printf("\n");
}

void afisareHeap(Heap heap)
{
	for (int i = 0;i < heap.dimensiune;i++) {
		afisareQuiz(heap.vector[i]);
		printf("\n");
	}
}

void filtreazaHeap(Heap heap, int pozRadacina)
{
	int nodSt = pozRadacina * 2 + 1;
	int nodDR = pozRadacina * 2 + 2;
	int pozMin = pozRadacina;
	if (nodSt < heap.dimensiune && heap.vector[nodSt].grileGresite < heap.vector[pozMin].grileGresite) {
		pozMin = nodSt;
	}
	if (nodSt < heap.dimensiune && heap.vector[nodSt].grileGresite < heap.vector[pozMin].grileGresite) {
		pozMin = nodSt;
	}

	if (pozMin != pozRadacina) {
		Quiz aux;
		aux = heap.vector[pozRadacina];
		heap.vector[pozRadacina] = heap.vector[pozMin];
		heap.vector[pozMin] = aux;
		if (pozMin * 2 + 1 < heap.dimensiune);
		filtreazaHeap(heap, pozMin);
	}

}

Quiz extragereMinima(Heap* heap)
{
	if (heap->dimensiune > 0) {
		Quiz aux;
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dimensiune - 1];
		heap->vector[heap->dimensiune - 1] = aux;
		heap->dimensiune--;

		for (int i = heap->dimensiune / 2 - 1;i >= 0;i--) {
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
	else {
		return initializareQuiz("N/A", -1);
	}
}

void dezalocareTotHeap(Heap* heap) 
{
	for (int i = 0;i < heap->dimensiuneTotala;i++) {
		free()
	}
}

void main()
{
	Heap heap;
	heap = initializareHeap(6);
	heap.vector[0] = initializareQuiz("Structuri de date", 3);
	heap.vector[1] = initializareQuiz("Java", 7);
	heap.vector[2] = initializareQuiz("Baze de date", 5);
	heap.vector[3] = initializareQuiz("ATP", 2);
	heap.vector[4] = initializareQuiz("POO", 9);
	heap.vector[5] = initializareQuiz("Analiza", 4);

	heap.dimensiune = 6;

	afisareHeap(heap);

	for (int i = heap.dimensiune / 2 - 1;i >= 0;i--) {
		filtreazaHeap(heap, i);
	}
	afisareHeap(heap);

	printf("\n");

	afisareQuiz(extragereMinima(&heap));
	afisareQuiz(extragereMinima(&heap));
	afisareQuiz(extragereMinima(&heap));
	afisareQuiz(extragereMinima(&heap));
	afisareQuiz(extragereMinima(&heap));
	afisareQuiz(extragereMinima(&heap));
	printf("\n");
	afisareHeap(heap);
}
