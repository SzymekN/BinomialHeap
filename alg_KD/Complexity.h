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
Funkcja usuwa ca³y kopiec
@param root - WskaŸnik do korzenia kopca
*/
void deleteHeapComplexity(Node* root, int& cnt);


/*
Funkcja tworzy pusty kopiec dwumianowy
@return Wskaznik do kopca dwumianowego
*/
BinomialHeapComplexity* makeBinomialHeapComplexity();

/*
Funkcja scala listy korzeni kopcow H1 i H2 w porzadku niemalejacym
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik d drugiego kopca
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
Funkcja laczy kopce H1 i H2 w jeden kopiec
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik do drugiego kopca
@return Wskaznik do nowo utworzonego kopca
*/
BinomialHeapComplexity* binomialHeapUnionComplexity(BinomialHeapComplexity* H1, BinomialHeapComplexity* H2, int& cnt);

/*
Funkcja wstawia wezel do kopca dwumianowego
@param H - Wskaznik do kopca
@param key - Wartosc klucza nowego wezla
@return Wskaznik do kopca
*/
BinomialHeapComplexity* binomialHeapInsertComplexity(BinomialHeapComplexity* H, int key, int& cnt);

/*
Funkcja ta znajduje wêze³ z minimalnym kluczem w n-wêz³owym kopcu dwumianowym
@param H - Wskaznik do kopca
@return WskaŸnik do wêz³a z minimalnym kluczem w n-wêz³owym kopcu dwumianowym
*/
Node* binomialHeapMinimumComplexity(BinomialHeapComplexity* H, int& cnt);

/*
Funkcja ta nadaje kluczowi w wêŸle wskazywanym przez wskaŸnik ptr now¹ wartoœæ.
@param H - Wskaznik do kopca
@param ptr - WskaŸnik do wêz³a, w którym zostanie zmieniony klucz
@param value - Nowa wartoœæ klucza
*/
void binomialHeapDecreaseKeyComplexity(BinomialHeapComplexity* H, Node* ptr, int value, int& cnt);

/*
Funkcja ta znajudje, a nastêpnie usuwa wêze³ z minimalnym kluczem z kopca dwumianowego H
@param H - Referencja do wskaŸnika na kopiec H
@return WskaŸnik do minimalnego wêz³a
*/
Node* binomialHeapExtractMinComplexity(BinomialHeapComplexity*& H, int& cnt);

/*
Funkcja usuwa wêze³ wskazywany przez wskaŸnik ptr w kopcu dwumianowym
@param H - Referencja do wskaŸnika na kopiec H
@param ptr - WskaŸnik do usuwanego wêz³a
*/
void binomialHeapDeleteComplexity(BinomialHeapComplexity*& H, Node* ptr, int& cnt);


#endif
