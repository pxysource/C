#ifndef STACK_H
#define STACK_H

#include "linklist.h"

template<typename T>
class Stack
{
private:
    LinkList<T> _linklist;
    unsigned int _maxSize;
    unsigned int _size;
    Node<T> *_top;
public:
    Stack();
    unsigned int stackMaxSize ();
    void setStackMaxSize (unsigned int newsize);
    void push (T data);
    T pop ();
    T top ();
    unsigned int size (){return _size;}
    bool isEmpty ();
};

template<typename T>
Stack<T>::Stack()
{
    _maxSize = 1024 * 1024;
    _size = 0;
    _top = (_linklist.head())->next;
}

template<typename T>
unsigned int Stack<T>::stackMaxSize ()
{
    cout << "stack max size: " << _maxSize;
    return _maxSize;
}

template<typename T>
void Stack<T>::setStackMaxSize (unsigned int newsize)
{
    if (newsize >= 1024 && newsize <= (8*1024*1024))
    {
        _maxSize = newsize;
        cout << "Set stack max size succeed" << endl;
    }
    else
    {
        cout << "Set stack max size error!" << endl;
        cout << "Please set stack size in rang (1K--8M)." <<endl;
    }
}

template<typename T>
void Stack<T>::push(T data)
{
    if ((_size+sizeof(T)) > _maxSize)
    {
        cout << "Stack is full, could overflow!" << endl;
        return;
    }

    _linklist.insertNode(data, 0);
    _top = (_linklist.head())->next;
    _size++;
}

template<typename T>
T Stack<T>::pop()
{
    T tmp;
    memset (&tmp, 0, sizeof(tmp));

    if (isEmpty())
    {
        cout << "Stack is empty!" << endl;
        return tmp;
    }

    tmp = _linklist.deleteNode(0);
    _top = (_linklist.head())->next;
    _size--;

    return tmp;
}

template<typename T>
T Stack<T>::top()
{
    T tmp;
    memset (&tmp, 0, sizeof(tmp));

    if (isEmpty())
    {
        cout << "Stack is empty!" << endl;
        return tmp;
    }

    tmp = _top->data;

    return tmp;
}

template<typename T>
bool Stack<T>::isEmpty()
{
    return nullptr == _top;
}

#endif // STACK_H
