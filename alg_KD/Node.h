#ifndef NODE_H
#define NODE_H
#include<limits>

class Node
{
    Node* parent;
    Node* sibling;
    Node* child;
    int value;
    int degree;

public:
    Node(int value, Node* parent, Node* sibling, Node* child, int degree)
    {
        this->value = value;
        this->parent = parent;
        this->sibling = sibling;
        this->child = child;
        this->degree = degree;
    }


    int getValue();
    Node* getParent();
    Node* getSibling();
    Node* getChild();
    int getDegree();

    void setValue(int v) { value = v; }
    void setParent(Node* p) { parent = p; }
    void setSibling(Node* s) { sibling = s; }
    void setChild(Node* c) { child = c; }
    void setDegree(int d) { degree = d; }
};



#endif