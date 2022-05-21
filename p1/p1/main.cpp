#include <iostream>

#include "CircularDoublyLinkedList.hpp"
#include "LinkedList.hpp"
#include "circularLinkedList.hpp"
#include "doublyLinkedList.hpp"
using namespace std;
void LinkedListTest();
int main() {
    CircularDoublyLinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.add(i);
        cout << list;
    }
    cout << list.get(5) << endl;
    cout << list.indexOf(5) << endl;
    list.set(5, 100);
    cout << list[5] << endl;
    cout << list.size() << endl;
    for (int i = 0; i < 10; i++) {
        list.remove(0);
        cout << list;
    }
}

void LinkedListTest() {
    LinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.add(i);
        cout << list;
    }
    cout << list.get(5) << endl;
    cout << list.indexOf(5) << endl;
    list.set(5, 100);
    cout << list[5] << endl;
    cout << list.size() << endl;
    for (int i = 0; i < 10; i++) {
        list.remove(0);
        cout << list;
    }
}