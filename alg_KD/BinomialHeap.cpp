#include "BinomialHeap.h"

BinomialHeap* makeBinomialHeap()
{
	BinomialHeap* heap = new BinomialHeap();
	heap->setSize(0);
	heap->setRoot(nullptr);

	return heap;
}

Node* binomialHeapMerge(BinomialHeap* H1, BinomialHeap* H2)
{
	Node* ptr1 = H1->getRoot();
	Node* ptr2 = H2->getRoot();
	Node* ptrH = nullptr;			// pomocnicza zmienna do tworzenia nowej listy korzeni 
	Node* rootList = nullptr;		// wska�nik na now� g�ow� w kopcu

	// je�li obydwa kopce s� puste, nie ��cz
	if (ptr1 == nullptr && ptr2 == nullptr) 
		return nullptr;

	// je�li H1 jest pusty zw�r� H2
	if (ptr1 == nullptr) 
	{
		delete H1;
		return ptr2;
	}

	// je�li H2 jest pusty zw�r� H1
	if (ptr2 == nullptr) 
	{
		delete H2;
		return ptr1;
	}


	// ustawianie g�owy kopca na korze� o ni�szym stopniu
	if (ptr1->getDegree() < ptr2->getDegree())
	{
		rootList = ptr1;
		ptrH = rootList;
		ptr1 = ptr1->getSibling();
	}
	else
	{
		rootList = ptr2;
		ptrH = rootList;
		ptr2 = ptr2->getSibling();
	}

	// ustawianie nowej listy korzeni w porzadku niemalejacym
	while (ptr1 != nullptr && ptr2 != nullptr)		
	{
		if (ptr1->getDegree() < ptr2->getDegree())
		{
			ptrH->setSibling(ptr1);
			ptrH = ptrH->getSibling();
			ptr1 = ptr1->getSibling();
		}
		else
		{
			ptrH->setSibling(ptr2);
			ptrH = ptrH->getSibling();
			ptr2 = ptr2->getSibling();
		}
	}

	// dopisywanie pozostalych korzeni do listy korzeni nowego kopca
	if (ptr1 == nullptr)			
	{
		while (ptr2 != nullptr)
		{
			ptrH->setSibling(ptr2);
			ptrH = ptrH->getSibling();
			ptr2 = ptr2->getSibling();
		}
	}
	else if (ptr2 == nullptr)
	{
		while (ptr1 != nullptr)
		{
			ptrH->setSibling(ptr1);
			ptrH = ptrH->getSibling();
			ptr1 = ptr1->getSibling();
		}
	}

	delete H1;
	delete H2;
	H1 = nullptr;
	H2 = nullptr;
	return rootList;
}

void binomialLink(Node* n1, Node* n2)
{
	n1->setParent(n2);
	n1->setSibling(n2->getChild());
	n2->setChild(n1);
	n2->setDegree(n2->getDegree() + 1);
}

BinomialHeap* binomialHeapUnion(BinomialHeap* H1, BinomialHeap* H2)
{
	BinomialHeap* newHeap = makeBinomialHeap();
	Node* rootList = binomialHeapMerge(H1, H2);
	newHeap->setRoot(rootList);

	// Je�li kopiec jest pusty, przerwij 
	if (newHeap->getRoot() == nullptr) 
		return newHeap;

	Node* rootPrev = nullptr;				// poprzedni korze�
	Node* root = newHeap->getRoot();		// aktualny korze�
	Node* rootNext = root->getSibling();	// nast�pny korze�

	while (rootNext != nullptr)
	{
		if (root->getDegree() != rootNext->getDegree() ||
			(rootNext->getSibling() != nullptr && rootNext->getSibling()->getDegree() == root->getDegree()))
		{
			rootPrev = root;			// przypadki 1 i 2 - przesuwanie wska�nika o jeden dalej w przypadkach 
			root = rootNext;			// gdy s�siaduj�ce w�z�y s� r�nych stopni lub 3 w�z�y o tych samych stopniach s� ko�o siebie
		}
		else
		{
			if (root->getValue() <= rootNext->getValue()) {
				root->setSibling(rootNext->getSibling());		// przypadek 3 - dwa korzenie o tym samym stopniu, wcze�niejszy ma mniejsz� warto��
				binomialLink(rootNext, root);
			}
			else {										// przypadek 4
				if (rootPrev == nullptr) {				// je�li poprzedni w�ze� nie istnieje, nast�pny staje si� nowym korzeniem	
					newHeap->setRoot(rootNext);		
				}
				else {
					rootPrev->setSibling(rootNext);		// w przeciwnym wypadku brat poprzedniego to korze� nast�pnego (bo aktualny jest dowi�zywany ni�ej)
				}
				binomialLink(root, rootNext);
				root = rootNext;
			}
		}
		rootNext = root->getSibling();
	}

	return newHeap;
}

