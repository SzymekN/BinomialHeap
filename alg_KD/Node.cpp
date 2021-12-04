#include "Node.h"

int Node::getValue() {
    if (this)
        return value;
    else
        return -1;
}
Node* Node::getParent() {
    if (this)
        return parent;
    else
        return nullptr;
}
Node* Node::getSibling() {
    if (this)
        return sibling;
    else
        return nullptr;
}
Node* Node::getChild() {
    if (this)
        return child;
    else
        return nullptr;
}
int Node::getDegree() {
    if (this)
        return degree;
    else
        return -1;
}