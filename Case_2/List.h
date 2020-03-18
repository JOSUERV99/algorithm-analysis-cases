#include "Node.h"
#include <stdlib.h>

template <class T>
class List {
    protected:
        Node<T> *first;
        Node<T> *last;
    public:
        int length;
        
        List() {
            length = 0;
            first = last = nullptr;    
        }

        ~List() {}

        void add(T objectToAdd) {
            Node<T> *newNode = new Node<T>(objectToAdd);
            if (!first) {
                first =  last = newNode;
                length++;
                return;
            }

            last->nextNode = newNode;
            last = last->nextNode;
            length++;
        }

        T removeFirst() {
            if (first) {
                T valueToReturn = first->getObject();
                Node<T> *toDelete = first;
                first = first->nextNode;
                length--;
                delete toDelete;
                return valueToReturn;
            } return 0;
        }

        T removeLast() {
            if (last) {
                T valueToReturn = last->getObject();
                Node<T> *nodeTemp = first;

                if (first == last) {
                    first = last = nullptr;
                    delete nodeTemp;
                } else {
                    while(nodeTemp) {
                        if (nodeTemp->nextNode == last) {
                            Node<T> *toDelete = last;
                            last = nodeTemp;
                            delete toDelete;
                            break;
                        }
                        nodeTemp = nodeTemp->nextNode;
                    }
                }
                length--;
                return valueToReturn;
            } return 0;
        }

        Node<T> *getFirst() {
            return first;
        }

        Node<T> *getLast() {
            return last;
        }
        
        bool isEmpty() {
            return first == nullptr ;
        }
};