BinomialHeap* binomialHeapInsert(BinomialHeap* H, int key)
{
	// tymczasowy kopiec z 1 wezlem
	BinomialHeap* temp = makeBinomialHeap();
	Node* n = new Node(key);
	int newSize{};

	// ��czenie kopca przekazanego kopca z nowym posiadaj�cym 1 w�ze�
	temp->setRoot(n);
	newSize = H->getSize() + 1;
	BinomialHeap* newHeap = binomialHeapUnion(H, temp);
	newHeap->setSize(newSize);

	return newHeap;
}

void deleteHeap(Node* root)
{
	if (root->getChild() != nullptr) deleteHeap(root->getChild());
	if (root->getSibling() != nullptr) deleteHeap(root->getSibling());

	std::cout << "Deleting: " << root->getValue() << std::endl;
	delete root;
}

int BinomialHeap::getHeight()
{
	if (this->size)
		return floor(log2(this->size));
	return 0;
}

void BinomialHeap::inorder(Node* root)
{
	if (root->getChild() != nullptr) inorder(root->getChild());

	std::cout << root->getValue() << std::endl;

	if (root->getSibling() != nullptr) inorder(root->getSibling());

}

void BinomialHeap::print(Node* root, int depth, bool sibling)
{
	// je�li jest to brat poprzedniego w�z�a wy�wietl now� ga���
	if (sibling) 
	{
		std::cout << std::endl;

		// zape�nij bia�ymi znakami w zale�no�ci od g�eboko�ci w drzewie
		if (depth != 0) 
		{
			std::cout << std::setw(7 * depth) << " " << "|" << std::endl;
			std::cout << std::setw(7 * depth) << " " << "->";
		}
		else 
		{
			std::cout << "|" << std::endl;
			std::cout << "->";
		}

		
	}

	std::cout << std::setw(2) << root->getValue();
	// wy�wietl najpierw dzieci
	if (root->getChild() != nullptr) 
	{
		std::cout << " --> ";
		print(root->getChild(), depth + 1, false);
	}
	if (root->getSibling() != nullptr)
		print(root->getSibling(), depth, true);
}

Node* binomialHeapMinimum(BinomialHeap* H)
{
	Node* min_ptr = nullptr;					// wska�nik na w�ze� z warto�ci� minimaln�
	Node* root = H->getRoot();					// korze�
	int min = std::numeric_limits<int>::max();	// warto�� minimalna

	while (root != nullptr) 
	{
		if (root->getValue() < min) 
		{
			min = root->getValue();
			min_ptr = root;
		}

		root = root->getSibling();
	}

	return min_ptr;
}

void binomialHeapDecreaseKey(BinomialHeap* H, Node* ptr, int value)
{

	// je�li przekazana warto�� nie spe�nia warunk�w zako�cz dzia�anie
	if (value > ptr->getValue()) 
	{
		std::cout << "ERROR: Wrong value" << std::endl;
		return;
	}

	ptr->setValue(value);
	Node* parent = ptr->getParent();

	// wynurz w�ze� po zmianie warto�ci
	while (parent != nullptr and parent->getValue() > ptr->getValue()) 
	{
		int temp = ptr->getValue();
		ptr->setValue(parent->getValue());
		parent->setValue(temp);
		ptr = parent;
		parent = parent->getParent();
	}
}

