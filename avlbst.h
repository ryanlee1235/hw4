#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertHelp (const std::pair<const Key, Value> &new_item, AVLNode<Key, Value>* curr);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node1, bool direction);
    void removeFix(AVLNode<Key, Value>* parent, int diff);
    void rotateRight(AVLNode<Key, Value>* node1);
    void rotateLeft(AVLNode<Key, Value>* node1);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(this->root_ == NULL)
    {
        AVLNode<Key, Value>* node1 = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        this->root_ = node1;
    }
    else
    {
        insertHelp(new_item, static_cast<AVLNode<Key, Value>*>(this->root_));
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelp(const std::pair<const Key, Value> &new_item, AVLNode<Key, Value>* current)
{
    // utilizes most of my code from BST, but adjusted to add balance and InsertFix() function
    // recursive insert function
    if(current == NULL)
    {
        return;
    }
    if(new_item.first < current->getKey()) // is new item to the left of current?
    {
        if(current->getLeft() == NULL)
        {
            // Add new node if the left child is of current doesn't exist
            AVLNode<Key, Value>* node1 = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
            current->setLeft(node1);
            // update balance, either inbalances it and we need to check with insert fix, or balances node
            if(current->getBalance() == 0)
            {
                current->setBalance(-1);
                insertFix(current, current->getLeft(), 0);

            }
            else
            {
                current->setBalance(0);
            }
        }
        else
        {
            // keep recursing until node with empty child is found
            insertHelp(new_item, current->getLeft());
            //return;
        }
    }
    else if(new_item.first > current->getKey())
    {
        // same as above but for if the key is larger than node
        if(current->getRight() == NULL)
        {
            AVLNode<Key, Value>* node1 = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
            current->setRight(node1);
            if(current->getBalance() == 0)
            {
                current->setBalance(1);
                insertFix(current, current->getRight(), 1);

            }
            else
            {
                current->setBalance(0);
            }
        }
        else
        {
            insertHelp(new_item, current->getRight());
            //return;
        }
    }
    else
    {
        // if the same key is entered, just update the value
        current->setValue(new_item.second);
        //return;
    }
    return;
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // keep track of balance difference, current, and parent node
    int diff = 0;
    AVLNode<Key, Value> *curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* parent = NULL;
    if(curr == NULL)
    {
        return;
    }
    else if(curr->getLeft() != NULL && curr->getRight() != NULL)
    {
        // if node has two children, swap with predecessor to make it one child
        AVLNode<Key, Value>* predecessorNode = static_cast<AVLNode<Key, Value>*>(this->predecessor(curr));
        nodeSwap(curr, predecessorNode);
    }
    if(curr->getLeft() != NULL && curr->getRight() == NULL)
    {
        // nodeSwap(curr, curr->getLeft());
        // checks if only one child exists
        parent = curr->getParent();
        AVLNode<Key, Value>* currLeft = curr->getLeft();
        
        currLeft->setParent(parent);
        if(parent != NULL)
        {
            if(parent->getLeft() == curr) // check which side the child is on
            {
                parent->setLeft(currLeft);
                //parent->updateBalance(1);
                // update the difference added from removing node
                diff = 1;
            }
            else
            {
                // update child of deleted node's parent
                parent->setRight(currLeft);
                //parent->updateBalance(-1);
                diff = -1;
            }
        }
        else
        {
            // no parent means the root_ must be set to currLeft
            this->root_ = currLeft;
        }
        delete curr;
        curr = NULL;
    }
    else if(curr->getRight() != NULL && curr->getLeft() == NULL)
    {
        // nodeSwap(curr, curr->getRight());
        parent = curr->getParent();
        AVLNode<Key, Value>* currRight = curr->getRight();
        
        currRight->setParent(parent);
        if(parent != NULL)
        {
            if(parent->getLeft() == curr) // check which side the child is on
            {
                parent->setLeft(currRight);
                //parent->updateBalance(1);
                diff = 1;
            }
            else
            {
                parent->setRight(currRight);
                //parent->updateBalance(-1);
                diff = -1;
            }
        }
        else
        {
            this->root_ = currRight;
        }
        delete curr;
        curr = NULL;
    }
    else
    {
        // simply delete node if no children but update parents/ root
        parent = curr->getParent();
        if(this->root_ == curr)
        {
            this->root_ = NULL;
        }
        else if(parent->getLeft() == curr) // check which side the child is on
        {
            parent->setLeft(NULL);
            //parent->updateBalance(1);
            diff = 1;
        }
        else if(parent->getRight() == curr)
        {
            parent->setRight(NULL);
            //parent->updateBalance(-1);
            diff = -1;
        }

        delete curr;
        curr = NULL;
    }
    // if(parent->getLeft() == curr) // check which side the child is on // DEBUG: deleted curr so this doesn't work
    // {
    //     diff = 1;
    // }
    // else
    // {
    //     diff = -1;
    // }
    // call removeFix to rebalance tree
    removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node1, bool direction)
{
    // bool direction makes it easier to keep track of which side the child is: 0 = left, 1 = right
    AVLNode<Key, Value>* gparent = parent->getParent();
    if(parent == NULL || gparent == NULL)
    {
        return;
    }
    if(gparent->getLeft() == parent) // if parent is left child of gparent
    {
        gparent->updateBalance(-1);
        if(gparent->getBalance() == 0)
        {
            return;
        }
        else if(gparent->getBalance() == -1)
        {
            insertFix(gparent, parent, 0); // recurse if gparent balance is still -1
        }
        else if(gparent->getBalance() == -2)
        {
            if(!direction) // zig zig case
            {
                rotateRight(gparent);
                parent->setBalance(0);
                gparent->setBalance(0);
            }
            else
            {
                // addressing all cases and updating balance as such
                rotateLeft(parent);
                rotateRight(gparent);
                if(node1->getBalance() == -1)
                {
                    parent->setBalance(0);
                    gparent->setBalance(1);
                    node1->setBalance(0);
                }
                else if(node1->getBalance() == 0)
                {
                    parent->setBalance(0);
                    gparent->setBalance(0);
                    node1->setBalance(0);
                }
                else if(node1->getBalance() == 1)
                {
                    parent->setBalance(-1);
                    gparent->setBalance(0);
                    node1->setBalance(0);
                }
            }
        }
    }
    else if(gparent->getRight() == parent) // if parent is a right child of gparent
    {
        gparent->updateBalance(1);
        if(gparent->getBalance() == 0)
        {
            return;
        }
        else if(gparent->getBalance() == 1)
        {
            insertFix(gparent, parent, 1); // recurse if gparent balance is still 1
        }
        else if(gparent->getBalance() == 2)
        {
            if(direction) // zig zig case
            {
                rotateLeft(gparent);
                parent->setBalance(0);
                gparent->setBalance(0);
            }
            else
            {
                rotateRight(parent);
                rotateLeft(gparent);
                if(node1->getBalance() == 1)
                {
                    parent->setBalance(0);
                    gparent->setBalance(-1);
                    node1->setBalance(0);
                }
                else if(node1->getBalance() == 0)
                {
                    parent->setBalance(0);
                    gparent->setBalance(0);
                    node1->setBalance(0);
                }
                else if(node1->getBalance() == -1)
                {
                    parent->setBalance(1);
                    gparent->setBalance(0);
                    node1->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node1, int diff)
{
    if(node1 == NULL)
    {
        return;
    }
    AVLNode<Key, Value>* parent = node1->getParent();
    // store next recursive case in advance
    int nextDiff = 0;
    if(parent != NULL)
    {
        if(parent->getLeft() == node1)
        {
            nextDiff = 1;
        }
        else
        {
            nextDiff = -1;
        }
    }
    if(diff == -1) // focusing on right child being removed first
    {
        if(node1->getBalance() + diff == -2) // removing node results in inbalance to the left subtree
        {
            AVLNode<Key, Value>* child = node1->getLeft();
            if(child->getBalance() == -1) // zig-zig case
            {
                rotateRight(node1);
                node1->setBalance(0);
                child->setBalance(0);
                removeFix(parent, nextDiff);
            }
            else if(child->getBalance() == 0) // balanced zig-zig case
            {
                rotateRight(node1);
                node1->setBalance(-1);
                child->setBalance(1);
            }
            else if(child->getBalance() == 1) // zig-zag case
            {
                AVLNode<Key, Value>* gchild = child->getRight(); // grandchild
                rotateLeft(child);
                rotateRight(node1);
                // same updating balance code as in insert's zig-zag
                if(gchild->getBalance() == 1)
                {
                    node1->setBalance(0);
                    child->setBalance(-1);
                    gchild->setBalance(0);
                }
                else if(gchild->getBalance() == 0)
                {
                    node1->setBalance(0);
                    child->setBalance(0);
                    gchild->setBalance(0);
                }
                else if(gchild->getBalance() == -1)
                {
                    node1->setBalance(1);
                    child->setBalance(0);
                    gchild->setBalance(0);
                }
                removeFix(parent, nextDiff);
            }
        }
        else if(node1->getBalance() + diff == -1) // removing doesn't make it inbalanced
        {
            node1->setBalance(-1);
        }
        else if(node1->getBalance() + diff == 0) // removing made parent balanced, but got to check to grandparent
        {
            node1->setBalance(0);
            removeFix(parent, nextDiff);
        }
    }
    else if(diff == 1) // above code mirrored for left case
    {
        if(node1->getBalance() + diff == 2) // removing node results in inbalance to the right subtree
        {
            AVLNode<Key, Value>* child = node1->getRight();
            if(child->getBalance() == 1) // zig-zig case
            {
                rotateLeft(node1);
                node1->setBalance(0);
                child->setBalance(0);
                removeFix(parent, nextDiff);
            }
            else if(child->getBalance() == 0) // balanced zig-zig case
            {
                rotateLeft(node1);
                node1->setBalance(1);
                child->setBalance(-1);
            }
            else if(child->getBalance() == -1) // zig-zag case
            {
                AVLNode<Key, Value>* gchild = child->getLeft(); // grandchild
                rotateRight(child);
                rotateLeft(node1);
                // same balance code as in insert's zig-zag
                if(gchild->getBalance() == -1)
                {
                    node1->setBalance(0);
                    child->setBalance(1);
                    gchild->setBalance(0);
                }
                else if(gchild->getBalance() == 0)
                {
                    node1->setBalance(0);
                    child->setBalance(0);
                    gchild->setBalance(0);
                }
                else if(gchild->getBalance() == 1)
                {
                    node1->setBalance(-1);
                    child->setBalance(0);
                    gchild->setBalance(0);
                }
                removeFix(parent, nextDiff);
            }
        }
        else if(node1->getBalance() + diff == 1) // removing doesn't make it inbalanced
        {
            node1->setBalance(1);
        }
        else if(node1->getBalance() + diff == 0) // removing made parent balanced, but got to check to grandparent
        {
            node1->setBalance(0);
            removeFix(parent, nextDiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node1)
{
    if(node1 == NULL)
    {
        return;
    }
    // set the new node as the left child of the original parent
    AVLNode<Key, Value>* newRoot = node1->getLeft();
    // after rotation, original node's left should be the new nodes original child
    node1->setLeft(newRoot->getRight());
    if(node1->getLeft() != NULL)
    {
        node1->getLeft()->setParent(node1);
    }
    // set the new root to have a child as the old root
    newRoot->setRight(node1);
    // set the parent of new root to original node's parent
    newRoot->setParent(node1->getParent());
    if(node1->getParent() != NULL)
    {
        // set original parent's child to the new root
        if(node1->getParent()->getLeft() == node1)
        {
            node1->getParent()->setLeft(newRoot);
        }
        else
        {
            node1->getParent()->setRight(newRoot);
        }
    }
    else
    {
        // if the olde node was the root, change root to new
        this->root_ = newRoot;
    }
    node1->setParent(newRoot);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node1)
{
    // same code as rotateRight
    if(node1 == NULL)
    {
        return;
    }
    AVLNode<Key, Value>* newRoot = node1->getRight();
    node1->setRight(newRoot->getLeft());
    if(node1->getRight() != NULL)
    {
        node1->getRight()->setParent(node1);
    }
    newRoot->setLeft(node1);
    newRoot->setParent(node1->getParent());
    if(node1->getParent() != NULL)
    {
        if(node1->getParent()->getLeft() == node1)
        {
            node1->getParent()->setLeft(newRoot);
        }
        else
        {
            node1->getParent()->setRight(newRoot);
        }
    }
    else
    {
        this->root_ = newRoot;
    }
    node1->setParent(newRoot);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
