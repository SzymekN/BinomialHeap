#include <iostream>
#include "BinomialHeap.h"
#include "Complexity.h"
using namespace std;

void test();

int main()
{
	BinomialHeap* H1 = makeBinomialHeap();

	cout << "Korzen kopca H1: " << H1->getRoot() << endl;
	cout << "Rozmiar kopca H1: " << H1->getSize() << endl;
	cout << "Wysokosc kopca H1: " << H1->getHeight() << endl;


	/*Budowanie kopca
	15			->		4			->			1
	|				/	|				/	/	|
	18				15	8				4	6	5
					|				/	|	|	|
					20				15	8	9
									|
									20
	*/

	//INSERT TEST
	H1 = binomialHeapInsert(H1, 1);
	H1 = binomialHeapInsert(H1, 5);
	H1 = binomialHeapInsert(H1, 6);
	H1 = binomialHeapInsert(H1, 9);

	H1 = binomialHeapInsert(H1, 4);
	H1 = binomialHeapInsert(H1, 8);
	H1 = binomialHeapInsert(H1, 15);
	H1 = binomialHeapInsert(H1, 20);

	H1 = binomialHeapInsert(H1, 4);
	H1 = binomialHeapInsert(H1, 8);
	H1 = binomialHeapInsert(H1, 15);
	H1 = binomialHeapInsert(H1, 20);

	H1 = binomialHeapInsert(H1, 15);
	H1 = binomialHeapInsert(H1, 18);

	cout << "Kopiec H1: " << endl;
	H1->print(H1->getRoot());


	//DECREASE KEY TEST
	cout << endl << "------------------ DECREASE KEY TEST ------------------" << endl;

	//wêze³ z wartoœci¹ 20 
	Node* decrease_test = H1->getRoot()->getSibling()->getSibling()->getChild()->getChild()->getChild();
	cout << "Zamiana wartosci wezle (znajdujacym sie w drzewie dwumianowym ktorego korzen jest ostatnim na liscie korzeni) z 20 na 2";
	binomialHeapDecreaseKey(H1, decrease_test, 2);
	cout << "\nKopiec H1 po zmianie wartosci klucza:\n";
	H1->print(H1->getRoot());


	//trzeci korzeñ na liœcie, z wartoœci¹ 1
	decrease_test = H1->getRoot()->getSibling()->getSibling();
	cout << "\nKopiec H1 proba zmiany klucza na wiekszy (z 1 na 5):\n";
	binomialHeapDecreaseKey(H1, decrease_test, 5);
	H1->print(H1->getRoot());

	//nullptr przekazany do funkcji
	decrease_test = nullptr;
	cout << "\nKopiec H1 proba zmiany klucza na wiekszy(przekazywany wskaznik wskazuje na nullptr):\n";
	binomialHeapDecreaseKey(H1, decrease_test, 5);
	H1->print(H1->getRoot());

	cout << "\n\nKorzen kopca H1: " << H1->getRoot()->getValue() << endl;
	cout << "Rozmiar kopca H1: " << H1->getSize() << endl;
	cout << "Wysokosc kopca H1: " << H1->getHeight() << endl;

	//EXTRACT MIN TEST
	int min;
	cout << endl << "------------------ EXTRACT MIN TEST ------------------" << endl;

	//usuwanie z ostatniego drzewa
	cout << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni.";
	min = binomialHeapExtractMin(H1)->getValue();
	cout << "\nUsunieta wartosc: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni.";
	min = binomialHeapExtractMin(H1)->getValue();
	cout << "\nUsunieta wartosc: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni.";
	min = binomialHeapExtractMin(H1)->getValue();
	cout << "\nUsunieta wartosc: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (srodkowym) na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 1 oraz wezla o kluczu 5: " << endl;
	H1 = binomialHeapInsert(H1, 1);
	H1 = binomialHeapInsert(H1, 5);
	H1->print(H1->getRoot());

	//usuwanie z drugiego drzewa
	min = binomialHeapExtractMin(H1)->getValue();
	cout << "\nUsunieta wartosc: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (ostatnim) na liscie korzeni.";
	min = binomialHeapExtractMin(H1)->getValue();
	cout << "\nUsunieta wartosc: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());


	cout << endl << "Usuwanie wezla nieposiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 3 oraz wezla o kluczu 1: " << endl;
	H1 = binomialHeapInsert(H1, 3);
	H1 = binomialHeapInsert(H1, 1);
	H1->print(H1->getRoot());

	//usuwanie z pierwszego drzewa
	min = binomialHeapExtractMin(H1)->getValue();
	cout << "\nUsunieta wartosc: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	// MINIMUM TEST
	cout << endl << "------------------ MINIMUM TEST ------------------" << endl;

	Node* minimum = binomialHeapMinimum(H1);		//wskaŸnik na wêze³ przechowuj¹cy najmniejszy klucz
	cout << "Wezel z najmniejszym kluczem w kopcu H1: " << minimum->getValue() << endl;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());


	BinomialHeap* H2 = makeBinomialHeap();

	H2 = binomialHeapInsert(H2, 2);
	H2 = binomialHeapInsert(H2, 17);
	H2 = binomialHeapInsert(H2, 5);
	H2 = binomialHeapInsert(H2, 9);

	H2 = binomialHeapInsert(H2, 4);
	H2 = binomialHeapInsert(H2, 8);
	H2 = binomialHeapInsert(H2, 15);
	H2 = binomialHeapInsert(H2, 20);

	cout << "\n\nKorzen kopca H2: " << H2->getRoot() << endl;
	cout << "Rozmiar kopca H2: " << H2->getSize() << endl;
	cout << "Wysokosc kopca H2: " << H2->getHeight() << endl;

	cout << endl << endl;
	cout << "Kopiec H2: " << endl;
	H2->print(H2->getRoot());

	//DELETE TEST
	cout << endl << "------------------ DELETE TEST ------------------" << endl;
	Node* delete_test = H2->getRoot()->getChild(); //wskaŸnik na wêze³ przechowuj¹cy wartoœc 4 tak jak w naszym pdfie

	cout << "Usuniecie wezla o wartosci 4 z kopca." << endl;
	cout << "Kopiec H2:" << endl;
	binomialHeapDelete(H2, delete_test);
	H2->print(H2->getRoot());

	delete_test = H2->getRoot()->getSibling(); //wskaŸnik na wêze³ przechowuj¹cy wartoœc 5 
	cout << endl << endl << "Usuniecie wezla o wartosci 5 z kopca." << endl;
	cout << "Kopiec H2:" << endl;
	binomialHeapDelete(H2, delete_test);
	H2->print(H2->getRoot());

	delete_test = H2->getRoot()->getSibling()->getChild(); //wskaŸnik na wêze³ przechowuj¹cy wartoœc 15 
	cout << endl << endl << "Usuniecie wezla o wartosci 15 z kopca." << endl;
	cout << "Kopiec H2:" << endl;
	binomialHeapDelete(H2, delete_test);
	H2->print(H2->getRoot());

	// UNION TEST
	cout << endl << "------------------ UNION TEST ------------------" << endl;

	cout << endl << "Testowanie operacji union na kopcach H1 i H2:" << endl;
	BinomialHeap* H3 = binomialHeapUnion(H1, H2);

	cout << "Kopiec H3: " << endl;
	H3->print(H3->getRoot());

	// DELETE HEAP TEST
	cout << endl << "------------------ DELETE HEAP TEST ------------------" << endl;
	deleteHeap(H3->getRoot());


	cout << endl << endl << "Funkcja test zliczajaca liczbe krokow dla wykonanych wczesniej funkcji." << endl;
	test();
}

