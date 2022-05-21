#pragma once
#include <iostream>
#include <stdexcept>

#include "List.hpp"

template <typename T>
class CircularLinkedList : public List<T> {
   private:
    struct Node {
        T m_element;
        Node* m_next;
        Node(T element, Node* next = nullptr)
            : m_element(element), m_next(next) {}
    };

    Node* m_first;

   public:
    template <typename S>
    friend std::ostream& operator<<(std::ostream& cout,
                                    const CircularLinkedList<S>& list);
    using List<T>::add;
    static const int ELEMENT_NOT_FOUND = -1;
    CircularLinkedList();
    void add(int index, T element) override;
    T remove(int index) override;
    void clear() override;
    T get(int index) const override;
    T set(int index, T element) const override;
    int indexOf(T element) const override;
    T operator[](int index) const;

   private:
    Node* getNode(int index) const;  //根据索引获取节点(确保index范围正确)
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList() : m_first(nullptr) {}

template <typename T>
typename CircularLinkedList<T>::Node* CircularLinkedList<T>::getNode(
    int index) const {
    Node* node = this->m_first;
    for (int i = 0; i < index; ++i) {
        node = node->m_next;
    }
    return node;
}

template <typename T>
T CircularLinkedList<T>::get(int index) const {
    return this->getNode(index)->m_element;
}

template <typename T>
T CircularLinkedList<T>::set(int index, T element) const {
    Node* node = this->getNode(index);
    T val = node->m_element;
    node->m_element = element;
    return val;
}

template <typename T>
int CircularLinkedList<T>::indexOf(T element) const {
    Node* node = this->m_first;
    for (int i = 0; i < this->m_size; ++i) {
        if (node->m_element == element) {
            return i;
        }
        node = node->m_next;
    }
    return ELEMENT_NOT_FOUND;
}
template <typename T>
T CircularLinkedList<T>::operator[](int index) const {
    this->checkIndex(index);
    return this->getNode(index)->m_element;
}

template <typename T>
std::ostream& operator<<(std::ostream& cout,
                         const CircularLinkedList<T>& list) {
    cout << "size=" << list.m_size << "[";
    for (int i = 0; i < list.m_size; ++i) {
        if (i != 0) {
            cout << ',';
        }
        cout << list[i] << '_';
        if (list.getNode(i)->m_next != nullptr) {
            cout << list.getNode(i)->m_next->m_element;
        } else {
            cout << "null";
        }
    }
    return cout << "]";
}

template <typename T>
void CircularLinkedList<T>::add(int index, T element) {
    this->checkIndexForAdd(index);
    if (index == 0) {
        //插入第一个节点
        if (this->m_size == 0) {
            //原来无节点
            this->m_first = new Node(element);
            this->m_first->m_next = this->m_first;
        } else {
            Node* lastNode = this->getNode(this->m_size - 1);
            this->m_first = lastNode->m_next = new Node(element, this->m_first);
        }

    } else {
        Node* preNode = this->getNode(index - 1);
        preNode->m_next = new Node(element, preNode->m_next);
    }
    ++this->m_size;
}

template <typename T>
T CircularLinkedList<T>::remove(int index) {
    this->checkIndex(index);
    Node* delNode = this->m_first;
    if (index == 0) {
        if (this->m_size == 1) {
            this->m_first = nullptr;
        } else {
            Node* lastNode = this->getNode(this->m_size - 1);
            this->m_first = lastNode->m_next = this->m_first->m_next;
        }

    } else {
        Node* preNode = this->getNode(index - 1);
        delNode = preNode->m_next;
        preNode->m_next = preNode->m_next->m_next;
    }
    T ret = delNode->m_element;
    delete delNode;
    --this->m_size;
    return ret;
}
template <typename T>
void CircularLinkedList<T>::clear() {
    Node* node = this->m_first;
    for (int i = 0; i < this->m_size - 1; ++i) {
        Node* tmp = node->m_next;
        delete node;
        node = tmp;
    }
}
