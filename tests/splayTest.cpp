#include "../splayTree.h"

#include "testUtility.h"
#include <cassert>

using namespace trees;

void testInsert() {

    Splay<int, int> left_lace;
    left_lace.insert(1, 1, 1);
    left_lace.insert(2, 2, 2);
    left_lace.insert(3, 3, 3);
    left_lace.insert(4, 4, 4);

    Splay<int, int> right_lace;
    right_lace.insert(4, 4, 4);
    right_lace.insert(3, 3, 3);
    right_lace.insert(2, 2, 2);
    right_lace.insert(1, 1, 1);

    Splay<int, int> tree;
    tree.insert(5, 5, 5);
    tree.insert(10, 10, 10);
    tree.insert(7, 7, 7);
    tree.insert(2, 2, 2);
    tree.insert(4, 4, 4);
    tree.insert(6, 6, 6);

    bool thrown = false;
    try { //5 is already in tree. check that splaying has been done
        tree.insert(5, 5, 5);
    } catch (BST<int, int>::KeyAlreadyExist& e) {
        thrown = true;
    }
    ASSERT_EQUALS(5, tree.getRoot());
    assert(thrown);
    thrown = false;

    try { //10 is already in tree. check that splaying has been done
        tree.insert(10, 10, 10);
    } catch (BST<int, int>::KeyAlreadyExist& e) {
        thrown = true;
    }
    ASSERT_EQUALS(10, tree.getRoot());
    assert(thrown);

    thrown = false;
    try { //10 is root.
        tree.insert(10, 10, 10);
    } catch (BST<int, int>::KeyAlreadyExist& e) {
        thrown = true;
    }
    ASSERT_EQUALS(10, tree.getRoot());
    assert(thrown);
}

void testFind() {
    Splay<double, double> tree;
    tree.insert(3, 3, 3);
    tree.insert(7, 7, 7);
    tree.insert(4, 4, 4);
    tree.insert(8, 8, 8);
    tree.insert(6, 6, 6);

    ASSERT_TRUE(tree.find(4) == 4 && tree.getRoot() == 4); //4 was child of root
    ASSERT_TRUE(tree.find(8) == 8 && tree.getRoot() == 8);
    ASSERT_TRUE(tree.find(3) == 3 && tree.getRoot() == 3);

    bool thrown = false;
    try { //should be splaying 8
        tree.find(9);
    } catch (BST<double, double>::KeyNotFound& e) {
        thrown = true;
    }
    ASSERT_EQUALS(8, tree.getRoot());
    assert(thrown);
    thrown = false;

    thrown = false;
    try { //should be splaying 6
        tree.find(5);
    } catch (BST<double, double>::KeyNotFound& e) {
        thrown = true;
    }
    ASSERT_EQUALS(6, tree.getRoot());
    assert(thrown);

    thrown = false;
    try { //should be splaying 7
        tree.find(6.6);
    } catch (BST<double, double>::KeyNotFound& e) {
        thrown = true;
    }
    ASSERT_EQUALS(7, tree.getRoot());
    assert(thrown);
}

void testRemove() {
    Splay<double, double> tree;
    bool thrown = false;
    try {
        tree.remove(10000);
    } catch (BST<double, double>::KeyNotFound& e) {
        thrown = true;
    }
    assert(thrown);
    ASSERT_EQUALS(0, tree.getSize());

    tree.insert(10, 10, 10);
    tree.insert(3, 3, 3);
    tree.insert(4, 4, 4);
    tree.insert(2, 2, 2);
    tree.insert(6, 6, 6);
    tree.insert(8, 8, 8);

    thrown = false;
    try { //5 isn't in the tree. 4 will be splayed
        tree.remove(5);
    } catch (BST<double, double>::KeyNotFound& e) {
        thrown = true;
    }
    assert(thrown);
    ASSERT_EQUALS(4, tree.getRoot());

    ASSERT_NO_THROW(tree.remove(2));
    ASSERT_EQUALS(3, tree.getRoot());
    ASSERT_EQUALS(5, tree.getSize());

    ASSERT_NO_THROW(tree.remove(6));
    ASSERT_EQUALS(8, tree.getRoot());

    ASSERT_NO_THROW(tree.remove(8));
    ASSERT_EQUALS(10, tree.getRoot());
    ASSERT_EQUALS(3, tree.getSize());

    ASSERT_NO_THROW(tree.remove(3));
    ASSERT_EQUALS(4, tree.getRoot());

    ASSERT_NO_THROW(tree.remove(10));
    ASSERT_EQUALS(4, tree.getRoot());

    ASSERT_NO_THROW(tree.remove(4));
    thrown = false;
    try {
        tree.getRoot();
    } catch (BST<double, double>::TreeIsEmpty& e) {
        thrown = true;
    }
    assert(thrown);

}

void testSelect() {
    Splay<int, int> tree;
    tree.insert(10, 10, 10);
    tree.insert(3, 3, 3);
    tree.insert(4, 4, 4);
    tree.insert(2, 2, 2);
    tree.insert(6, 6, 6);
    tree.insert(8, 8, 8);

    ASSERT_EQUALS(2, tree.select(1));
    ASSERT_EQUALS(6, tree.select(4));
    ASSERT_EQUALS(3, tree.select(2));
    ASSERT_EQUALS(3, tree.getRoot());

    ASSERT_EQUALS(10, tree.select(6));
    ASSERT_EQUALS(8, tree.select(5));
    ASSERT_EQUALS(4, tree.select(3));
    ASSERT_EQUALS(4, tree.getRoot());

    bool thrown = false;
    try {
        tree.select(10);
    } catch (BST<int, int>::InvalidInput& e) {
        thrown = true;
    }
    assert(thrown);

}

void testRank() {
    Splay<int, int> tree;
    tree.insert(10, 10, 10);
    tree.insert(3, 3, 3);
    tree.insert(4, 4, 4);
    tree.insert(2, 2, 2);
    tree.insert(6, 6, 6);
    tree.insert(8, 8, 8);

    ASSERT_EQUALS(33, tree.rank_weight(10));
    ASSERT_EQUALS(23, tree.rank_weight(8));
    ASSERT_EQUALS(9, tree.rank_weight(4));
    ASSERT_EQUALS(4, tree.getRoot());

    ASSERT_EQUALS(2, tree.rank_weight(2));
    ASSERT_EQUALS(15, tree.rank_weight(6));
    ASSERT_EQUALS(5, tree.rank_weight(3));
    ASSERT_EQUALS(3, tree.getRoot());

    bool thrown = false;
    try {
        tree.rank_weight(-1);
    } catch (BST<int, int>::KeyNotFound& e) {
        thrown = true;
    }
    assert(thrown);
}

int main() {
    RUN_TEST(testInsert);
    RUN_TEST(testFind);
    RUN_TEST(testRemove);
    RUN_TEST(testSelect);
    RUN_TEST(testRank);
    return 0;
}