#include "Complexity.h"


BinomialHeapComplexity* makeBinomialHeapComplexity()
{
	BinomialHeapComplexity* heap = new BinomialHeapComplexity();
	heap->setSize(0);
	heap->setRoot(nullptr);
	return heap;
}

Node* binomialHeapMergeComplexity(BinomialHeapComplexity* H1, BinomialHeapComplexity* H2, int& cnt)
{
	Node* ptr1 = H1->getRoot();
	Node* ptr2 = H2->getRoot();
	Node* ptrH = nullptr;
	Node* rootList = nullptr;
	
	cnt++;
	if (ptr1 == nullptr && ptr2 == nullptr) return nullptr;

	if (ptr1 == nullptr) 
	{
		delete H1;
		return ptr2;
	}

	if (ptr2 == nullptr) 
	{
		delete H2;
		return ptr1;
	}

	if (ptr1->getDegree() < ptr2->getDegree())		// ustawienie wskaznika ptrH na nowa liste korzeni
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

	while (ptr1 != nullptr && ptr2 != nullptr)		// ustawianie nowej listy korzeni w porzadku niemalejacym
	{
		cnt++;
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

	if (ptr1 == nullptr)			// dopisywanie pozostalych korzeni do listy korzeni nowego kopca
	{
		while (ptr2 != nullptr)
		{
			cnt++;
			ptrH->setSibling(ptr2);
			ptrH = ptrH->getSibling();
			ptr2 = ptr2->getSibling();
		}
	}
	else if (ptr2 == nullptr)
	{
		while (ptr1 != nullptr)
		{
			cnt++;
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

void binomialLinkComplexity(Node* n1, Node* n2)
{
	n1->setParent(n2);
	n1->setSibling(n2->getChild());
	n2->setChild(n1);
	n2->setDegree(n2->getDegree() + 1);
}

BinomialHeapComplexity* binomialHeapUnionComplexity(BinomialHeapComplexity* H1, BinomialHeapComplexity* H2, int& cnt)
{
	BinomialHeapComplexity* newHeap = makeBinomialHeapComplexity();
	Node* rootList = binomialHeapMergeComplexity(H1, H2,cnt);
	newHeap->setRoot(rootList);

	if (newHeap->getRoot() == nullptr) return newHeap;

	Node* rootPrev = nullptr;
	Node* root = newHeap->getRoot();
	Node* rootNext = root->getSibling();

	cnt++;
	while (rootNext != nullptr)
	{
		cnt++;
		if (root->getDegree() != rootNext->getDegree() ||
			(rootNext->getSibling() != nullptr && rootNext->getSibling()->getDegree() == root->getDegree()))
		{
			rootPrev = root;			// przypadki 1 i 2
			root = rootNext;
		}
		else
		{
			if (root->getValue() <= rootNext->getValue()) {
				root->setSibling(rootNext->getSibling());		// przypadek 3
				binomialLinkComplexity(rootNext, root);
			}
			else {
				if (rootPrev == nullptr) {
					newHeap->setRoot(rootNext);		// przypadek 4
				}
				else {
					rootPrev->setSibling(rootNext);
				}
				binomialLinkComplexity(root, rootNext);
				root = rootNext;
			}
		}
		rootNext = root->getSibling();
	}


	return newHeap;
}

BinomialHeapComplexity* binomialHeapInsertComplexity(BinomialHeapComplexity* H, int key, int& cnt)
{
	// tymczasowy kopiec z 1 wezlem
	BinomialHeapComplexity* temp = makeBinomialHeapComplexity();
	Node* n = new Node(key);
	temp->setRoot(n);

	int newSize = H->getSize() + 1;

	BinomialHeapComplexity* newHeap = binomialHeapUnionComplexity(H, temp, cnt);

	newHeap->setSize(newSize);

	return newHeap;
}

void deleteHeapComplexity(Node* root, int& cnt)
{
	if (root->getChild() != nullptr) deleteHeapComplexity(root->getChild(), cnt);
	if (root->getSibling() != nullptr) deleteHeapComplexity(root->getSibling(), cnt);

	cnt++;
	std::cout << "Deleting: " << root->getValue() << std::endl;
	delete root;
}

int BinomialHeapComplexity::getHeight()
{
	if (this->size)
		return floor(log2(this->size));
	return 0;
}


Node* binomialHeapMinimumComplexity(BinomialHeapComplexity* H, int& cnt)
{
	Node* min_ptr = nullptr;
	Node* root = H->getRoot();
	int min = std::numeric_limits<int>::max();

	cnt++;
	while (root != nullptr) {
		cnt++;
		if (root->getValue() < min) {
			min = root->getValue();
			min_ptr = root;
		}
		root = root->getSibling();
	}
	return min_ptr;
}

void binomialHeapDecreaseKeyComplexity(BinomialHeapComplexity* H, Node* ptr, int value, int& cnt)
{
	if (value > ptr->getValue()) {
		std::cout << "ERROR: Wrong value" << std::endl;
		return;
	}
	ptr->setValue(value);
	Node* parent = ptr->getParent();

	cnt++;
	while (parent != nullptr and parent->getValue() > ptr->getValue()) {
		cnt++;
		int temp = ptr->getValue();
		ptr->setValue(parent->getValue());
		parent->setValue(temp);
		ptr = parent;
		parent = parent->getParent();
	}
}

Node* binomialHeapExtractMinComplexity(BinomialHeapComplexity*& H, int& cnt)
{
	Node* min = binomialHeapMinimumComplexity(H,cnt);
	Node* tmp = H->getRoot();									//zmienna pozwalalaj�ca na poruszanie si� po li�cie korzeni kopca H; wska�nik do powsta�ej listy korzeni kopca H`
	Node* minCh = min->getChild();								//wska�nik do poruszania si� po li�cie syn�w minimalnego korzenia
	Node* secondRoot = H->getRoot()->getSibling();				//drugi korze� na li�cie, potrzebny je�li usuwan� warto�ci� jest pierwszy korze�
	min->setChild(nullptr);										//zerwanie po�aczenia minimalnego w�z�a z jego synami
	std::vector<Node*> tabN;									//wektor wska�nik�w na w�z�y b�d�ce dzie�mi minimalnego korzenia 

	cnt++;
	while (tmp->getSibling() != min && tmp != min) {
		cnt++;
		tmp = tmp->getSibling();
	}
	if (tmp != min) {
		if (tmp->getSibling()->getSibling() == nullptr)
			tmp->setSibling(nullptr);							//usuni�cie korzenia o minimalnej warto�ci w�z�a z listy korzeni (wska�nik brata ustawiany jest na nullptr, poniewa� usuwany korze� jest ostatnim na li�cie korzeni)
		else
			tmp->setSibling(tmp->getSibling()->getSibling());	//usuni�cie korzenia o minimalnej warto�ci w�z�a z listy korzeni( sytuacja, w kt�rej w�ze� usuwany nie jest ostatnim korzeniem na li�cie korzeni)
	}


	BinomialHeapComplexity* newHeap = makeBinomialHeapComplexity();

	if (minCh != nullptr) {				//je�li usuwany w�ze� nie jest w�z�em o stopniu zerowym

		while (minCh != nullptr) {		//dodanie listy dzieci korzenia minimalnego do wektora
			cnt++;
			tabN.push_back(minCh);
			minCh->setParent(nullptr);	//zerwanie po��czenia z minimalnym w�z�em
			minCh = minCh->getSibling();
		}


		for (int i = tabN.size() - 1; i > 0; i--) {		//odwr�cenie kolejno�cie element�w na li�cie syn�w w�z�a minimalnego
			cnt++;
			tabN[i]->setSibling(tabN[i - 1]);
		}
		tabN[0]->setSibling(nullptr); //w przyk�adzie z naszej prezentacji jest to w�ze� o warto�ci 4 i ustawiamy tak wska�nik �eby nie mia� brata po prawej stronie

		tmp = tabN[tabN.size() - 1];
	}
	else {	//w przeciwnym wypadku 
		tmp = nullptr;
	}
	newHeap->setRoot(tmp);
	newHeap->setSize(pow(2, min->getDegree()) - 1);

	BinomialHeapComplexity* heap = new BinomialHeapComplexity();
	if (min != H->getRoot())
		heap = H;
	else if (secondRoot != nullptr)				//je�li g�owa jest najmniejszym w�z�em							
		heap->setRoot(secondRoot);
	else							//je�li kopiec dwumianowy sk�ada si� z jednego drzewa dwumianowego
		heap->setRoot(nullptr);

	int size = H->getSize() - 1;

	H = binomialHeapUnionComplexity(heap, newHeap,cnt);

	H->setSize(size);

	return min;
}

void binomialHeapDeleteComplexity(BinomialHeapComplexity*& H, Node* ptr,int& cnt) {

	binomialHeapDecreaseKeyComplexity(H, ptr, std::numeric_limits<int>::min(), cnt);
	binomialHeapExtractMinComplexity(H, cnt);
}
