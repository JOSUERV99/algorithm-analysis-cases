#include "List.h"

template <class T>
class Queue : public List<T> {
    public:
        Queue() : List<T>() {}

        void enqueue(T objectToAdd) {
            this->add(objectToAdd);
        }

        T dequeue() {
            return this->removeFirst();
        }
};