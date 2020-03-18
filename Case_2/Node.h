template <class T>
class Node {
    public:
        T object;
        Node<T> *nextNode;

        Node()  {
            nextNode = nullptr;
        }
        
        Node(T object) {
            this->object = object;
            nextNode = nullptr;
        }

        ~Node() {}

        Node<T> next() {
            return nextNode;
        }

        T getObject() {
            return object;
        }
        
        bool hasNext() {
            return !( nextNode == nullptr );
        }
};