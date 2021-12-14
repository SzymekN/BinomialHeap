#include "Binomial_Heap.h"

Binomial_Heap* make_binomial_heap()
{
	Binomial_Heap* heap = new Binomial_Heap();
	heap->setSize(0);
	heap->setRoot(nullptr);

	return heap;
}

Node* binomial_heap_merge(Binomial_Heap* H1, Binomial_Heap* H2)
{
	Node* ptr1 = H1->getRoot();
	Node* ptr2 = H2->getRoot();
	Node* ptrH = nullptr;
	Node* rootList = nullptr;

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

void binomial_link(Node* n1, Node* n2)
{
	n1->setParent(n2);
	n1->setSibling(n2->getChild());
	n2->setChild(n1);
	n2->setDegree(n2->getDegree() + 1);
}

Binomial_Heap* binomial_heap_union(Binomial_Heap* H1, Binomial_Heap* H2)
{
	Binomial_Heap* newHeap = make_binomial_heap();
	Node* rootList = binomial_heap_merge(H1, H2);
	newHeap->setRoot(rootList);

	if (newHeap->getRoot() == nullptr) return newHeap;



	Node* rootPrev = nullptr;
	Node* root = newHeap->getRoot();
	Node* rootNext = root->getSibling();

	while (rootNext != nullptr)
	{
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
				binomial_link(rootNext, root);
			}
			else {
				if (rootPrev == nullptr) {
					newHeap->setRoot(rootNext);		// przypadek 4
				}
				else {
					rootPrev->setSibling(rootNext);
				}
				binomial_link(root, rootNext);
				root = rootNext;
			}
		}
		rootNext = root->getSibling();
	}


	return newHeap;
}

Binomial_Heap* binomial_heap_insert(Binomial_Heap* H, int key)
{
	// tymczasowy kopiec z 1 wezlem
	Binomial_Heap* temp = make_binomial_heap();
	Node* n = new Node(key, nullptr, nullptr, nullptr, 0);
	temp->setRoot(n);

	int newSize = H->getSize() + 1;

	Binomial_Heap* newHeap = binomial_heap_union(H, temp);

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

int Binomial_Heap::getHeight()
{
	if (this->size)
		return floor(log2(this->size));
	return 0;
}

void Binomial_Heap::inorder(Node* root)
{
	if (root->getChild() != nullptr) inorder(root->getChild());
	std::cout << root->getValue() << std::endl;
	if (root->getSibling() != nullptr) inorder(root->getSibling());

}

void Binomial_Heap::print(Node* root, int depth, bool sibling)
{

	if (sibling) {
		std::cout << std::endl;
		if (depth != 0) {
			std::cout << std::setw(7 * depth) << " " << "|" << std::endl;
			std::cout << std::setw(7 * depth) << " " << "->";
		}
		else {
			std::cout << "|" << std::endl;
			std::cout << "->";
		}

		
	}
	std::cout << std::setw(2) << root->getValue();
	if (root->getChild() != nullptr) {
		std::cout << " --> ";
		print(root->getChild(), depth + 1, false);
	}
	if (root->getSibling() != nullptr)
		print(root->getSibling(), depth, true);
}

Node* binomial_heap_minimum(Binomial_Heap* H)
{
	Node* min_ptr = nullptr;
	Node* root = H->getRoot();
	int min = std::numeric_limits<int>::max();
	while (root != nullptr) {
		if (root->getValue() < min) {
			min = root->getValue();
			min_ptr = root;
		}
		root = root->getSibling();
	}
	return min_ptr;
}

void binomial_heap_decrease_key(Binomial_Heap* H, Node* ptr, int value)
{
	if (value > ptr->getValue()) {
		std::cout << "ERROR: Wrong value" << std::endl;
		return;
	}
	ptr->setValue(value);
	Node* parent = ptr->getParent();
	while (parent != nullptr and parent->getValue() > ptr->getValue()) {
		int temp = ptr->getValue();
		ptr->setValue(parent->getValue());
		parent->setValue(temp);
		ptr = parent;
		parent = parent->getParent();
	}
}

Node* binomial_heap_extract_min(Binomial_Heap*& H) 
{
	Node* min = binomial_heap_minimum(H);
	Node* tmp = H->getRoot();									//zmienna pozwalalaj¹ca na poruszanie siê po liœcie korzeni kopca H; wskaŸnik do powsta³ej listy korzeni kopca H`
	Node* minCh = min->getChild();								//wskaŸnik do poruszania siê po liœcie synów minimalnego korzenia
	Node* secondRoot = H->getRoot()->getSibling();				//drugi korzeñ na liœcie, potrzebny jeœli usuwan¹ wartoœci¹ jest pierwszy korzeñ
	min->setChild(nullptr);										//zerwanie po³aczenia minimalnego wêz³a z jego synami
	std::vector<Node*> tabN;									//wektor wskaŸników na wêz³y bêd¹ce dzieæmi minimalnego korzenia 

	while (tmp->getSibling() != min && tmp != min) {	
		tmp = tmp->getSibling();
	}
	if (tmp != min) {
		if (tmp->getSibling()->getSibling() == nullptr)
			tmp->setSibling(nullptr);	//usuniêcie korzenia o minimalnej wartoœci wêz³a z listy korzeni (wskaŸnik brata ustawiany jest na nullptr, poniewa¿ usuwany korzeñ jest ostatnim na liœcie korzeni)
		else
			tmp->setSibling(tmp->getSibling()->getSibling()); //usuniêcie korzenia o minimalnej wartoœci wêz³a z listy korzeni( sytuacja, w której wêze³ usuwany nie jest ostatnim korzeniem na liœcie korzeni)
	}


	Binomial_Heap* newHeap = make_binomial_heap();

	if (minCh != nullptr) {			//jeœli usuwany wêze³ nie jest wêz³em o stopniu zerowym

		while (minCh != nullptr) {		//dodanie listy dzieci korzenia minimalnego do wektora
			tabN.push_back(minCh);
			minCh->setParent(nullptr); //zerwanie po³¹czenia z minimalnym wêz³em
			minCh = minCh->getSibling();
		}

		for (int i = tabN.size() - 1; i > 0; i--) {		//odwrócenie kolejnoœcie elementów na liœcie synów wêz³a minimalnego

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

	Binomial_Heap* heap = new Binomial_Heap();
	if (min != H->getRoot())
		heap = H;
	else if (secondRoot != nullptr)				//jeœli g³owa jest najmniejszym wêz³em							
		heap->setRoot(secondRoot);
	else							//jeœli kopiec dwumianowy sk³ada siê z jednego drzewa dwumianowego
		heap->setRoot(nullptr);

	int size = H->getSize() - 1;

	H = binomial_heap_union(heap, newHeap);
	
	H->setSize(size);

	return min;
}

void binomial_heap_delete(Binomial_Heap*& H, Node* ptr) {

	binomial_heap_decrease_key(H, ptr, std::numeric_limits<int>::min());
	binomial_heap_extract_min(H);
}
