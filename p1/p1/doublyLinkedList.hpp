#pragma once
#include <iostream>

#include "List.hpp"
template <typename T>
class DoublyLinkedList : public List<T> {
   private:
    struct DNode {
        T m_element;
        DNode *m_prev;
        DNode *m_next;
        DNode(T element, DNode *prev = nullptr, DNode *next = nullptr)
            : m_element(element), m_prev(prev), m_next(next) {}
    };
    DNode *m_first;
    DNode *m_last;

   public:
    static const int ELEMENT_NOT_FOUND = -1;
    template <typename S>
    friend std::ostream &operator<<(std::ostream &cout,
                                    const DoublyLinkedList<S> &list);
    DoublyLinkedList();
    using List<T>::add;
    void add(int index, T element) override;
    T remove(int index) override;
    void clear() override;
    T get(int index) const override;
    T set(int index, T element) const override;
    int indexOf(T element) const override;
    T operator[](int index) const;

   private:
    DNode *getNode(int index) const;
};

template <typename T>
typename DoublyLinkedList<T>::DNode *DoublyLinkedList<T>::getNode(
    int index) const {
    DNode *node{nullptr};
    if (index < this->m_size >> 1) {
        node = this->m_first;
        for (int i = 0; i < index; ++i) {
            node = node->m_next;
        }
    } else {
        node = this->m_last;
        for (int i = this->m_size - 1; i > index; --i) {
            node = node->m_prev;
        }
    }
    return node;
}
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : m_first(nullptr), m_last(nullptr) {}

template <typename T>
void DoublyLinkedList<T>::add(int index, T element) {
    this->checkIndexForAdd(index);
    if (index == this->m_size) {
        if (this->m_last == nullptr) {
            this->m_first = this->m_last = new DNode(element, nullptr, nullptr);
        } else {
            this->m_last = this->m_last->m_next =
                new DNode(element, this->m_last, nullptr);
        }
    } else {
        DNode *nextNode = this->getNode(index);
        if (nextNode == this->m_first) {
            //这里this->m_first!=nullptr:这种情况上一个if中
            this->m_first = this->m_first->m_prev =
                new DNode(element, nullptr, this->m_first);
        } else {
            nextNode->m_prev = nextNode->m_prev->m_next =
                new DNode(element, nextNode->m_prev, nextNode);
        }
    }
    ++this->m_size;
}

template <typename T>
T DoublyLinkedList<T>::remove(int index) {
    this->checkIndex(index);
    DNode *node = this->getNode(index);
    if (node->m_prev == nullptr) {
        this->m_first = this->m_first->m_next;
    } else {
        node->m_prev->m_next = node->m_next;
    }

    if (node->m_next == nullptr) {
        this->m_last = this->m_last->m_prev;
    } else {
        node->m_next->m_prev = node->m_prev;
    }
    T val = node->m_element;
    delete node;
    --this->m_size;
    return val;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    DNode *p1 = this->m_first;
    DNode *p2 = this->m_last;
    while (p1 != p2) {
        DNode *tmp = p1->m_next;
        delete p1;
        p1 = tmp;
        if (p1 == p2) {
            break;
        }
        tmp = p2->m_prev;
        delete p2;
        p2 = tmp;
    }
    delete p1;
}

template <typename T>
T DoublyLinkedList<T>::get(int index) const {
    return this->getNode(index)->m_element;
}

template <typename T>
T DoublyLinkedList<T>::set(int index, T element) const {
    DNode *node = this->getNode(index);
    T val = node->m_element;
    node->m_element = element;
    return val;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T element) const {
    DNode *node = this->m_first;
    for (int i = 0; i < this->m_size; ++i) {
        if (node->m_element == element) {
            return i;
        }
        node = node->m_next;
    }
    return ELEMENT_NOT_FOUND;
}

template <typename T>
T DoublyLinkedList<T>::operator[](int index) const {
    this->checkIndex(index);
    return this->getNode(index)->m_element;
}

template <typename T>
std::ostream &operator<<(std::ostream &cout, const DoublyLinkedList<T> &list) {
    cout << "size=" << list.m_size << "[";
    for (int i = 0; i < list.m_size; ++i) {
        if (i != 0) {
            cout << ',';
        }
        if (list.getNode(i)->m_prev != nullptr) {
            cout << list.getNode(i)->m_prev->m_element << '_';
        } else {
            cout << "null_";
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