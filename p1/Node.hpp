template <typename T>
struct Node {
    T m_element;
    Node* m_next;
    Node(T element, Node* next = nullptr) : m_element(element), m_next(next) {}
};