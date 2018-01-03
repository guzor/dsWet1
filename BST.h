
#ifndef HW1_BST_H
#define HW1_BST_H

#include <exception>
#include <new>
#include <stddef.h>
#include <cassert>

/**updating the son as if he is a left son or right son*/
#define UPDATE_PARENT_SON(n, updated_son) if ((n)->parent){\
            if((n)->parent->left_son == (n))\
                (n)->parent->left_son = (updated_son);\
            else\
                (n)->parent->right_son = (updated_son);}

namespace trees {

    /**BINARY SEARCH TREE
     * @tparam T - Type of data the tree would keep
     * @tparam Key - The key by which the tree will be sorted
     *               Key should overload comparision operators <,>,= */
    template<class T, class Key>
    class BST {

    protected:
        struct Node {
            T data;
            Key key;
            int size_of_sub_tree;
            int weight;
            int value;
            Node* parent;
            Node* left_son;
            Node* right_son;

            /**CONSTRUCTOR
             * @param data - The node data
             * @param key - unique key by which the node should be placed. */
            Node(const T& data, const Key& key, int value);
        };

        Node* root; //tree's root
        int size;

        /**FIND MIN
         * finding the min (by key) node in ptr's sub-tree
         * @param ptr - the root node of the sub-tree
         * @return - pointer to the minimal node of NULL if empty*/
        Node* findMinRec(Node* ptr);

        /**FIND MAX
         * finding the max (by key) node in ptr's sub-tree
         * @param ptr - the root node of the sub-tree
         * @return - pointer to the minimal node of NULL if empty*/
        Node* findMaxRec(Node* ptr);

        /**FIND REC
         * recursive helper function for find.
         * finding node with key in current's sub-tree.
         * @param key - the key we are searching
         * @param current - the current root's node
         * @param res - the result will be put in res:
         *              if key was found- res will be key's node
         *              if key wasn't found- res will be where key's should have been
         *              if current is NULL- NULL
         * @return true if key was founded, otherwise false  */
        bool findRec(const Key& key, Node* current, Node** res);

        void update_ranks_to_the_top(Node* ptr);

        void update_ranks(Node* n);

    private:
        /**COPY REC
         * recursive helper function for copy
         * @param ptr - the source tree's node
         * @param new_node_parent - the parent of the current node in the new tree
         * @return The new sub-tree new root's node. */
        Node* copyRec(const Node* ptr, Node* new_node_parent);

        /**DELETE REC
         * recursive helper function for deleting the tree
         * delete ptr sub-trees and then delete ptr itself
         * @param ptr - the current node to delete.  */
        void deleteRec(Node* ptr);

        /**INORDER ON DATA AND KEY REC
         * recursive helper for inorder function. operating on both data and key
         * @param p - the current node of the tree */
        template<class Func>
        void inorderDataAndKeyRec(Func& function, Node* p);


        /**INORDER REC
         * recursive helper for inorder function. operating on data.
         * @param p - the current node of the tree */
        template<class Func>
        void inorderDataRec(Func& function, Node* p);

        /**REVERSE INORDER REC
         * recursive helper for inorder fucdtion. operating on data.
         * @param p - the current node of the tree */
        template<class Func>
        void reverseInorderRec(Func& function, Node* p);


    public:
        /**EMPTY CONSTRUCTOR
         * initializing the tree with a null root*/
        BST();

        /**CONSTRUCTOR
         * initializing the tree with root's data and key
         * @param root_data - the root data
         * @param key - the root key */
        BST(const T& root_data, const Key& key, int value);

        /**COPY CONSTRUCTOR
         * @param tree - the source tree*/
        BST(const BST& tree);

        /**DESTRUCTOR
         * deleting the tree and al it's nodes */
        ~BST();


        /**ASSIGNMENT OPERATOR
         * @param tree - the source tree */
        BST& operator=(const BST& tree);


        /**INSERT
         * inserts new data (with key) to the tree
         * @param data
         * @param key
         * @exceptopn KeyAlreadyExist - if key is already in the tree */
        virtual void insert(const T& data, const Key& key, int value);

        /**FIND
         * finds the data with the wanted key
         * @param key - the key of the data to be found
         * @return data that has been founded
         * @exception KeyNotFound - there is no node with the wanted key in tree
         */
        virtual T& find(const Key& key);

        /**REMOVE
         * remove the data by it's key from the tree
         * @param key - the key of the data to be removed
         * @return the data that has been removed
         * @exception KeyNotFound - there is no node with the wanted key in tree
         */
        virtual T remove(const Key& key);

        /**FIND MAX
         * finding the max in the tree by key and return its data
         * @return the data of max
         */
        virtual T findMax();

        /**FIND MIN
         * finding the min in the tree by key and return its data
         * @return the data of min */
        virtual T findMin();

        /**INORDER
         * apply the function on each tree's data by inorder
         * @tparam Func - function object that overload operator() and has one
         *                parameter of type T
         * @param function - the function to apply for each data */
        template<class Func>
        void inorderData(Func& function);


