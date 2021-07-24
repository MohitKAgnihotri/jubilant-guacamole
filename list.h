#ifndef LIST_CLASS
#define LIST_CLASS   

#include <fstream>
#include <iostream>
using namespace std;

template <class T> class List;
template <class T> class ListIterator;

template <class T>

class  Node
{
    friend class List<T>;
    friend class ListIterator <T>;
    T   data;
    Node<T>* next;
};

template <class T>

class List
{
public:
    List();
    ~List();
    T* InsertAscending(T&);
    T* InsertAtEnd(T&);
    T* InsertSorted(T&);

    T* Delete(T&);
    T* Retrieve(void);
    void Full() { cout << "List is Full" << endl; }
    void Empty() { cout << "List is Empty" << endl; }
    bool isEmpty() { return head == NULL; }
    bool isNotEmpty() { return head != NULL; }

private:

    Node<T>* head;
    friend class List <T>;
    friend class ListIterator <T>;
};


// constructor
template <class T>
List<T>::List()
{
    head = NULL;
}


// destructor
template <class T>

List<T>::~List<T>()
{
    Node<T>* ptr, * save;
    for (ptr = head; ptr != 0; )
    {
        save = ptr->next;
        delete ptr;
        ptr = save;
    }
}

template <class T>

T* List<T>::InsertAscending(T& x)
{
    Node<T>* newnode = new Node<T>, * ptr;
    if (newnode == NULL)
    {
        Full();
        return NULL;
    }
    newnode->next = NULL;
    newnode->data = x;

    if (head == NULL || head->data >= x)
    {
        newnode->next = head;
        head = newnode;
    }
    else
    {
        for (ptr = head; ptr->next != NULL && ptr->next->data < x; ptr = ptr->next);
        newnode->next = ptr->next;
        ptr->next = newnode;
    }
    return &x;
}


template <class T>

T* List<T>::InsertAtEnd(T& x)
{
    Node<T>* newnode = new Node<T>, * ptr;
    if (newnode == NULL)
    {
        Full();
        return NULL;
    }
    newnode->next = NULL;
    newnode->data = x;

    if (head == NULL)
    {
        newnode->next = head;
        head = newnode;
    }
    else
    {
        for (ptr = head; ptr->next != NULL; ptr = ptr->next);
        newnode->next = ptr->next;
        ptr->next = newnode;
    }
    return &x;
}

template <typename T>
T* List<T>::InsertSorted( T& newitem)
{ 
    Node<T>* newNode = new Node<T>, * ptr;
    if (newNode == NULL)
    {
        Full();
        return NULL;
    }
    newNode->next = NULL;
    newNode->data = newitem;

    if (head == NULL)
    {
        head = newNode;
        return &newitem;
    }
    else if (newNode->data < head->data)
    {
        newNode->next = head;
        head = newNode;
        return &newitem;
    }
    else
    {
        // insertion somewhere after the head.
        Node<T>* insertionPoint = head;

        while (insertionPoint->next && insertionPoint->next->data < newNode->data)
            insertionPoint = insertionPoint->next;

        newNode->next = insertionPoint->next;
        insertionPoint->next = newNode;
        return &newitem;
    }
}

template <class T>
T* List<T>::Delete(T& x)
{
    Node<T>* ptr, * last = NULL;
    if (head == NULL)
    {
        Empty();
        return NULL;
    }
    if (head->data == x)
    {
        x = head->data;
        ptr = head;
        head = head->next;
        delete ptr;
        return &x;
    }
    else
    {
        for (ptr = head->next, last = head; ptr != NULL && ptr->data < x; ptr = ptr->next)
        {
            last = ptr;
        }

        if (ptr != NULL && ptr->data == x)
        {
            x = ptr->data;
            last->next = ptr->next;
            delete ptr;
            return &x;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}

// return first element in the list
template <class T>
T* List<T>::Retrieve()
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        return (&head->data);
    }
}

template <class T>
class  ListIterator
{
public:
    ListIterator(const List<T>& L) :list(L), current(0)
    {
        current = list.head;
    };
    T* First();
    T* Next();
    void Reset();
private:
    const List<T>& list;
    Node <T>* current;
};

template <class T>
void ListIterator<T>::Reset()
{
    current = list.head;
}

template <class T>
T* ListIterator<T>::First()
{
    current = list.head;
    if (current)
    {
        return &current->data;
    }
    else
    {
        return 0;
    }
}


template <class T>
T* ListIterator<T>::Next()
{
    if (current == 0)
    {
        return 0;
    }
    T* data = &current->data;
    current = current->next;
    return data;
}
#endif