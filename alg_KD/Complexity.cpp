#include "Complexity.h"


Binomial_Heap_Complexity* make_binomial_heap_complexity()
{
	Binomial_Heap_Complexity* heap = new Binomial_Heap_Complexity();
	heap->setSize(0);
	heap->setRoot(nullptr);
	return heap;
}

Node* binomial_heap_merge_complexity(Binomial_Heap_Complexity* H1, Binomial_Heap_Complexity* H2, int& cnt)
{
	Node* ptr1 = H1->getRoot();
	Node* ptr2 = H2->getRoot();
	Node* ptrH = nullptr;
	Node* rootList = nullptr;
	
	cnt++;
	if (ptr1 == nullptr && ptr2 == nullptr) return nullptr;
	if (ptr1 == nullptr) {
		delete H1;
		return ptr2;
	}
	if (ptr2 == nullptr) {
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

	return rootList;
}

void binomial_link_complexity(Node* n1, Node* n2)
{
	n1->setParent(n2);
	n1->setSibling(n2->getChild());
	n2->setChild(n1);
	n2->setDegree(n2->getDegree() + 1);
}

Binomial_Heap_Complexity* binomial_heap_union_complexity(Binomial_Heap_Complexity* H1, Binomial_Heap_Complexity* H2, int& cnt)
{
	Binomial_Heap_Complexity* newHeap = make_binomial_heap_complexity();
	Node* rootList = binomial_heap_merge_complexity(H1, H2,cnt);
	newHeap->setRoot(rootList);

	if (newHeap->getRoot() == nullptr) return newHeap;



	Node* rootPrev = nullptr;
	Node* root = newHeap->getRoot();
	Node* rootNext = root->getSibling();

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
				binomial_link_complexity(rootNext, root);
			}
			else {
				if (rootPrev == nullptr) {
					newHeap->setRoot(rootNext);		// przypadek 4
				}
				else {
					rootPrev->setSibling(rootNext);
				}
				binomial_link_complexity(root, rootNext);
				root = rootNext;
			}
		}
		rootNext = root->getSibling();
	}


	return newHeap;
}

Binomial_Heap_Complexity* binomial_heap_insert_complexity(Binomial_Heap_Complexity* H, int key, int& cnt)
{
	// tymczasowy kopiec z 1 wezlem
	Binomial_Heap_Complexity* temp = make_binomial_heap_complexity();
	Node* n = new Node(key, nullptr, nullptr, nullptr, 0);
	temp->setRoot(n);

	int newSize = H->getSize() + 1;

	Binomial_Heap_Complexity* newHeap = binomial_heap_union_complexity(H, temp, cnt);

	newHeap->setSize(newSize);

	return newHeap;
}

void delete_heap_complexity(Node* root)
{
	if (root->getChild() != nullptr) deleteHeap(root->getChild());
	if (root->getSibling() != nullptr) deleteHeap(root->getSibling());

	std::cout << "Deleting: " << root->getValue() << std::endl;
	delete root;
}

int Binomial_Heap_Complexity::getHeight()
{
	if (this->size)
		return floor(log2(this->size));
	return 0;
}


Node* binomial_heap_minimum_complexity(Binomial_Heap_Complexity* H, int& cnt)
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

void binomial_heap_decrease_key_complexity(Binomial_Heap_Complexity* H, Node* ptr, int value, int& cnt)
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

Node* binomial_heap_extract_min_complexity(Binomial_Heap_Complexity*& H, int& cnt)
{
	Node* min = binomial_heap_minimum_complexity(H,cnt);
	Node* tmp = H->getRoot();									//zmienna pozwalalaj¹ca na poruszanie siê po liœcie korzeni kopca H; wskaŸnik do powsta³ej listy korzeni kopca H`
	Node* minCh = min->getChild();								//wskaŸnik do poruszania siê po liœcie synów minimalnego korzenia
	Node* secondRoot = H->getRoot()->getSibling();				//drugi korzeñ na liœcie, potrzebny jeœli usuwan¹ wartoœci¹ jest pierwszy korzeñ
	min->setChild(nullptr);										//zerwanie po³aczenia minimalnego wêz³a z jego synami
	std::vector<Node*> tabN;									//wektor wskaŸników na wêz³y bêd¹ce dzieæmi minimalnego korzenia 
	cnt++;
	while (tmp->getSibling() != min && tmp != min) {
		cnt++;
		tmp = tmp->getSibling();
	}
	if (tmp != min) {
		if (tmp->getSibling()->getSibling() == nullptr)
			tmp->setSibling(nullptr);	//usuniêcie korzenia o minimalnej wartoœci wêz³a z listy korzeni (wskaŸnik brata ustawiany jest na nullptr, poniewa¿ usuwany korzeñ jest ostatnim na liœcie korzeni)
		else
			tmp->setSibling(tmp->getSibling()->getSibling()); //usuniêcie korzenia o minimalnej wartoœci wêz³a z listy korzeni( sytuacja, w której wêze³ usuwany nie jest ostatnim korzeniem na liœcie korzeni)
	}


	Binomial_Heap_Complexity* newHeap = make_binomial_heap_complexity();

	if (minCh != nullptr) {			//jeœli usuwany wêze³ nie jest wêz³em o stopniu zerowym

		while (minCh != nullptr) {		//dodanie listy dzieci korzenia minimalnego do wektora
			cnt++;
			tabN.push_back(minCh);
			minCh->setParent(nullptr); //zerwanie po³¹czenia z minimalnym wêz³em
			minCh = minCh->getSibling();
		}


		for (int i = tabN.size() - 1; i > 0; i--) {		//odwrócenie kolejnoœcie elementów na liœcie synów wêz³a minimalnego
			cnt++;
			tabN[i]->setSibling(tabN[i - 1]);
		}
		tabN[0]->setSibling(nullptr); //w przyk³adzie z naszej prezentacji jest to wêze³ o wartoœci 4 i ustawiamy tak wskaŸnik ¿eby nie mia³ brata po prawej stronie

		tmp = tabN[tabN.size() - 1];
	}
	else {	//w przeciwnym wypadku 
		tmp = nullptr;
	}
	newHeap->setRoot(tmp);
	newHeap->setSize(pow(2, min->getDegree()) - 1);

	Binomial_Heap_Complexity* heap = new Binomial_Heap_Complexity();
	if (min != H->getRoot())
		heap = H;
	else if (secondRoot != nullptr)				//jeœli g³owa jest najmniejszym wêz³em							
		heap->setRoot(secondRoot);
	else							//jeœli kopiec dwumianowy sk³ada siê z jednego drzewa dwumianowego
		heap->setRoot(nullptr);

	int size = H->getSize() - 1;

	H = binomial_heap_union_complexity(heap, newHeap,cnt);

	H->setSize(size);

	return min;
}

void binomial_heap_delete_complexity(Binomial_Heap_Complexity*& H, Node* ptr,int& cnt) {

	binomial_heap_decrease_key_complexity(H, ptr, std::numeric_limits<int>::min(), cnt);
	binomial_heap_extract_min_complexity(H, cnt);
}