void test() {

	int cnt = 0;
	BinomialHeapComplexity* H1 = makeBinomialHeapComplexity();

	cout << endl << "------------------ ZLICZANIE KROKOW ------------------" << endl;

	H1 = binomialHeapInsertComplexity(H1, 1, cnt);
	cout << "Liczba krokow dla wykonania pierwszej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 5, cnt);
	cout << "Liczba krokow dla wykonania drugiej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 6, cnt);
	cout << "Liczba krokow dla wykonania trzeciej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 9, cnt);
	cout << "Liczba krokow dla wykonania czwartej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 4, cnt);
	cout << "Liczba krokow dla wykonania piatej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 8, cnt);
	cout << "Liczba krokow dla wykonania szostej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 15, cnt);
	cout << "Liczba krokow dla wykonania siodmej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 20, cnt);
	cout << "Liczba krokow dla wykonania osmej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 4, cnt);
	cout << "Liczba krokow dla wykonania dziewiatej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 8, cnt);
	cout << "Liczba krokow dla wykonania dziesiatej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 15, cnt);
	cout << "Liczba krokow dla wykonania jedenastej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 20, cnt);
	cout << "Liczba krokow dla wykonania dwunastej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 15, cnt);
	cout << "Liczba krokow dla wykonania trzynastej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 18, cnt);
	cout << "Liczba krokow dla wykonania czternastej operacji insert: " << cnt << endl;
	cnt = 0;


	//DECREASE KEY TEST
	cout << endl << "------------------ DECREASE KEY TEST ------------------" << endl;
	//wg moich obliczeñ to powinien byæ wêze³ z wartoœci¹ 20 
	Node* decrease_test = H1->getRoot()->getSibling()->getSibling()->getChild()->getChild()->getChild();
	cout << "Zamiana wartosci wezle (znajdujacym sie w drzewie dwumianowym ktorego korzen jest ostatnim na liscie korzeni) z 20 na 2" << endl;
	binomialHeapDecreaseKeyComplexity(H1, decrease_test, 2, cnt);
	cout << "Liczba krokow dla wykonania pierwszej operacji decrease key: " << cnt << endl;
	cnt = 0;


	//trzeci korzeñ na liœcie, z wartoœci¹ 1
	decrease_test = H1->getRoot()->getSibling()->getSibling();
	cout << "\nKopiec H1 proba zmiany klucza na wiekszy (z 1 na 5):\n";
	binomialHeapDecreaseKeyComplexity(H1, decrease_test, 5, cnt);
	cout << "Liczba krokow dla wykonania drugiej operacji decrease key: " << cnt << endl;
	cnt = 0;

	//nullptr przekazany do funkcji
	decrease_test = nullptr;
	cout << "\nKopiec H1 proba zmiany klucza na wiekszy(przekazywany wskaznik wskazuje na nullptr):\n";
	binomialHeapDecreaseKeyComplexity(H1, decrease_test, 5, cnt);
	cout << "Liczba krokow dla wykonania trzeciej operacji decrease key: " << cnt << endl;
	cnt = 0;

	//EXTRACT MIN TEST
	int min;
	cout << endl << "------------------ EXTRACT MIN TEST ------------------" << endl;
	//usuwanie z ostatniego drzewa
	cout << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni." << endl;
	min = binomialHeapExtractMinComplexity(H1, cnt)->getValue();
	cout << "Liczba krokow dla wykonania pierwszej operacji extract min: " << cnt << endl;
	cnt = 0;

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni." << endl;
	min = binomialHeapExtractMinComplexity(H1, cnt)->getValue();
	cout << "Liczba krokow dla wykonania drugiej operacji extract min: " << cnt << endl;
	cnt = 0;

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni." << endl;
	min = binomialHeapExtractMinComplexity(H1, cnt)->getValue();
	cout << "Liczba krokow dla wykonania trzeciej operacji extract min: " << cnt << endl;
	cnt = 0;

	//cout << "\nKopiec H1 - usuwanie korzenia, ze œrodkowego drzewa: " << endl;
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (srodkowym) na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 1 oraz wezla o kluczu 5: " << endl;
	H1 = binomialHeapInsertComplexity(H1, 1, cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 5, cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;

	//usuwanie z drugiego drzewa
	min = binomialHeapExtractMinComplexity(H1, cnt)->getValue();
	cout << "Liczba krokow dla wykonania czwartej operacji extract min: " << cnt << endl;
	cnt = 0;

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (ostatnim) na liscie korzeni." << endl;
	min = binomialHeapExtractMinComplexity(H1, cnt)->getValue();
	cout << "Liczba krokow dla wykonania piatej operacji extract min: " << cnt << endl;
	cnt = 0;

	//cout << "\nKopiec H1 - usuwanie korzenia, z pierwszego drzewa: " << endl;
	cout << endl << "Usuwanie wezla nieposiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 3 oraz wezla o kluczu 1: " << endl;
	H1 = binomialHeapInsertComplexity(H1, 3, cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomialHeapInsertComplexity(H1, 1, cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;

	//usuwanie z pierwszego drzewa
	min = binomialHeapExtractMinComplexity(H1, cnt)->getValue();
	cout << "Liczba krokow dla wykonania szostej operacji extract min: " << cnt << endl;
	cnt = 0;

	// MINIMUM TEST
	cout << endl << "------------------ MINIMUM TEST ------------------" << endl;
	binomialHeapMinimumComplexity(H1, cnt);
	cout << "Liczba krokow dla wykonania operacji minimum: " << cnt << endl;
	cnt = 0;

	BinomialHeapComplexity* H2 = makeBinomialHeapComplexity();

	cout << endl << "---------- ZLICZANIE KROKOW DLA DRUGIEGO KOPCA--------------" << endl;

	H2 = binomialHeapInsertComplexity(H2, 2, cnt);
	cout << "Liczba krokow dla wykonania pierwszej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 17, cnt);
	cout << "Liczba krokow dla wykonania drugiej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 5, cnt);
	cout << "Liczba krokow dla wykonania trzeciej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 9, cnt);
	cout << "Liczba krokow dla wykonania czwartej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 4, cnt);
	cout << "Liczba krokow dla wykonania piatej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 8, cnt);
	cout << "Liczba krokow dla wykonania szostej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 15, cnt);
	cout << "Liczba krokow dla wykonania siodmej operacji insert: " << cnt << endl;
	cnt = 0;
	H2 = binomialHeapInsertComplexity(H2, 20, cnt);
	cout << "Liczba krokow dla wykonania osmej operacji insert: " << cnt << endl;
	cnt = 0;


	//DELETE TEST
	cout << endl << "------------------ DELETE TEST ------------------" << endl;
	Node* delete_test = H2->getRoot()->getChild();
	binomialHeapDeleteComplexity(H2, delete_test, cnt);
	cout << "Liczba krokow dla wykonania pierwszej operacji delete: " << cnt << endl;
	cnt = 0;


	delete_test = H2->getRoot()->getSibling();
	binomialHeapDeleteComplexity(H2, delete_test, cnt);
	cout << "Liczba krokow dla wykonania drugiej operacji delete: " << cnt << endl;
	cnt = 0;

	delete_test = H2->getRoot()->getSibling()->getChild();
	binomialHeapDeleteComplexity(H2, delete_test, cnt);
	cout << "Liczba krokow dla wykonania trzeciej operacji delete: " << cnt << endl;
	cnt = 0;

	// UNION TEST
	cout << endl << "------------------ UNION TEST ------------------" << endl;
	BinomialHeapComplexity* H3 = binomialHeapUnionComplexity(H1, H2, cnt);
	cout << "Liczba krokow dla wykonania operacji union na kopcach H1 i H2: " << cnt << endl;


	// DELETE HEAP TEST
	cout << endl << "------------------ DELETE HEAP TEST ------------------" << endl;
	deleteHeapComplexity(H3->getRoot(), cnt);
	cout << "Liczba krokow dla usuwania kopca: " << cnt << endl;

	cout << "\nKoniec wywolania funkcji 'Test'." << endl;
}