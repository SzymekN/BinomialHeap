#ifndef COMPLEXITY_H
#define COMPLEXITY_H

#include "BinomialHeap.h"

class BinomialHeapComplexity
{
	int size;
	Node* root;


public:
	inline void setSize(int x) { size = x; }
	inline void setRoot(Node* ptr) { root = ptr; }

	int getHeight();
	inline int getSize() { return size; }
	inline Node* getRoot() { return root; }

	BinomialHeapComplexity() : size(0), root(nullptr) {};

};


/*
Funkcja zlicza liczbe krokow podczas usuwania ca�ego kopca
@param root - Wska�nik do korzenia kopca
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji 
*/
void deleteHeapComplexity(Node* root, int& cnt);


/*
Funkcja tworzy pusty kopiec dwumianowy
@return Wskaznik do kopca dwumianowego
*/
BinomialHeapComplexity* makeBinomialHeapComplexity();

/*
Funkcja zlicza liczbe krok�w podczas scalania listy korzeni kopcow H1 i H2 w porzadku niemalejacym
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik d drugiego kopca
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
@return Wskaznik do listy korzeni nowo utworzonego kopca
*/
Node* binomialHeapMergeComplexity(BinomialHeapComplexity* H1, BinomialHeapComplexity* H2, int& cnt);

/*
Funkcja ustawia wezel n1 jako nowa glowa listy synow wezla n2
@param n1 - Wskaznik do pierwszego wezla
@param n2 - Wskaznik do drugiego wezla
*/
void binomialLinkComplexity(Node* n1, Node* n2);

/*
Funkcja zlicza liczb� krok�w podczas ��czenia kopca H1 i H2 w jeden kopiec
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik do drugiego kopca
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
@return Wskaznik do nowo utworzonego kopca
*/
BinomialHeapComplexity* binomialHeapUnionComplexity(BinomialHeapComplexity* H1, BinomialHeapComplexity* H2, int& cnt);

/*
Funkcja zlicza liczb� krok�w podczas wstawiania wezla do kopca dwumianowego
@param H - Wskaznik do kopca
@param key - Wartosc klucza nowego wezla
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
@return Wskaznik do kopca
*/
BinomialHeapComplexity* binomialHeapInsertComplexity(BinomialHeapComplexity* H, int key, int& cnt);

/*
Funkcja ta zlicza liczb� krok�w podczas znajdywania w�z�a z minimalnym kluczem w n-w�z�owym kopcu dwumianowym
@param H - Wskaznik do kopca
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
@return Wska�nik do w�z�a z minimalnym kluczem w n-w�z�owym kopcu dwumianowym
*/
Node* binomialHeapMinimumComplexity(BinomialHeapComplexity* H, int& cnt);

/*
Funkcja ta zlicza liczb� krok�w podczas nadawania kluczowi w w�le wskazywanym przez wska�nik ptr now� warto��.
@param H - Wskaznik do kopca
@param ptr - Wska�nik do w�z�a, w kt�rym zostanie zmieniony klucz
@param value - Nowa warto�� klucza
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
*/
void binomialHeapDecreaseKeyComplexity(BinomialHeapComplexity* H, Node* ptr, int value, int& cnt);

/*
Funkcja ta zlicza liczb� krok�w podczas znajdywania, a nast�pnie usuwania w�z�a z minimalnym kluczem z kopca dwumianowego H
@param H - Referencja do wska�nika na kopiec H
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
@return Wska�nik do minimalnego w�z�a
*/
Node* binomialHeapExtractMinComplexity(BinomialHeapComplexity*& H, int& cnt);

/*
Funkcja zlicza liczb� krok�w podczas usuwania w�z�a wskazywanego przez wska�nik ptr w kopcu dwumianowym
@param H - Referencja do wska�nika na kopiec H
@param ptr - Wska�nik do usuwanego w�z�a
@param cnt - Zmienna zliczaj�ca liczb� krok�w podczas wykonywania si� funkcji
*/
void binomialHeapDeleteComplexity(BinomialHeapComplexity*& H, Node* ptr, int& cnt);


#endif