        /**INORDER ON DATA AND KEY
         * apply the function on each tree's data and key by inorder
         * @tparam Func - function object that overload operator() and has two
         *                parameter: type T and type Key
         * @param function - the function to apply */
        template<class Func>
        void inorderDataAndKey(Func& function);

        /**REVERSE INORDER
         * apply the function on each tree's data by inorder
         * @tparam Func - function object that overload operator() and has one
         *                parameter of type T
         * @param function - the function to apply for each data */
        template<class Func>
        void reverseInorder(Func& function);

        /**GET ROOT
         * @return the root's data
         * @exceptopn TreeIsEmpty if tree is empty */
        T getRoot() const;

        /**GET SIZE
         * @return the size of the tree */
        int getSize() const;

        //TODO DESCRIPTION
        virtual Key select(int k);

        //TODO virtual int rank_weight(Key x);

        /**-------------ERRORS--------------------------------------**/
        class TreeException : public std::exception {
        };

        class KeyNotFound : public TreeException {
            Key element;
        public:
            explicit KeyNotFound(const Key& key) : element(key) {}
        };

        class KeyAlreadyExist : public TreeException {
            Key element;
        public:
            explicit KeyAlreadyExist(const Key& key) : element(key) {}
        };

        class TreeIsEmpty : public TreeException {
        };

        class InvalidInput : public TreeException {
        };
    };

    template<class T, class Key>
    BST<T, Key>::BST(): root(NULL), size(0) {}

    template<class T, class Key>
    BST<T, Key>::BST(const T& root_data, const Key& key, int value):
            root(new Node(root_data, key, value)), size(1) {}

    template<class T, class Key>
    BST<T, Key>::~BST() {
        if (root != NULL) {
            deleteRec(root);
        }
    }

    template<class T, class Key>
    BST<T, Key>& BST<T, Key>::operator=(const BST& tree) {
        Node* saved = this->root;
        try {
            this->root = copyRec(tree.root, NULL);
        } catch (std::bad_alloc&) {
            this->root = saved;
            throw std::bad_alloc();
        }
        deleteRec(this->root);
        return *this;
    }

    template<class T, class Key>
    void BST<T, Key>::deleteRec(Node* ptr) {
        if (ptr == NULL) return;
        deleteRec(ptr->left_son);
        deleteRec(ptr->right_son);
        delete ptr;
    }

    template<class T, class Key>
    BST<T, Key>::BST(const BST& tree) : size(tree.size) {
        this->root = copyRec(tree.root, NULL);
    }

    template<class T, class Key>
    typename BST<T, Key>::Node*
    BST<T, Key>::copyRec(const Node* ptr, Node* new_node_parent) {
        if (ptr == NULL) return NULL;
        Node* new_root = new Node(ptr->data, ptr->key, ptr->value);
        new_root->weight = ptr->weight;
        new_root->size_of_sub_tree = ptr->size_of_sub_tree;
        new_root->parent = new_node_parent;
        new_root->left_son = copyRec(ptr->left_son, new_root);
        new_root->right_son = copyRec(ptr->right_son, new_root);
        return new_root;
    }

    template<class T, class Key>
    T& BST<T, Key>::find(const Key& key) {
        Node* res = NULL;
        if (findRec(key, root, &res))
            return res->data;
        throw KeyNotFound(key);
    }

    template<class T, class Key>
    bool BST<T, Key>::findRec(const Key& key, Node* current, Node** res) {
        if (current == NULL) {
            *res = NULL;
            return false;
        }
        if (current->key == key) { //key founded
            *res = current;
            return true;
        }
        bool found;
        if (current->key > key) //search left tree
            found = findRec(key, current->left_son, res);
        else                    //search right tree
            found = findRec(key, current->right_son, res);
        if (*res == NULL) //current is the parent where key should have been
            *res = current;
        return found;
    }

    template<class T, class Key>
    void BST<T, Key>::insert(const T& data, const Key& key, int value) {
        Node* new_node_parent = NULL;
        if (findRec(key, root, &new_node_parent))
            throw KeyAlreadyExist(key);
        //new_node_parent is the parent of the node that should be added
        if (new_node_parent) {
            if (key < new_node_parent->key) {
                new_node_parent->left_son = new Node(data, key, value);
                new_node_parent->left_son->parent = new_node_parent;
            } else {
                new_node_parent->right_son = new Node(data, key, value);
                new_node_parent->right_son->parent = new_node_parent;
            }
            update_ranks_to_the_top(new_node_parent);
        } else { //parent is null meaning the tree is empty
            root = new Node(data, key, value);
        }
        size++;
    }

    template<class T, class Key>
    typename BST<T, Key>::Node* BST<T, Key>::findMinRec(Node* ptr) {
        if (ptr == NULL)
            return NULL;
        while (ptr->left_son)
            ptr = ptr->left_son;
        return ptr;
    }

    template<class T, class Key>
    typename BST<T, Key>::Node* BST<T, Key>::findMaxRec(Node* ptr) {
        if (ptr == NULL)
            return NULL;
        while (ptr->right_son)
            ptr = ptr->right_son;
        return ptr;
    }


