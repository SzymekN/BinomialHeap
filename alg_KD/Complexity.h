#ifndef COMPLEXITY_H
#define COMPLEXITY_H

#include "Binomial_Heap.h"

class Binomial_Heap_Complexity
{
	int size;
	Node* root;
	

public:
	inline void setSize(int x) { size = x; }
	inline void setRoot(Node* ptr) { root = ptr; }

	int getHeight();
	inline int getSize() { return size; }
	inline Node* getRoot() { return root; }

	Binomial_Heap_Complexity() : size(0), root(nullptr) {};

};


/*
Funkcja usuwa ca³y kopiec
@param root - WskaŸnik do korzenia kopca
*/
void delete_heap_complexity(Node* root, int& cnt);


/*
Funkcja tworzy pusty kopiec dwumianowy
@return Wskaznik do kopca dwumianowego
*/
Binomial_Heap_Complexity* make_binomial_heap_complexity();

/*
Funkcja scala listy korzeni kopcow H1 i H2 w porzadku niemalejacym
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik d drugiego kopca
@return Wskaznik do listy korzeni nowo utworzonego kopca
*/
Node* binomial_heap_merge_complexity(Binomial_Heap_Complexity* H1, Binomial_Heap_Complexity* H2, int& cnt);

/*
Funkcja ustawia wezel n1 jako nowa glowa listy synow wezla n2
@param n1 - Wskaznik do pierwszego wezla
@param n2 - Wskaznik do drugiego wezla
*/
void binomial_link_complexity(Node* n1, Node* n2);

/*
Funkcja laczy kopce H1 i H2 w jeden kopiec
@param H1 - Wskaznik do pierwszego kopca
@param H2 - Wskaznik do drugiego kopca
@return Wskaznik do nowo utworzonego kopca
*/
Binomial_Heap_Complexity* binomial_heap_union_complexity(Binomial_Heap_Complexity* H1, Binomial_Heap_Complexity* H2, int& cnt);

/*
Funkcja wstawia wezel do kopca dwumianowego
@param H - Wskaznik do kopca
@param key - Wartosc klucza nowego wezla
@return Wskaznik do kopca
*/
Binomial_Heap_Complexity* binomial_heap_insert_complexity(Binomial_Heap_Complexity* H, int key, int& cnt);

/*
Funkcja ta znajduje wêze³ z minimalnym kluczem w n-wêz³owym kopcu dwumianowym
@param H - Wskaznik do kopca
@return WskaŸnik do wêz³a z minimalnym kluczem w n-wêz³owym kopcu dwumianowym
*/
Node* binomial_heap_minimum_complexity(Binomial_Heap_Complexity* H, int& cnt);

/*
Funkcja ta nadaje kluczowi w wêŸle wskazywanym przez wskaŸnik ptr now¹ wartoœæ.
@param H - Wskaznik do kopca
@param ptr - WskaŸnik do wêz³a, w którym zostanie zmieniony klucz
@param value - Nowa wartoœæ klucza
*/
void binomial_heap_decrease_key_complexity(Binomial_Heap_Complexity* H, Node* ptr, int value, int& cnt);

/*
Funkcja ta znajudje, a nastêpnie usuwa wêze³ z minimalnym kluczem z kopca dwumianowego H
@param H - Referencja do wskaŸnika na kopiec H
@return WskaŸnik do minimalnego wêz³a
*/
Node* binomial_heap_extract_min_complexity(Binomial_Heap_Complexity*& H, int& cnt);

/*
Funkcja usuwa wêze³ wskazywany przez wskaŸnik ptr w kopcu dwumianowym
@param H - Referencja do wskaŸnika na kopiec H
@param ptr - WskaŸnik do usuwanego wêz³a
*/
void binomial_heap_delete_complexity(Binomial_Heap_Complexity*& H, Node* ptr, int& cnt);


#endif
