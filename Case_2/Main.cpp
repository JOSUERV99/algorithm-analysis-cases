#include <iostream>
#include "Box.h"
#include "Queue.h"

#define BOX_TEST_AMOUNT 10
using namespace std;

void showList(List<Box>);
void showQueue(Queue<Box>);

int main(int argc, char const *argv[]) {

    Box boxes[BOX_TEST_AMOUNT];
    List<Box> list;
    Queue<Box> queue;

    for (int i=0; i < BOX_TEST_AMOUNT; i++) {
        boxes[i] = Box();
        boxes[i].setInt(i);
        boxes[i].setChar( (char) ( i + 97 ));

        list.add(boxes[i]);
        queue.enqueue(boxes[i]);
    }

    // Testing list
    cout << "Testing list..." << endl;
    showList(list);
    cout << "Largo de la lista " << list.length << endl;
    list.removeLast();
    showList(list);
    cout << "Largo de la lista luego de borrar el ultimo " << list.length << endl;
    list.removeFirst();
    showList(list);
    cout << "Largo de la lista luego de borrar el primero " << list.length << endl << endl << endl;
    
    // Testing queue
    cout << "Testing queue..." << endl;
    showQueue(queue);
    cout << "\nLargo de la cola " << queue.length << endl;
    queue.dequeue();
    showQueue(queue);
    cout << "Largo de la cola despues de dequeue() -> " << queue.length << endl;
    queue.enqueue(boxes[BOX_TEST_AMOUNT-1]);
    showQueue(queue);
    cout << "Largo de la cola despues de enqueue( ultima caja del array ) -> " << queue.length << endl;

    return 0;
}

void showList(List<Box> listToShow) {
    Node<Box> *currentNode = listToShow.getFirst();
    int contador = 0;
    while (currentNode) {
        currentNode->getObject().show();
        if (currentNode == listToShow.getLast())
            break;
        else
            currentNode = currentNode->nextNode;
    }
}

void showQueue(Queue<Box> queueToShow) {
    Node<Box> *currentNode = queueToShow.getFirst();
    int contador = 0;
    while (currentNode) {
        currentNode->getObject().show();
       if (currentNode == queueToShow.getLast())
            break;
        else
            currentNode = currentNode->nextNode;
    }
}