Node* binomialHeapExtractMin(BinomialHeap*& H) 
{
	Node* min = binomialHeapMinimum(H);
	Node* tmp = H->getRoot();							// zmienna pozwalalaj�ca na poruszanie si� po li�cie korzeni kopca H; wska�nik do powsta�ej listy korzeni kopca H`
	Node* minCh = min->getChild();						// wska�nik do poruszania si� po li�cie syn�w minimalnego korzenia
	Node* secondRoot = H->getRoot()->getSibling();		// drugi korze� na li�cie, potrzebny je�li usuwan� warto�ci� jest pierwszy korze�
	min->setChild(nullptr);								// zerwanie po�aczenia minimalnego w�z�a z jego synami
	std::vector<Node*> tabN;							// wektor wska�nik�w na w�z�y b�d�ce dzie�mi minimalnego korzenia 

	// ustaw tmp na w�ze� poprzedzaj�cy minimum 
	while (tmp->getSibling() != min && tmp != min) {	
		tmp = tmp->getSibling();
	}

	// je�li min nie jest pierwszym korzeniem kopca 
	if (tmp != min) {
		if (tmp->getSibling()->getSibling() == nullptr)
			tmp->setSibling(nullptr);							// usuni�cie korzenia o minimalnej warto�ci w�z�a z listy korzeni (wska�nik brata ustawiany jest na nullptr, poniewa� usuwany korze� jest ostatnim na li�cie korzeni)
		else
			tmp->setSibling(tmp->getSibling()->getSibling());	// usuni�cie korzenia o minimalnej warto�ci w�z�a z listy korzeni( sytuacja, w kt�rej w�ze� usuwany nie jest ostatnim korzeniem na li�cie korzeni)
	}


	BinomialHeap* newHeap = makeBinomialHeap();		// kopiec z list� korzeni dziecka w�z�a minimalnego

	// je�li usuwany w�ze� nie jest w�z�em o stopniu zerowym
	if (minCh != nullptr) {					

		// dodanie listy dzieci korzenia minimalnego do wektora
		while (minCh != nullptr) {			
			tabN.push_back(minCh);
			minCh->setParent(nullptr);		// zerwanie po��czenia z minimalnym w�z�em
			minCh = minCh->getSibling();
		}

		// odwr�cenie kolejno�cie element�w na li�cie syn�w w�z�a minimalnego
		for (int i = tabN.size() - 1; i > 0; i--) {		

			tabN[i]->setSibling(tabN[i - 1]);
		}

		tabN[0]->setSibling(nullptr);		// pierwszy w�ze� (o najwy�szym stopniu) ustawiamy najbardziej na prawo, czyli nie ma brata

		tmp = tabN[tabN.size() - 1];
	}
	else {									// w przeciwnym wypadku lista korzeni dziecka nie istnieje
		tmp = nullptr;
	}


	newHeap->setRoot(tmp);
	newHeap->setSize(pow(2, min->getDegree()) - 1);

	BinomialHeap* heap = new BinomialHeap();
	if (min != H->getRoot())				// je�li g�owa nie jest najmniejszym w�z�em
		heap = H;
	else if (secondRoot != nullptr)			// je�li g�owa jest najmniejszym w�z�em							
		heap->setRoot(secondRoot);
	else									// je�li kopiec dwumianowy sk�ada si� z jednego drzewa dwumianowego
		heap->setRoot(nullptr);

	int size = H->getSize() - 1;
	H = binomialHeapUnion(heap, newHeap);
	H->setSize(size);

	return min;
}

void binomialHeapDelete(BinomialHeap*& H, Node* ptr) {

	binomialHeapDecreaseKey(H, ptr, std::numeric_limits<int>::min());
	binomialHeapExtractMin(H);
}