    template<class T, class Key>
    T BST<T, Key>::remove(const Key& key) {
        Node* to_delete = NULL;
        if (!findRec(key, root, &to_delete))
            throw KeyNotFound(key);
        T deleted_data = to_delete->data;
        //has two sons
        if (to_delete->left_son != NULL &&
            to_delete->right_son != NULL) {
            Node* next = findMinRec(to_delete->right_son);
            to_delete->data = next->data;
            to_delete->key = next->key;
            to_delete->value = next->value;
            delete next;
            Node* new_next = findMinRec(to_delete->right_son);
            update_ranks_to_the_top(new_next);
        }
        Node* to_delete_parent = to_delete->parent;
        //is leaf
        if (to_delete->left_son == NULL &&
            to_delete->right_son == NULL) {
            UPDATE_PARENT_SON(to_delete, NULL)
            delete to_delete;
            update_ranks_to_the_top(to_delete_parent);
        }
            //has one son
        else {
            Node* saved_son;
            if (to_delete->left_son)
                saved_son = to_delete->left_son;
            else
                saved_son = to_delete->right_son;
            UPDATE_PARENT_SON(to_delete, saved_son)
            saved_son->parent = to_delete->parent;
            delete to_delete;
            update_ranks_to_the_top(to_delete_parent);
        }
        size--;
        return deleted_data;
    }

    template<class T, class Key>
    T BST<T, Key>::findMin() {
        Node* result = findMinRec(root);
        if (result)
            return result->data;
        throw TreeIsEmpty();
    }

    template<class T, class Key>
    T BST<T, Key>::findMax() {
        Node* result = findMaxRec(root);
        if (result)
            return result->data;
        throw TreeIsEmpty();
    }

    template<class T, class Key>
    template<class Func>
    void BST<T, Key>::inorderData(Func& function) {
        inorderDataRec(function, root);
    }

    template<class T, class Key>
    template<class Func>
    void BST<T, Key>::inorderDataRec(Func& function, Node* p) {
        if (p == NULL) return;
        inorderDataRec(function, p->left_son);
        function(p->data);
        inorderDataRec(function, p->right_son);
    }

    template<class T, class Key>
    template<class Func>
    void BST<T, Key>::inorderDataAndKey(Func& function) {
        inorderDataAndKeyRec(function, root);
    }

    template<class T, class Key>
    template<class Func>
    void BST<T, Key>::inorderDataAndKeyRec(Func& function, Node* p) {
        if (p == NULL) return;
        inorderDataAndKeyRec(function, p->left_son);
        function(p->data, p->key);
        inorderDataAndKeyRec(function, p->right_son);
    }

    template<class T, class Key>
    template<class Func>
    void BST<T, Key>::reverseInorder(Func& function) {
        reverseInorderRec(function, root);
    }

    template<class T, class Key>
    template<class Func>
    void BST<T, Key>::reverseInorderRec(Func& function, Node* p) {
        if (p == NULL) return;
        reverseInorderRec(function, p->right_son);
        function(p->data);
        reverseInorderRec(function, p->left_son);
    }

    template<class T, class Key>
    T BST<T, Key>::getRoot() const {
        if (root == NULL) throw TreeIsEmpty();
        return root->data;
    }

    template<class T, class Key>
    int BST<T, Key>::getSize() const {
        return size;
    }

    template<class T, class Key>
    void BST<T, Key>::update_ranks_to_the_top(Node* ptr) {
        if (ptr == NULL)
            return;
        update_ranks(ptr);
        update_ranks_to_the_top(ptr->parent);
    }

    template<class T, class Key>
    void BST<T, Key>::update_ranks(Node* n) {
        if (n == NULL)
            return;
        n->size_of_sub_tree = 1;
        n->weight = n->value;
        if (n->right_son) {
            n->size_of_sub_tree += n->right_son->size_of_sub_tree;
            n->weight += n->right_son->weight;
        }
        if (n->left_son) {
            n->size_of_sub_tree += n->left_son->size_of_sub_tree;
            n->weight += n->left_son->weight;
        }
    }

    template<class T, class Key>
    Key BST<T, Key>::select(int k) {
        if (k > size || k <= 0)
            throw InvalidInput();
        Node* ptr = this->root;
        while (ptr) {
            int size_of_left = 0;
            if (ptr->left_son)
                size_of_left = ptr->left_son->size_of_sub_tree;
            if (size_of_left == k - 1)
                return ptr->key;
            if (size_of_left > k - 1) {
                ptr = ptr->left_son;
            } else {
                assert(size_of_left < k - 1);
                assert(ptr->right_son);
                k = k - size_of_left - 1;
                ptr = ptr->right_son;
            }
        }
        assert(false);
        throw InvalidInput();
    }

/*-------------------------------------------------------------*/
/*----------------------------NODE-----------------------------*/
    template<class T, class Key>
    BST<T, Key>::Node::Node(const T& data, const Key& key, int value):
            data(data), key(key), size_of_sub_tree(1), weight(value), value(value),
            parent(NULL), left_son(NULL), right_son(NULL) {}

/*-------------------------------------------------------------*/

}

#endif //HW1_BST_H
