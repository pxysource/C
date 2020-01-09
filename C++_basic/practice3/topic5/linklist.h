#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <cstring>
using namespace std;

template<typename T>
struct Node
{
    Node<T> *next;
    T data;
};

template<typename T>
class LinkList
{
private:
    Node<T> *_head;
    unsigned int _size;
public:
    LinkList();
    ~LinkList ();

    void clearList ();
    void insertNode (T data, unsigned int pos);
    T deleteNode (unsigned int pos);
    Node<T> *getNode (unsigned int pos);
    bool isEmpty ();
    unsigned int size () {return _size;}
    Node<T> *head () {return _head;}
};

template<typename T>
LinkList<T>::LinkList()
{
    _head = new Node<T>;
    memset(_head, 0, sizeof(Node<T>));
    _head->next = nullptr;
    _size = 0;
}

template<typename T>
LinkList<T>::~LinkList()
{
    if (!isEmpty())
    {
        clearList();
    }

    delete _head;
}

template<typename T>
void LinkList<T>::clearList()
{
    if (isEmpty())
    {
        cout << "linklist is empty!" << endl;
        return;
    }

    Node<T> *current;

    while (nullptr != _head->next)
    {
        current = _head->next;
        _head->next = current->next;
        delete current;
    }

    _size = 0;
}

template<typename T>
void LinkList<T>::insertNode(T data, unsigned int pos)
{
    Node<T> *newnode = new Node<T>;
    newnode->data = data;
    newnode->next = nullptr;

    Node<T> *current = _head;

    if (pos > _size)
    {
        pos = _size;
    }

    for(unsigned int i = 0; i < pos; i++)
    {
        current = current->next;
    }

    newnode->next = current->next;
    current->next = newnode;
    _size++;
}

template<typename T>
T LinkList<T>::deleteNode(unsigned int pos)
{
    Node<T> *tmp = nullptr;
    Node<T> *current = _head;
    T ret;
    memset(&ret, 0, sizeof(ret));

    if (isEmpty())
    {
        cout << "LinkList is empty!" << endl;
        //用模板的时候返, 回值为模板类型, 出错时返回值应该怎么设置
        return ret;
    }

    if (pos > _size)
    {
        pos = _size - 1;
    }

    for (unsigned int i = 0; i < pos; i++)
    {
        current = current->next;
    }

    tmp = current->next;
    current->next = tmp->next;
    _size--;

    ret = tmp->data;
    delete tmp;

    return ret;
}

template<typename T>
Node<T> *LinkList<T>::getNode(unsigned int pos)
{
    Node<T> *current = nullptr;

    if (isEmpty())
    {
        cout << "linklist is empty!" << endl;
        return current;
    }

    if (pos >= _size)
    {
        pos = _size - 1;
    }

    current = _head;
    for (unsigned int i = 0; i < pos; i++)
    {
        current = current->next;
    }

    return current->next;
}

template<typename T>
bool LinkList<T>::isEmpty()
{
    return nullptr == _head->next;
}

#endif // LINKLIST_H
