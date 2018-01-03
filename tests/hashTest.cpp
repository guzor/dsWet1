#include "../HashTable.h"

#include "testUtility.h"
#include <cassert>

void testInit() {
    int arr[5] = {1, 3, 83, 11, 4};
    HashTable hash(arr, 5);
    for (int i = 0; i < 10; i++) {
        List<Group> current = hash.getList(i);
        i++;
        i--;
    }
}

void testInsert() {
    int arr[3] = {1, 3, 7};
    HashTable hash(arr, 3);
    ASSERT_NO_THROW(hash.insert(Group(2)));
    ASSERT_NO_THROW(hash.insert(Group(9)));
    ASSERT_NO_THROW(hash.insert(Group(4)));
    for (int i = 0; i < 6; i++) {
        List<Group> current = hash.getList(i);
        i++;
        i--;
    }
    ASSERT_NO_THROW(hash.insert(Group(13)));
    for (int i = 0; i < 12; i++) {
        List<Group> current = hash.getList(i);
        i++;
        i--;
    }
    bool thrown = false;
    try {
        hash.insert(Group(3));
    } catch (HashTable::KeyAlreadyExist& e) {
        thrown = true;
    }
    assert(thrown);
}

void testFind() {
    int arr[5] = {1, 5, 15, 3, 7};
    HashTable hash(arr, 5);
    ASSERT_EQUALS(5, hash.find(5).getID());
    ASSERT_EQUALS(15, hash.find(15).getID());
    ASSERT_EQUALS(3, hash.find(3).getID());
    ASSERT_THROWS(HashTable::KeyNotFound, hash.find(100));
    ASSERT_THROWS(HashTable::KeyNotFound, hash.find(25));

    hash.insert(Group(11));
    hash.insert(Group(12));
    hash.insert(Group(13));
    hash.insert(Group(14));
    hash.insert(Group(21));
    hash.insert(Group(16));
    //rehash
    ASSERT_EQUALS(5, hash.find(5).getID());
    ASSERT_EQUALS(1, hash.find(1).getID());

}

int main() {
    RUN_TEST(testInit);
    RUN_TEST(testInsert);
    RUN_TEST(testFind);
}
