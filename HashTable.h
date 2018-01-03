//
// Created by or.guz on 03-Jan-18.
//

#ifndef DSWET2_HASHTABLE_H
#define DSWET2_HASHTABLE_H

#include "list.h"
#include <stddef.h>
#include <exception>
#include "cassert"
#include "Group.h"

class HashTable {
    int array_size;
    int num_of_items;
    List<Group>* hash_table;

    void rehash(int new_size);

    int hash(int x) {
        return x % array_size;
    }

public:
    HashTable(const int* id_array, int n);
    ~HashTable();
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);

    Group& find(int group_id);
    Group& operator[](int x);
    void insert(const Group& group);
    //TODO ? void remove(int key);
    List<Group> getList(int i) const; //FOR DEBUGGING

    class HashTableException : public std::exception {
    };

    class KeyNotFound : public HashTableException {
    };

    class KeyAlreadyExist : public HashTableException {
    };

    class InvalidSize : public HashTableException {

    };

    class Compare {
        int id;
    public:
        explicit Compare(int id) : id(id) {}

        bool operator()(const Group& group) const {
            return group.getID() == id;
        }
    };
};

HashTable::HashTable(const int* id_array, int n) : array_size(n * 2),
                                                   num_of_items(0),
                                                   hash_table(NULL) {
    if (n <= 0)
        throw InvalidSize();
    hash_table = new List<Group>[n * 2];
    try {
        for (int i = 0; i < n; i++) {
            assert(num_of_items < array_size);
            insert(Group(id_array[i]));
        }
        assert(num_of_items == n);
    } catch (std::bad_alloc& e) {
        delete[] hash_table;
        throw e;
    } catch (Group::InvalidInput& e) {
        delete[] hash_table;
        throw e;
    }
}

HashTable::~HashTable() {
    delete[] hash_table;
}

HashTable::HashTable(const HashTable& source) :
        array_size(source.array_size), num_of_items(source.num_of_items),
        hash_table(NULL) {
    hash_table = new List<Group>[source.array_size];
    try {
        for (int i = 0; i < array_size; i++) {
            hash_table[i] = source.hash_table[i];
        }
    } catch (std::bad_alloc& e) {
        delete[] hash_table;
        throw e;
    }

}

HashTable& HashTable::operator=(const HashTable& source) {
    List<Group>* temp_copy = new List<Group>[source.array_size];
    try {
        for (int i = 0; i < source.array_size; i++) {
            temp_copy[i] = source.hash_table[i];
        }
    } catch (std::bad_alloc& e) {
        delete[] temp_copy;
        throw e;
    }
    delete[] this->hash_table;
    this->hash_table = temp_copy;
    this->array_size = source.array_size;
    this->num_of_items = source.num_of_items;
    return *this;
}

Group& HashTable::find(int group_id) {
    Compare compare(group_id);
    typename List<Group>::Iterator iterator = hash_table[hash(group_id)].find(compare);
    if (iterator == hash_table[hash(group_id)].end())
        throw KeyNotFound();
    return *iterator;
}


Group& HashTable::operator[](int x) {
    return find(x);
}


void HashTable::insert(const Group& group) {
    try { //check if group already exist
        find(group.getID());
    } catch (KeyNotFound& e) {
        if (num_of_items == array_size) { //reallocate
            rehash(array_size * 2);
        }
        hash_table[hash(group.getID())].insert(group);
        num_of_items++;
        return;
    }
    throw KeyAlreadyExist();
}


void HashTable::rehash(int new_size) {
    assert(new_size > 0);
    List<Group>* temp_copy = new List<Group>[new_size];
    int old_size = this->array_size;
    try {
        this->array_size = new_size;
        for (int i = 0; i < old_size; i++) {
            for (typename List<Group>::Iterator iterator = hash_table[i].begin();
                 iterator != hash_table[i].end(); iterator++) {
                Group& current = *iterator;
                temp_copy[hash(current.getID())].insert(current);
            }
        }
    } catch (std::bad_alloc& e) {
        this->array_size = old_size; //recover size
        delete[] temp_copy;
        throw e;
    }
    delete[] this->hash_table;
    this->hash_table = temp_copy;
}

List<Group> HashTable::getList(int i) const {
    return hash_table[i];
}

#endif //DSWET2_HASHTABLE_H
