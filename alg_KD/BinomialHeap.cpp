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
	Node* rootList = nullptr;		// wskaŸnik na now¹ g³owê w kopcu

	// jeœli obydwa kopce s¹ puste, nie ³¹cz
	if (ptr1 == nullptr && ptr2 == nullptr) 
		return nullptr;

	// jeœli H1 jest pusty zwóræ H2
	if (ptr1 == nullptr) 
	{
		delete H1;
		return ptr2;
	}

	// jeœli H2 jest pusty zwóræ H1
	if (ptr2 == nullptr) 
	{
		delete H2;
		return ptr1;
	}


	// ustawianie g³owy kopca na korzeñ o ni¿szym stopniu
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

	// Jeœli kopiec jest pusty, przerwij 
	if (newHeap->getRoot() == nullptr) 
		return newHeap;

	Node* rootPrev = nullptr;				// poprzedni korzeñ
	Node* root = newHeap->getRoot();		// aktualny korzeñ
	Node* rootNext = root->getSibling();	// nastêpny korzeñ

	while (rootNext != nullptr)
	{
		if (root->getDegree() != rootNext->getDegree() ||
			(rootNext->getSibling() != nullptr && rootNext->getSibling()->getDegree() == root->getDegree()))
		{
			rootPrev = root;			// przypadki 1 i 2 - przesuwanie wskaŸnika o jeden dalej w przypadkach 
			root = rootNext;			// gdy s¹siaduj¹ce wêz³y s¹ ró¿nych stopni lub 3 wêz³y o tych samych stopniach s¹ ko³o siebie
		}
		else
		{
			if (root->getValue() <= rootNext->getValue()) {
				root->setSibling(rootNext->getSibling());		// przypadek 3 - dwa korzenie o tym samym stopniu, wczeœniejszy ma mniejsz¹ wartoœæ
				binomialLink(rootNext, root);
			}
			else {										// przypadek 4
				if (rootPrev == nullptr) {				// jeœli poprzedni wêze³ nie istnieje, nastêpny staje siê nowym korzeniem	
					newHeap->setRoot(rootNext);		
				}
				else {
					rootPrev->setSibling(rootNext);		// w przeciwnym wypadku brat poprzedniego to korzeñ nastêpnego (bo aktualny jest dowi¹zywany ni¿ej)
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

	// ³¹czenie kopca przekazanego kopca z nowym posiadaj¹cym 1 wêze³
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
	// jeœli jest to brat poprzedniego wêz³a wyœwietl now¹ ga³¹Ÿ
	if (sibling) 
	{
		std::cout << std::endl;

		// zape³nij bia³ymi znakami w zale¿noœci od g³ebokoœci w drzewie
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
	// wyœwietl najpierw dzieci
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
	Node* min_ptr = nullptr;					// wskaŸnik na wêze³ z wartoœci¹ minimaln¹
	Node* root = H->getRoot();					// korzeñ
	int min = std::numeric_limits<int>::max();	// wartoœæ minimalna

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

	// jeœli przekazana wartoœæ nie spe³nia warunków zakoñcz dzia³anie
	if (value > ptr->getValue()) 
	{
		std::cout << "ERROR: Wrong value" << std::endl;
		return;
	}

	ptr->setValue(value);
	Node* parent = ptr->getParent();

	// wynurz wêze³ po zmianie wartoœci
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
	Node* tmp = H->getRoot();							// zmienna pozwalalaj¹ca na poruszanie siê po liœcie korzeni kopca H; wskaŸnik do powsta³ej listy korzeni kopca H`
	Node* minCh = min->getChild();						// wskaŸnik do poruszania siê po liœcie synów minimalnego korzenia
	Node* secondRoot = H->getRoot()->getSibling();		// drugi korzeñ na liœcie, potrzebny jeœli usuwan¹ wartoœci¹ jest pierwszy korzeñ
	min->setChild(nullptr);								// zerwanie po³aczenia minimalnego wêz³a z jego synami
	std::vector<Node*> tabN;							// wektor wskaŸników na wêz³y bêd¹ce dzieæmi minimalnego korzenia 

	// ustaw tmp na wêze³ poprzedzaj¹cy minimum 
	while (tmp->getSibling() != min && tmp != min) {	
		tmp = tmp->getSibling();
	}

	// jeœli min nie jest pierwszym korzeniem kopca 
	if (tmp != min) {
		if (tmp->getSibling()->getSibling() == nullptr)
			tmp->setSibling(nullptr);							// usuniêcie korzenia o minimalnej wartoœci wêz³a z listy korzeni (wskaŸnik brata ustawiany jest na nullptr, poniewa¿ usuwany korzeñ jest ostatnim na liœcie korzeni)
		else
			tmp->setSibling(tmp->getSibling()->getSibling());	// usuniêcie korzenia o minimalnej wartoœci wêz³a z listy korzeni( sytuacja, w której wêze³ usuwany nie jest ostatnim korzeniem na liœcie korzeni)
	}


	BinomialHeap* newHeap = makeBinomialHeap();		// kopiec z list¹ korzeni dziecka wêz³a minimalnego

	// jeœli usuwany wêze³ nie jest wêz³em o stopniu zerowym
	if (minCh != nullptr) {					

		// dodanie listy dzieci korzenia minimalnego do wektora
		while (minCh != nullptr) {			
			tabN.push_back(minCh);
			minCh->setParent(nullptr);		// zerwanie po³¹czenia z minimalnym wêz³em
			minCh = minCh->getSibling();
		}

		// odwrócenie kolejnoœcie elementów na liœcie synów wêz³a minimalnego
		for (int i = tabN.size() - 1; i > 0; i--) {		

			tabN[i]->setSibling(tabN[i - 1]);
		}

		tabN[0]->setSibling(nullptr);		// pierwszy wêze³ (o najwy¿szym stopniu) ustawiamy najbardziej na prawo, czyli nie ma brata

		tmp = tabN[tabN.size() - 1];
	}
	else {									// w przeciwnym wypadku lista korzeni dziecka nie istnieje
		tmp = nullptr;
	}


	newHeap->setRoot(tmp);
	newHeap->setSize(pow(2, min->getDegree()) - 1);

	BinomialHeap* heap = new BinomialHeap();
	if (min != H->getRoot())				// jeœli g³owa nie jest najmniejszym wêz³em
		heap = H;
	else if (secondRoot != nullptr)			// jeœli g³owa jest najmniejszym wêz³em							
		heap->setRoot(secondRoot);
	else									// jeœli kopiec dwumianowy sk³ada siê z jednego drzewa dwumianowego
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
