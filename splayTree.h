

#ifndef WET_SPLAYTREE_H
#define WET_SPLAYTREE_H

#include "BST.h"
#include <cassert>
#include <stddef.h>

namespace trees {

    /**SPLAY SEARCH TREE
     * @tparam T - Type of data the tree would keep
     * @tparam Key - The key by which the tree will be sorted
     *               Key should overload comparision operators <,>,= */
    template<class T, class Key>
    class Splay : public BST<T, Key> {

        /**SPLAY
         * splaying to_splay to the root
         * @param to_splay - the node should be splayed */
        void splay(typename BST<T, Key>::Node* to_splay);

        /**ROTATE RIGHT
         * rotating n to the right (LL rotation)
         * @param n
         */
        void rotateRight(typename BST<T, Key>::Node* n);

        /**ROTATE LEFT
         * rotating n to the left (RR rotation)
         * @param n  */
        void rotateLeft(typename BST<T, Key>::Node* n);

    public:
        /**INSERT
         * insert the data to the tree and splaying it to the root
         * @param data
         * @param key
         * @exceptopn KeyAlreadyExist - if key is already in the tree
         *                              key will be splayed to the root*/
        void insert(const T& data, const Key& key, int value); //override;

        /**FIND
         * finds the key in the tree and splaying it to the top
         * @param key - the key of the data to be found
         * @return data that has been founded
         * @exception KeyNotFound - there is no node with the wanted key in tree
         *                          the parent of the key would have been, is spalyed*/
        T& find(const Key& key); //override;

        /**REMOVE
         * finds the key in the tree and splays it to the root.
         * remove the data by it's key from the tree.
         * @param key - the key of the data to be removed
         * @return the data that has been removed
         * @exception KeyNotFound - there is no node with the wanted key in tree
         *                          the parent of the key would have been, is spalyed*/
        T remove(const Key& key); //override;


        /**FIND MIN
         * finding the min in the tree by key, splay it and return its data
         * @return the data of min */
        T findMin(); //override

        /**FIND MAX
        * finding the max in the tree by key, splay it and return its data
        * @return the data of max */
        T findMax(); //override

        Key select(int k);

        int rank_weight(Key x);
    };

    template<class T, class Key>
    void Splay<T, Key>::rotateRight(typename BST<T, Key>::Node* n) {
        typename BST<T, Key>::Node* parent = n->parent;
        n->parent->left_son = n->right_son;
        if (n->right_son)
            n->right_son->parent = parent;
        n->parent = parent->parent;
        UPDATE_PARENT_SON(parent,
                          n) //connect n to grandfather. making it the 'root' of th sub-tree.
        n->right_son = parent;
        parent->parent = n;
        this->update_ranks(parent);
        this->update_ranks(n);
    }

    template<class T, class Key>
    void Splay<T, Key>::rotateLeft(typename BST<T, Key>::Node* n) {
        assert(n->parent);
        typename BST<T, Key>::Node* parent = n->parent;
        parent->right_son = n->left_son;
        if (n->left_son)
            n->left_son->parent = parent;
        n->parent = parent->parent;
        UPDATE_PARENT_SON(parent,
                          n) //connect n to grandfather. making it the 'root' of th sub-tree.
        n->left_son = parent;
        parent->parent = n;
        this->update_ranks(parent);
        this->update_ranks(n);
    }

