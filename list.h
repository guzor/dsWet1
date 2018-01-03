#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <iostream>
#include <cassert>

#define nullptr NULL
/*---------------------------------------------------------------------------*/
/* List Class */
/*---------------------------------------------------------------------------*/

/** generic doubly list class:
 *  Assumptions on T: T has default constructor T()
 *                    T has copy constructor T(T)
 *                    assignment operator=
 *             operator==: List operator== and != require operator ==, != of T.
 *
 *  Exceptions: elementNotFound */
template<class T>
class List {
    class Node;

    Node* head;
    Node* last;
    int size;

public:
    /**constructs a new empty list */
    List();

    /**copy consturctor
     * constructs a copy of the given list
     * @param list - the source list that should be copied
     */
    List(const List& list);

    /**destructor for List
     * destroy a list and all it's content */
    ~List();

    /**assignment operator
     * destroy the old list and assign it to be a copy of the source list
     * @param list - the list to be assigned
     * @return a refernce to the new assigned list */
    List& operator=(const List& list);

    /**a class that implementing an internal iterator for the list */
    class Iterator;

    /**Method returns an iterator points to the first item in the list.
     * If the list is empty return iterator to the end of the list will be
     * returned
     * @return an iterator points to the first item in the list */
    Iterator begin() const;

    /**Method returns an iterator for the end of the list.
     * The end of the list defines as a pointer to a not exist item (dummy)
     * @return an iterator to the end of the list */
    Iterator end() const;

    /** get the current size of the list
     * @return the size of the list */
    int getSize() const;

    /**insert a new item to the list with the value of data, before the given
     * iterator. The data will be copied by value, with it's copy constructor.
     * If the iterator points to the end of the list the new item will be insert
     * to the end of the list
     * @param data - The new item to be added to the list
     * @param iterator - an iterator to the place the item should be added
     * before
     * @Exceptions: ElementNotFound- the iterator point to a different list */
    void insert(const T& data, Iterator iterator);
    /**insert a new item to the list with the value of data to the end of the
     * list. The data will be copied by value, with it's copy constructor.
     * @param data - The new item to be added to the list */
    void insert(const T& data);

    /**removes the item the iterator points to from the list
     * @param iterator - points to the item to remove
     * @Exceptions: ElementNotFound - the list is empty or the iterator is
     * invalid: points to a different list or doesn't point to a valid item */
    void remove(Iterator iterator);

    /**finds an item that apply to the function in the list by the predicate
     * function.
     * The first item that returns true in the predicate function object will
     * be returned (by iterator)
     * @tparam Predicate - Function object that get one parameter and return true
     *                     or false
     * @param predicate -the function by which the items are being checked
     * @return iterator to the first item that apply to predicate. If none exist
     *         iterator to the end of the list will be returned */
    template<class Predicate>
    Iterator find(const Predicate& predicate) const;

    /**sorts the list by the compare function.
     *The list will be sorted as every 2 successive items o1,o2 will return true
     * in compare(o1,o2)
     * @tparam Compare - A function object that gets 2 parameters and return
     *                     true or false
     * @param compare - the compare function by which 2 items will be compared*/
    template<class Compare>
    void sort(const Compare& compare);

    /**compare operators:
     * == return if the list is equals to the given list. Equals lists are two
     * list contains the same values in the same order
     * != return true if the list are different (not equals)
     * @param list - the list to compare "this" list to
     * @return ==: true if the lists are equals. !=: true if the lists are
     *                                               different
     */
    bool operator==(const List& list) const;
    bool operator!=(const List& list) const;

    class ElementNotFound : public std::runtime_error {
    public:
        ElementNotFound() : std::runtime_error("Element not found") {}
    };
};


/*---------------------------------------------------------------------------*/
/* Node Class*/
/*---------------------------------------------------------------------------*/

/**generic node class that implement the list nodes.
 * store the data, the next and the previous nodes to each node. */
template<class T>
class List<T>::Node {
    T data;
    Node* previous;
    Node* next;

public:
    /**constructor- creates node with a T data with the default constructor T()
     * the node will be before and after nullptr*/
    Node();

