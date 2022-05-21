template <typename T>
struct DNode {
    T m_element;
    DNode *m_prev;
    DNode *m_next;
    DNode(T element, DNode *prev = nullptr, DNode *next = nullptr)
        : m_element(element), m_prev(prev), m_next(next) {}
};