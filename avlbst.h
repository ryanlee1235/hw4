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
    void balance(AVLNode<Key, Value>* node1);
    virtual void insertHelp (const std::pair<const Key, Value> &new_item, AVLNode<Key, Value>* curr);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node1, bool direction);
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
        //balance(static_cast<AVLNode<Key, Value>*>(this->root_));
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelp(const std::pair<const Key, Value> &new_item, AVLNode<Key, Value>* current)
{
    /*
    if(curr == NULL)
    {
        curr = new AVLNode(new_item.first, new_item.second, NULL);
        return curr;
    }
    else if(new_item.first < curr->getKey())
    {
        curr->setLeft(insertHelp(new_item, curr->getLeft()));

    }
    else if(new_item.first > curr->getKey())
    {
        insertHelp(new_item, curr->getRight());
    }
    else if(new_item.first == curr->getKey())
    {

    }

    {
        */
    if(current == NULL)
    {
        return;
    }
    if(new_item.first < current->getKey())
    {
        if(current->getLeft() == NULL)
        {
            AVLNode<Key, Value>* node1 = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
            current->setLeft(node1);
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
            insertHelp(new_item, current->getLeft());
            //return;
        }
    }
    else if(new_item.first > current->getKey())
    {
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
}

template<class Key, class Value>
void AVLTree<Key, Value>::balance(AVLNode<Key, Value>* node1)
{
    if(node1 == NULL)
    {
        return;
    }

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
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node1)
{
    if(node1 == NULL)
    {
        return;
    }
    AVLNode<Key, Value>* newRoot = node1->getLeft();
    node1->setLeft(newRoot->getRight());
    if(node1->getLeft() != NULL)
    {
        node1->getLeft()->setParent(node1);
    }
    newRoot->setRight(node1);
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
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node1)
{
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
