#ifndef Binomial_Heap_H
#define Binomial_Heap_H

#include "Node.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>

class BinomialHeap
{
	int size;
	Node* root;

public:
	inline void setSize(int x) { size = x; }
	inline void setRoot(Node* ptr) { root = ptr; }

	int getHeight();
	inline int getSize() { return size; }
	inline Node* getRoot() { return root; }
	void inorder(Node* root);
	void print(Node* root, int depth=0, bool sibling=false);

	BinomialHeap() : size(0), root(nullptr) {};

};

/*
Funkcja usuwa ca�y kopiec
@param root - Wska�nik do korzenia kopca
*/
void deleteHeap(Node* root);


/*
Funkcja tworzy pusty kopiec dwumianowy
@return Wskaznik do kopca dwumianowego
*/
BinomialHeap* makeBinomialHeap();

/*
Funkcja scala listy korzeni kopcow H1 i H2 w porzadku niemalejacym
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik d drugiego kopca
@return Wskaznik do listy korzeni nowo utworzonego kopca
*/
Node* binomialHeapMerge(BinomialHeap* H1, BinomialHeap* H2);

/*
Funkcja ustawia wezel n1 jako nowa glowa listy synow wezla n2
@param n1 - Wskaznik do pierwszego wezla
@param n2 - Wskaznik do drugiego wezla
*/
void binomialLink(Node* n1, Node* n2);

/*
Funkcja laczy kopce H1 i H2 w jeden kopiec
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik do drugiego kopca
@return Wskaznik do nowo utworzonego kopca
*/
BinomialHeap* binomialHeapUnion(BinomialHeap* H1, BinomialHeap* H2);

/*
Funkcja wstawia wezel do kopca dwumianowego
@param H - Wskaznik do kopca
@param key - Wartosc klucza nowego wezla
@return Wskaznik do kopca
*/
BinomialHeap* binomialHeapInsert(BinomialHeap* H, int key);

/*
Funkcja ta znajduje w�ze� z minimalnym kluczem w n-w�z�owym kopcu dwumianowym
@param H - Wskaznik do kopca
@return Wska�nik do w�z�a z minimalnym kluczem w n-w�z�owym kopcu dwumianowym
*/
Node* binomialHeapMinimum(BinomialHeap* H);

/*
Funkcja ta nadaje kluczowi w w�le wskazywanym przez wska�nik ptr now� warto��.
@param H - Wskaznik do kopca
@param ptr - Wska�nik do w�z�a, w kt�rym zostanie zmieniony klucz
@param value - Nowa warto�� klucza
*/
void binomialHeapDecreaseKey(BinomialHeap* H, Node* ptr, int value);

/*
Funkcja ta znajudje, a nast�pnie usuwa w�ze� z minimalnym kluczem z kopca dwumianowego H
@param H - Referencja do wska�nika na kopiec H
@return Wska�nik do minimalnego w�z�a
*/
Node* binomialHeapExtractMin(BinomialHeap*& H);

/*
Funkcja usuwa w�ze� wskazywany przez wska�nik ptr w kopcu dwumianowym
@param H - Referencja do wska�nika na kopiec H
@param ptr - Wska�nik do usuwanego w�z�a
*/
void binomialHeapDelete(BinomialHeap*& H, Node* ptr);

#endif