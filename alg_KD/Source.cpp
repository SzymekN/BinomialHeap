#include <iostream>
#include <locale>
#include "Binomial_Heap.h"
#include "Complexity.h"
using namespace std;

void test();

int main()
{
	setlocale(LC_ALL, "Polish");
	Binomial_Heap* H1 = make_binomial_heap();

	cout << "Korzeñ kopca H1: " << H1->getRoot() << endl;
	cout << "Rozmiar kopca H1: " << H1->getSize() << endl;
	cout << "Wysokoœæ kopca H1: " << H1->getHeight() << endl;


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
	H1 = binomial_heap_insert(H1, 1);
	H1 = binomial_heap_insert(H1, 5);
	H1 = binomial_heap_insert(H1, 6);
	H1 = binomial_heap_insert(H1, 9);

	H1 = binomial_heap_insert(H1, 4);
	H1 = binomial_heap_insert(H1, 8);
	H1 = binomial_heap_insert(H1, 15);
	H1 = binomial_heap_insert(H1, 20);

	H1 = binomial_heap_insert(H1, 4);
	H1 = binomial_heap_insert(H1, 8);
	H1 = binomial_heap_insert(H1, 15);
	H1 = binomial_heap_insert(H1, 20);

	H1 = binomial_heap_insert(H1, 15);
	H1 = binomial_heap_insert(H1, 18);

	cout << "Kopiec H1: " << endl;
	H1->print(H1->getRoot());


	//DECREASE KEY TEST
	cout << endl << "------------------ DECREASE KEY TEST ------------------" << endl;
	//wg moich obliczeñ to powinien byæ wêze³ z wartoœci¹ 20 
	Node* decrease_test = H1->getRoot()->getSibling()->getSibling()->getChild()->getChild()->getChild();
	cout << "Zamiana wartosci wezle (znajdujacym sie w drzewie dwumianowym ktorego korzen jest ostatnim na liscie korzeni) z 20 na 2";
	binomial_heap_decrease_key(H1, decrease_test, 2);
	cout << "\nKopiec H1 po zmianie wartoœci klucza:\n";
	H1->print(H1->getRoot());


	//trzeci korzeñ na liœcie, z wartoœci¹ 1
	decrease_test = H1->getRoot()->getSibling()->getSibling();
	cout << "\nKopiec H1 próba zmiany klucza na wiêkszy (z 1 na 5):\n";
	binomial_heap_decrease_key(H1, decrease_test, 5);
	H1->print(H1->getRoot());

	//nullptr przekazany do funkcji
	decrease_test = nullptr;
	cout << "\nKopiec H1 próba zmiany klucza na wiêkszy(przekazywany wskaznik wskazuje na nullptr):\n";
	binomial_heap_decrease_key(H1, decrease_test, 5);
	H1->print(H1->getRoot());

	cout << "\n\nKorzeñ kopca H1: " << H1->getRoot()->getValue() << endl;
	cout << "Rozmiar kopca H1: " << H1->getSize() << endl;
	cout << "Wysokoœæ kopca H1: " << H1->getHeight() << endl;

	//EXTRACT MIN TEST
	int min;
	cout <<endl << "------------------ EXTRACT MIN TEST ------------------" << endl;
	//usuwanie z ostatniego drzewa
	cout << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni.";
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuniêta wartoœæ: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni.";
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuniêta wartoœæ: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni.";
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuniêta wartoœæ: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//cout << "\nKopiec H1 - usuwanie korzenia, ze œrodkowego drzewa: " << endl;
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (œrodkowym) na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 1 oraz wezla o kluczu 5: " << endl;
	H1 = binomial_heap_insert(H1, 1);
	H1 = binomial_heap_insert(H1, 5);
	H1->print(H1->getRoot());

	//usuwanie z drugiego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuniêta wartoœæ: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (ostatnim) na liscie korzeni.";
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuniêta wartoœæ: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//cout << "\nKopiec H1 - usuwanie korzenia, z pierwszego drzewa: " << endl;
	cout << endl << "Usuwanie wezla nieposiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 3 oraz wezla o kluczu 1: " << endl;
	H1 = binomial_heap_insert(H1, 3);
	H1 = binomial_heap_insert(H1, 1);
	H1->print(H1->getRoot());

	//usuwanie z pierwszego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuniêta wartoœæ: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	Binomial_Heap* H2 = make_binomial_heap();

	cout << "\n\nKorzen kopca H2: " << H2->getRoot() << endl;
	cout << "Rozmiar kopca H2: " << H2->getSize() << endl;
	cout << "Wysokosc kopca H2: " << H2->getHeight() << endl;

	H2 = binomial_heap_insert(H2, 2);
	H2 = binomial_heap_insert(H2, 17);
	H2 = binomial_heap_insert(H2, 5);
	H2 = binomial_heap_insert(H2, 9);

	H2 = binomial_heap_insert(H2, 4);
	H2 = binomial_heap_insert(H2, 8);
	H2 = binomial_heap_insert(H2, 15);
	H2 = binomial_heap_insert(H2, 20);

	cout <<endl<<endl<< "Funkcja test zliczajaca liczbe krokow dla wykonanych wczesniej funkcji." << endl;
	test();
	cout << endl << endl;
	cout << "Kopiec H2: " << endl;

	H2->print(H2->getRoot());
	cout << endl << "------------------ DELETE TEST ------------------" << endl;
	Node* delete_test = H2->getRoot()->getChild(); //wskaŸnik na wêze³ przechowuj¹cy wartoœc 4 tak jak w naszym pdfie
	
	cout << "Usuniecie wezla o wartosci 4 z kopca." << endl;
	cout << "Kopiec H2:" << endl;
	binomial_heap_delete(H2, delete_test);
	H2->print(H2->getRoot());
}