    template<class T, class Key>
    void Splay<T, Key>::splay(typename BST<T, Key>::Node* to_splay) {
        if (to_splay == NULL) return; //empty tree
        if (to_splay->parent == NULL) { //splayed is already root
            this->root = to_splay;
            return;
        }
        typename BST<T, Key>::Node* grandP = to_splay->parent->parent;
        /*child of root*/
        if (grandP == NULL) {
            if (to_splay->parent->left_son == to_splay)//left child of root
                rotateRight(to_splay);
            else                            //right child of root
                rotateLeft(to_splay);
            this->root = to_splay;
            return;
        }
        /*has grandfather*/
        if (grandP->left_son && grandP->left_son->left_son == to_splay) { //LL
            rotateRight(to_splay->parent);
            rotateRight(to_splay);
        } else if (grandP->left_son &&
                   grandP->left_son->right_son == to_splay) { //LR
            rotateLeft(to_splay);
            rotateRight(to_splay);
        } else if (grandP->right_son &&
                   grandP->right_son->left_son == to_splay) { //RL
            rotateRight(to_splay);
            rotateLeft(to_splay);
        } else if (grandP->right_son &&
                   grandP->right_son->right_son == to_splay) { //RR
            rotateLeft(to_splay->parent);
            rotateLeft(to_splay);
        }

        /*run again*/
        splay(to_splay);
    }

    template<class T, class Key>
    T& Splay<T, Key>::find(const Key& key) {
        typename BST<T, Key>::Node* res = NULL;
        bool found = this->findRec(key, this->root, &res);
        splay(res);
        assert(this->root == res);
        if (!found) {
            throw typename BST<T, Key>::KeyNotFound(key);
        }
        return res->data;
    }

    template<class T, class Key>
    void Splay<T, Key>::insert(const T& data, const Key& key, int value) {
        try {
            BST<T, Key>::insert(data, key, value);
        } catch (typename BST<T, Key>::KeyAlreadyExist& e) {
            this->find(key); //using the Splay find, which will splay it.
            throw e;
        }
        this->find(key); //using the Splay find, which will splay it.
    }

    template<class T, class Key>
    T Splay<T, Key>::remove(const Key& key) {
        T saved_data = this->find(
                key); //splaying the node we want to delete to the root
        typename BST<T, Key>::Node* saved_left_son = this->root->left_son;
        typename BST<T, Key>::Node* saved_right_son = this->root->right_son;
        if (saved_right_son)//severing the right sub-tree from root.
            saved_right_son->parent = NULL;
        if (saved_left_son)//severing the left sub-tree from root.
            saved_left_son->parent = NULL;
        delete this->root;
        typename BST<T, Key>::Node* new_root = this->findMinRec(saved_right_son);
        if (new_root == NULL) //no right son at all
            this->root = saved_left_son;
        else { //new_root is the min of the right son sub-tree
            splay(new_root);
            new_root->left_son = saved_left_son;
            if (saved_left_son) saved_left_son->parent = new_root;
            assert(new_root->parent == NULL);
            this->root = new_root;
            //update ranks
            if (this->root->right_son) {
                typename BST<T, Key>::Node* update_start_node = this->findMinRec(
                        this->root->right_son);
                this->update_ranks_to_the_top(update_start_node);
            } else {
                this->update_ranks_to_the_top(this->root);
            }
        }
        this->size--;
        return saved_data;
    }

    template<class T, class Key>
    T Splay<T, Key>::findMin() {
        typename BST<T, Key>::Node* result = this->findMinRec(this->root);
        if (result) {
            splay(result);
            return result->data;
        }
        throw typename BST<T, Key>::TreeIsEmpty();
    }

    template<class T, class Key>
    T Splay<T, Key>::findMax() {
        typename BST<T, Key>::Node* result = this->findMaxRec(this->root);
        if (result) {
            splay(result);
            return result->data;
        }
        throw typename BST<T, Key>::TreeIsEmpty();
    }

    template<class T, class Key>
    Key Splay<T, Key>::select(int k) {
        Key result = BST<T, Key>::select(k);
        find(result);
        return result;
    }

    template<class T, class Key>
    int Splay<T, Key>::rank_weight(Key x) {
        this->find(x); //will splay x to the root
        int result = this->root->value;
        if (this->root->left_son)
            result += this->root->left_son->weight;
        return result;
    }

}/*namespace end*/
#endif //WET_SPLAYTREE_H
