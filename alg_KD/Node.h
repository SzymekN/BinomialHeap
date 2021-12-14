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
    Node(int value, Node* parent = nullptr, Node* sibling = nullptr, Node* child = nullptr, int degree = 0)
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

    void setValue(int v) { if(this) value = v; }
    void setParent(Node* p) { if(this) parent = p; }
    void setSibling(Node* s) { if(this) sibling = s; }
    void setChild(Node* c) { if(this) child = c; }
    void setDegree(int d) { if(this) degree = d; }
};



#endif