// Файл MyStack.h
#ifndef MyStack_h
#define MyStack_h

#include <iostream>

// Шаблонный класс ListNode (узел односвязного списка)
template<class INF, class FRIEND>
class ListNode {
private:
    INF d;                  // информационная часть узла
    ListNode *next;         // указатель на следующий узел списка
    ListNode(void) { next = nullptr; } // конструктор
    friend FRIEND;
};

// Шаблонный класс MyStack на основе односвязного списка.
template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node *top;
public:
    MyStack(void) : top(nullptr) {} // конструктор
    ~MyStack(void);                // деструктор
    bool empty(void) const;        // стек пустой?
    bool push(INF n);              // добавить узел в вершину стека
    bool pop(void);                // удалить узел из вершины стека
    INF top_inf(void) const;       // считать информацию из вершины стека
    MyStack(const MyStack& other); // конструктор копирования
    MyStack<INF>& operator=(const MyStack<INF>& other); // оператор присваивания

    template<class T>
    friend std::ostream& operator<<(std::ostream& os, const MyStack<T>& stack);
};

// Реализация методов класса MyStack
template<class INF>
MyStack<INF>::~MyStack(void) {
    while (!empty()) {
        pop();
    }
}

template<class INF>
bool MyStack<INF>::empty(void) const {
    return top == nullptr;
}

template<class INF>
bool MyStack<INF>::push(INF n) {
    Node *newNode = new Node;
    newNode->d = n;
    newNode->next = top;
    top = newNode;
    return true;
}

template<class INF>
bool MyStack<INF>::pop(void) {
    if (empty()) {
        return false;
    }
    Node *temp = top;
    top = top->next;
    delete temp;
    return true;
}

template<class INF>
INF MyStack<INF>::top_inf(void) const {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top->d;
}

template<class INF>
MyStack<INF>::MyStack(const MyStack& other) : top(nullptr) {
    Node *current = other.top;
    MyStack<INF> tempStack;
    while (current != nullptr) {
        tempStack.push(current->d);
        current = current->next;
    }
    while (!tempStack.empty()) {
        push(tempStack.top_inf());
        tempStack.pop();
    }
}

template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack<INF>& other) {
    if (this != &other) {
        while (!empty()) {
            pop();
        }
        Node *current = other.top;
        MyStack<INF> tempStack;
        while (current != nullptr) {
            tempStack.push(current->d);
            current = current->next;
        }
        while (!tempStack.empty()) {
            push(tempStack.top_inf());
            tempStack.pop();
        }
    }
    return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const MyStack<T>& stack) {
    typename MyStack<T>::Node *current = stack.top;
    while (current != nullptr) {
        os << current->d << " ";
        current = current->next;
    }
    return os;
}

void Multipliers(int n, MyStack<int> &stack);

#endif
