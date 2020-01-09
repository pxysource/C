#ifndef QUEUE_H
#define QUEUE_H

#include "linklist.h"

template<typename T>
class Queue
{
private:
    LinkList<T> _linklist;
    unsigned int _maxSize;
    unsigned int _size;
    Node<T> *_begin;
    Node<T> *_end;
public:
    Queue();
    unsigned int queueMaxSize ();
    void setQueueMaxSize (unsigned int newsize);
    void inQueue (T data);
    T outQueue ();
    T beginValue ();
    T endValue ();
    unsigned int size (){return _size;}
    bool isEmpty ();
};

template<typename T>
Queue<T>::Queue()
{
    _maxSize = 1024*1024;
    _size = 0;
    _begin = _end = (_linklist.head())->next;
}

template<typename T>
unsigned int Queue<T>::queueMaxSize ()
{
    cout << "queue max size: " << _maxSize;
    return _maxSize;
}

template<typename T>
void Queue<T>::setQueueMaxSize(unsigned int newsize)
{
    if (newsize >= 1024 && newsize <= 8*1024*1024)
    {
        _maxSize = newsize;
        cout << "Set queue max size succeed." << endl;
    }
    else
    {
        cout << "Error: set queue max size failed!" << endl;
        cout << "Queue max size in range[1K, 8M]" << endl;
    }
}

template<typename T>
void Queue<T>::inQueue(T data)
{
    if ((1+_size)*sizeof(T) > _maxSize)
    {
        cout << "Queue is full, could overflow!" << endl;
        return;
    }

    _linklist.insertNode(data, _linklist.size());

    if (0 == this->_size)
    {
        _begin = (_linklist.head())->next;
    }

    _end = _linklist.getNode(_linklist.size());

    _size++;
}

template<typename T>
T Queue<T>::outQueue()
{
    T tmp;
    memset(&tmp, 0, sizeof(tmp));

    if (isEmpty())
    {
        cout << "Queue is empty!" << endl;
        return tmp;
    }

    tmp = _linklist.deleteNode(0);
    _begin = (_linklist.head())->next;

    if (1 == _size)
    {
        _end = nullptr;
    }

    _size--;

    return tmp;
}

template<typename T>
T Queue<T>::beginValue()
{
    T tmp;
    memset (&tmp, 0, sizeof(tmp));

    if (isEmpty())
    {
        cout << "Queue is empty!" << endl;
        return tmp;
    }

    tmp = _begin->t;
    return tmp;
}

template<typename T>
T Queue<T>::endValue()
{
    T tmp;
    memset (&tmp, 0, sizeof(tmp));

    if (isEmpty())
    {
        cout << "Queue is empty!" << endl;
        return tmp;
    }

    tmp = _end->data;
    return tmp;
}

template<typename T>
bool Queue<T>::isEmpty()
{
    return _begin == nullptr;
}

#endif // QUEUE_H
