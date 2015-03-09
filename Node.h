// Node.h
// Author: Ali Selcuk AKYUZ
// Mail: selcuk@retinarobotics.com || e174043@metu.edu.tr
// Electrical and Electronics Engineering Department
// Middle East Technical University - ANKARA 
// If any questions please send me an email

#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

template<class T>
class Node
{
    public:
        Node();
        Node(const T& item, Node<T>* ptrnext = NULL);
        T data;
        // access to the next node
        Node<T>* NextNode();
        // list modification methods
        void InsertAfter(Node<T>* p);
        Node<T>* DeleteAfter();
        Node<T> * GetNode(const T& item, Node<T>* nextptr = NULL);
    private:

        Node<T> * next;
};

#endif // NODE_H 