    /**constructor- creates node with a T data and set the next and previous
     * nodes to nullptr. data will be copied by the copy constructor of T
     * @param data - the data to put inside the node */
    explicit Node(T data);

    /** get the next node
     * @return a pointer to the next node to "this" node */
    Node* getNext() const;
    /** get the previous node
     * @return a pointer to the previous node to "this" node */
    Node* getPrevious() const;

    /**sets the next node to point on the given node
     * @param node - the node that this node should be pointed to
     */
    void setNext(Node* node);
    /**sets the previous node to point on the given node
     * @param node - a pointer to the node before "this" */
    void setPrevious(Node* node);

    /**return the data in the node
     * @return - referance to the node's data */
    T& getData();

    /**change the data of the node
     * @param new_data - the new data should be put in the node */
    void setData(T& new_data);
};

/*---------------------------------------------------------------------------*/
/*Iterator Class*/
/*---------------------------------------------------------------------------*/

/**class of list that implements an iterator.
 * The iterator implemented as a pointer to one of the list's nodes. when it
 * reach the end of the list it points to the dummy last node.
 * In addition the iterator holds a pointer to the list to which it belongs */
template<class T>
class List<T>::Iterator {
    const List<T>* list;
    Node* current;

    /**constuctor
     * creates a new iterator to the given list that points to one of the nodes
     * @param list - pointer tothe list to which the iteraotr belongs
     * @param current - pointer to the node the iterator points to*/
    Iterator(const List<T>* list, Node* current);

    friend class List<T>;

public:

    /**Dereference operator
     * return the data to which the iterator points to
     * @return T type data of the current position of the iterator*/
    T& operator*();

    /**++ operator
     * advance the iterator to the next node and return the iterator after the
     * change.
     * If the iterator points to the end of the list (last node). The action is
     * not defined (will remain at the same node)
     * @return - reference to the iterator itself after the change */
    Iterator& operator++();
    /**operator ++
     * advance the iterator to the next node and return a copy of iterator
     * before the change.
     * If the iterator points to the end of the list (last node). The action is
     * not defined (will remain at the same node)
     * @return - a copy of the iterator before the change */
    Iterator operator++(int);

    /**-- operator
     * advance the iterator to the previous node and return the iterator after the
     * change.
     * If the iterator points to the first item of the list. The action is
     * not defined (will remain at the same node)
     * @return - reference to the iterator itself after the change */
    Iterator& operator--();
    /**operator --
     * advance the iterator to the previous node and return a copy of iterator
     * before the change.
     * If the iterator points to the first item of the list (last node). The
     * action is not defined (will remain at the same node)
     * @return - a copy of the iterator before the change */
    Iterator operator--(int);

    /**comparison operators
     * compare two iterator and return if they are equals. Iterator considered
     * equals if they belong to the same list and points to the same node.
     * (if both points to the last node they are equal as weel
     * @param iterator - the iterator "this" should be compare to
     * @return ==: true if equals. !=: true if not equals */
    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;
};


/*---------------------------------------------------------------------------*/
/* List Functions */
/*---------------------------------------------------------------------------*/

template<class T>
List<T>::List() : head(new Node),
                  last(new Node), size(0) {
    head->setNext(last);
    last->setPrevious(head);
}

template<class T>
List<T>::List(const List& list) : head(new Node()), last(new Node()), size(0) {
    head->setNext(last);
    last->setPrevious(head);
    for (Iterator it = list.begin(); it != list.end(); it++) {
        this->insert(*it);
    }
    assert(size == list.size);
}

template<class T>
List<T>::~List() {
    Iterator it = begin();
    while (it != end()) {
        Iterator to_delete = it++;
        remove(to_delete);
    }
    delete head;
    delete last;
}

template<class T>
List<T>& List<T>::operator=(const List& list) {
    if (this == &list) {
        return *this;
    }
    Iterator it = begin();
    while (it != end()) {
        Iterator to_delete = it++;
        remove(to_delete);
    }
    assert(size == 0);
    for (it = list.begin(); it != list.end(); it++) {
        this->insert(*it);
    }
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(this, head->getNext());
}

template<class T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(this, last);
}


template<class T>
int List<T>::getSize() const {
    return this->size;
}

