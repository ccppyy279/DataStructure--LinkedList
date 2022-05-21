// interface
#pragma once
template <typename T>
class List {
   protected:
    int m_size;

   public:
    static const int ELEMENT_NOT_FOUND;
    void add(T element) { this->add(this->m_size, element); }
    List() : m_size(0) {}
    int size() const { return this->m_size; }
    bool isEmpty() const { return this->m_size == 0; }
    bool isContain(T element) const {
        return this->indexOf(element) != ELEMENT_NOT_FOUND;
    }
    virtual int indexOf(T element) const = 0;
    virtual void add(int index, T element) = 0;
    virtual T remove(int index) = 0;
    virtual T get(int index) const = 0;
    virtual T set(int index, T element) const = 0;
    virtual void clear() = 0;

   protected:
    void checkIndexForAdd(int index) const {
        if (index < 0 || index > this->m_size) {
            throw std::out_of_range("加法下标越界");
        }
    }
    void checkIndex(int index) const {
        if (index < 0 || index >= this->m_size) {
            throw std::out_of_range("下标越界");
        }
    }
};

template <typename T>
const int List<T>::ELEMENT_NOT_FOUND = -1;