void test() {

	int cnt = 0;
	Binomial_Heap_Complexity* H1 = make_binomial_heap_complexity();

	
	H1 = binomial_heap_insert_complexity(H1, 1,cnt);
	cout << "Liczba krokow dla wykonania pierwszej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 5, cnt);
	cout << "Liczba krokow dla wykonania drugiej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 6, cnt);
	cout << "Liczba krokow dla wykonania trzeciej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 9, cnt);
	cout << "Liczba krokow dla wykonania czwartej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 4, cnt);
	cout << "Liczba krokow dla wykonania piatej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 8, cnt);
	cout << "Liczba krokow dla wykonania szostej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 15, cnt);
	cout << "Liczba krokow dla wykonania siodmej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 20, cnt);
	cout << "Liczba krokow dla wykonania osmej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 4, cnt);
	cout << "Liczba krokow dla wykonania dziewiatej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 8, cnt);
	cout << "Liczba krokow dla wykonania dziesiatej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 15, cnt);
	cout << "Liczba krokow dla wykonania jedenastej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 20, cnt);
	cout << "Liczba krokow dla wykonania dwunastej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 15, cnt);
	cout << "Liczba krokow dla wykonania trzynastej operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 18, cnt);
	cout << "Liczba krokow dla wykonania czternastej operacji insert: " << cnt << endl;
	cnt = 0;


	//DECREASE KEY TEST
	cout << endl << "------------------ DECREASE KEY TEST ------------------" << endl;
	//wg moich obliczeñ to powinien byæ wêze³ z wartoœci¹ 20 
	Node* decrease_test = H1->getRoot()->getSibling()->getSibling()->getChild()->getChild()->getChild();
	cout << "Zamiana wartosci wezle (znajdujacym sie w drzewie dwumianowym ktorego korzen jest ostatnim na liscie korzeni) z 20 na 2"<<endl;
	binomial_heap_decrease_key_complexity(H1, decrease_test, 2, cnt);
	cout << "Liczba krokow dla wykonania pierwszej operacji decrease key: " << cnt << endl;
	cnt = 0;


	//trzeci korzeñ na liœcie, z wartoœci¹ 1
	decrease_test = H1->getRoot()->getSibling()->getSibling();
	cout << "\nKopiec H1 próba zmiany klucza na wiêkszy (z 1 na 5):\n";
	binomial_heap_decrease_key_complexity(H1, decrease_test, 5,cnt);
	cout << "Liczba krokow dla wykonania drugiej operacji decrease key: " << cnt << endl;
	cnt = 0;

	//nullptr przekazany do funkcji
	decrease_test = nullptr;
	cout << "\nKopiec H1 próba zmiany klucza na wiêkszy(przekazywany wskaznik wskazuje na nullptr):\n";
	binomial_heap_decrease_key_complexity(H1, decrease_test, 5,cnt);
	cout << "Liczba krokow dla wykonania trzeciej operacji decrease key: " << cnt << endl;
	cnt = 0;

	//EXTRACT MIN TEST
	int min;
	cout << endl << "------------------ EXTRACT MIN TEST ------------------" << endl;
	//usuwanie z ostatniego drzewa
	cout << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni." << endl;
	min = binomial_heap_extract_min_complexity(H1,cnt)->getValue();
	cout << "Liczba krokow dla wykonania pierwszej operacji extract min: " << cnt << endl;
	cnt = 0;

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem ostatnim na liscie korzeni." << endl;
	min = binomial_heap_extract_min_complexity(H1,cnt)->getValue();
	cout << "Liczba krokow dla wykonania drugiej operacji extract min: " << cnt << endl;
	cnt = 0;

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni." << endl;
	min = binomial_heap_extract_min_complexity(H1,cnt)->getValue();
	cout << "Liczba krokow dla wykonania trzeciej operacji extract min: " << cnt << endl;
	cnt = 0;

	//cout << "\nKopiec H1 - usuwanie korzenia, ze œrodkowego drzewa: " << endl;
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (œrodkowym) na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 1 oraz wezla o kluczu 5: " << endl;
	H1 = binomial_heap_insert_complexity(H1, 1,cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 5,cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;

	//usuwanie z drugiego drzewa
	min = binomial_heap_extract_min_complexity(H1,cnt)->getValue();
	cout << "Liczba krokow dla wykonania czwartej operacji extract min: " << cnt << endl;
	cnt = 0;

	//usuwanie z ostatniego drzewa
	cout << endl << "Usuwanie wezla posiadajacego dzieci oraz bedacego korzeniem drugim (ostatnim) na liscie korzeni." << endl;
	min = binomial_heap_extract_min_complexity(H1,cnt)->getValue();
	cout << "Liczba krokow dla wykonania piatej operacji extract min: " << cnt << endl;
	cnt = 0;

	//cout << "\nKopiec H1 - usuwanie korzenia, z pierwszego drzewa: " << endl;
	cout << endl << "Usuwanie wezla nieposiadajacego dzieci oraz bedacego korzeniem pierwszym na liscie korzeni." << endl;
	cout << "Kopiec H1 po dodaniu wezla o kluczu 3 oraz wezla o kluczu 1: " << endl;
	H1 = binomial_heap_insert_complexity(H1, 3,cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;
	H1 = binomial_heap_insert_complexity(H1, 1,cnt);
	cout << "Liczba krokow dla wykonania operacji insert: " << cnt << endl;
	cnt = 0;

	//usuwanie z pierwszego drzewa
	min = binomial_heap_extract_min_complexity(H1,cnt)->getValue();
	cout << "Liczba krokow dla wykonania szostej operacji extract min: " << cnt << endl;
	cnt = 0;

	cout << "Koniec wywolania funkcji 'Test'." << endl;
}