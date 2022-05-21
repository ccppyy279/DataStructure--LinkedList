#pragma once
#include <iostream>
#include <stdexcept>

#include "List.hpp"

template <typename T>
class LinkedList : public List<T> {
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
                                    const LinkedList<S>& list);
    using List<T>::add;
    static const int ELEMENT_NOT_FOUND = -1;
    LinkedList();
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
LinkedList<T>::LinkedList() : m_first(nullptr) {}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(int index) const {
    Node* node = this->m_first;
    for (int i = 0; i < index; ++i) {
        node = node->m_next;
    }
    return node;
}

template <typename T>
void LinkedList<T>::add(int index, T element) {
    this->checkIndexForAdd(index);
    if (index == 0) {
        //添加首节点
        this->m_first = new Node(element, this->m_first);
    } else {
        //获取前一个节点
        Node* preNode = this->getNode(index - 1);
        preNode->m_next = new Node(element, preNode->m_next);
    }
    ++this->m_size;
}
template <typename T>
void LinkedList<T>::clear() {
    Node* p = this->m_first;
    while (p != nullptr) {
        Node* tmp = p->m_next;
        delete p;
        p = tmp;
    }
    this->m_size = 0;
}

template <typename T>
T LinkedList<T>::remove(int index) {
    this->checkIndex(index);
    Node* node = this->m_first;
    if (index == 0) {
        //删除首节点
        Node* delNode = this->m_first;
        this->m_first = this->m_first->m_next;
        delete delNode;
    } else {
        //前一个节点
        Node* preNode = this->getNode(index - 1);
        Node* delNode = node = preNode->m_next;
        preNode->m_next = preNode->m_next->m_next;
        delete delNode;
    }
    --this->m_size;
    return node->m_element;
}

template <typename T>
T LinkedList<T>::get(int index) const {
    return this->getNode(index)->m_element;
}

template <typename T>
T LinkedList<T>::set(int index, T element) const {
    Node* node = this->getNode(index);
    T val = node->m_element;
    node->m_element = element;
    return val;
}

template <typename T>
int LinkedList<T>::indexOf(T element) const {
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
T LinkedList<T>::operator[](int index) const {
    this->checkIndex(index);
    return this->getNode(index)->m_element;
}

template <typename T>
std::ostream& operator<<(std::ostream& cout, const LinkedList<T>& list) {
    cout << "size=" << list.m_size << "[";
    for (int i = 0; i < list.m_size; ++i) {
        if (i != 0) {
            cout << ',';
        }
        cout << list[i];
    }
    return cout << "]";
}