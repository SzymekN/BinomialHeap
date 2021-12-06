#include <iostream>
#include <locale>
#include "Binomial_Heap.h"

using namespace std;



int main()
{
	setlocale(LC_ALL, "Polish");
	Binomial_Heap* H1 = make_binomial_heap();

	cout << "Korze� kopca H1: " << H1->getRoot() << endl;
	cout << "Rozmiar kopca H1: " << H1->getSize() << endl;
	cout << "Wysoko�� kopca H1: " << H1->getHeight() << endl;


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

	//wg moich oblicze� to powinien by� w�ze� z warto�ci� 20 
	Node* decrease_test = H1->getRoot()->getSibling()->getSibling()->getChild()->getChild()->getChild();
	binomial_heap_decrease_key(H1, decrease_test, 2);
	cout << "\nKopiec H1 po zmianie warto�ci klucza:\n";
	H1->print(H1->getRoot());


	//trzeci korze� na li�cie, z warto�ci� 1
	decrease_test = H1->getRoot()->getSibling()->getSibling();
	cout << "\nKopiec H1 pr�ba zmiany klucza na wi�kszy:\n";
	binomial_heap_decrease_key(H1, decrease_test, 5);
	H1->print(H1->getRoot());

	//nullptr przekazany do funkcji
	decrease_test = nullptr;
	cout << "\nKopiec H1 pr�ba zmiany klucza na wi�kszy:\n";
	binomial_heap_decrease_key(H1, decrease_test, 5);
	H1->print(H1->getRoot());

	cout << "\n\nKorze� kopca H1: " << H1->getRoot()->getValue() << endl;
	cout << "Rozmiar kopca H1: " << H1->getSize() << endl;
	cout << "Wysoko�� kopca H1: " << H1->getHeight() << endl;

	//EXTRACT MIN TEST
	int min;

	//usuwanie z ostatniego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuni�ta warto��: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout<<"\nUsuni�ta warto��: "<<min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z pierwszego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuni�ta warto��: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	cout << "\nKopiec H1 - usuwanie korzenia, ze �rodkowego drzewa: " << endl;
	H1 = binomial_heap_insert(H1, 1);
	H1 = binomial_heap_insert(H1, 5);
	H1->print(H1->getRoot());

	//usuwanie z drugiego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuni�ta warto��: " << min;
	cout << "\nKopiec H1: " << endl;
	H1->print(H1->getRoot());

	//usuwanie z ostatniego drzewa
	min = binomial_heap_extract_min(H1)->getValue();
	cout << "\nUsuni�ta warto��: " << min;
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

	cout << "Kopiec H2: " << endl;

	H2->print(H2->getRoot());

	Node* delete_test = H2->getRoot()->getChild(); //wska�nik na w�ze� przechowuj�cy warto�c 4 tak jak w naszym pdfie

	binomial_heap_delete(H2,delete_test);
	cout << endl;
	H2->print(H2->getRoot());
}