template<class T>
void List<T>::insert(const T& data) {
    Node* new_node = new Node(data);
    Node* previous = last->getPrevious();
    (*previous).setNext(new_node);
    (*new_node).setNext(last);
    last->setPrevious(new_node);
    (*new_node).setPrevious(previous);
    size++;
}

template<class T>
void List<T>::insert(const T& data, Iterator iterator) {
    if (this != iterator.list) {
        throw ElementNotFound();
    }
    Node* new_node = new Node(data);
    Node* previous = iterator.current->getPrevious();
    (*new_node).setPrevious(previous);
    (*previous).setNext(new_node);
    (*new_node).setNext(iterator.current);
    iterator.current->setPrevious(new_node);
    size++;
}

template<class T>
void List<T>::remove(Iterator iterator) {
    if (this != iterator.list || iterator == end() || getSize() == 0) {
        throw ElementNotFound();
    }
    Node* previous = iterator.current->getPrevious();
    Node* next = iterator.current->getNext();
    (*previous).setNext(next);
    (*next).setPrevious(previous);
    delete iterator.current;
    size--;
}

template<class T>
template<class Predicate>
typename List<T>::Iterator List<T>::find(const Predicate& predicate) const {
    Iterator iterator = begin();
    for (; iterator != end(); iterator++) {
        if (predicate(*iterator)) {
            return iterator;
        }
    }
    assert(iterator == end());
    return iterator;
}

template<class T>
template<class Compare>
void List<T>::sort(const Compare& compare) {
    bool not_sorted = true;
    int len = size - 1;
    while (len > 0 && not_sorted) {
        not_sorted = false;
        Iterator it = begin();
        for (int i = 0; i < len; i++) {
            Iterator next = it;
            next++;
            assert(next != end());
            if (compare(*it, *next) == false) {
                T temp = *it;
                it.current->setData(*next);
                next.current->setData(temp);
                not_sorted = true;
            }
            it++;
        }
        len--;
    }
}

template<class T>
bool List<T>::operator==(const List& list) const {
    if (this->size != list.size) {
        return false;
    }
    Iterator it1 = this->begin();
    Iterator it2 = list.begin();
    while (it1 != this->end()) {
        if (*(it1++) != *(it2++)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool List<T>::operator!=(const List& list) const {
    return !(*this == list);
}

/*---------------------------------------------------------------------------*/
/* Node Functions */
/*---------------------------------------------------------------------------*/

template<class T>
List<T>::Node::Node() :previous(nullptr), next(nullptr) {
}

template<class T>
List<T>::Node::Node(T data) : data(data), previous(nullptr), next(nullptr) {
}

template<class T>
typename List<T>::Node* List<T>::Node::getNext() const {
    return this->next;
}

template<class T>
typename List<T>::Node* List<T>::Node::getPrevious() const {
    return this->previous;
}

template<class T>
T& List<T>::Node::getData() {
    return this->data;
}

template<class T>
void List<T>::Node::setNext(Node* node) {
    this->next = node;
}

template<class T>
void List<T>::Node::setPrevious(Node* node) {
    this->previous = node;
}

template<class T>
void List<T>::Node::setData(T& new_data) {
    data = new_data;
}

/*---------------------------------------------------------------------------*/
/* Iterator Functions */
/*---------------------------------------------------------------------------*/

template<class T>
List<T>::Iterator::Iterator(const List<T>* list, Node* current): list(list),
                                                                 current(current) {
}

template<class T>
T& List<T>::Iterator::operator*() {
    if (current == list->last || current == list->head) {
        throw ElementNotFound();
    }
    return (*current).getData();
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (*this != list->end()) {
        current = current->getNext();
    }
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator result = *this;
    ++(*this);
    return result;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    if (current->getPrevious() == list->head) return *this;
    current = current->getPrevious();
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator result = *this;
    --*this;
    return result;
}

template<class T>
bool List<T>::Iterator::operator==(const Iterator& iterator) const {
    return (list == iterator.list && this->current == iterator.current);
}

template<class T>
bool List<T>::Iterator::operator!=(const Iterator& iterator) const {
    return !((*this) == iterator);
}


#endif //LIST_LIST_H
