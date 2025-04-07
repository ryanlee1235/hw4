#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    char letter = 'a';
    for(int i = 0; i < 30; i++)
    {
        bt.insert(std::make_pair(letter + i, i));
    }
<<<<<<< HEAD
    /*
    bt.insert(std::make_pair('d',4));
    bt.insert(std::make_pair('b',2));
    bt.insert(std::make_pair('g',7));
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('c',3));
    bt.insert(std::make_pair('e',5));
    */
=======
    // bt.insert(std::make_pair('d',4));
    // bt.insert(std::make_pair('b',2));
    // bt.insert(std::make_pair('g',7));
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('c',3));
    // bt.insert(std::make_pair('e',5));
    // bt.insert(std::make_pair('d',9));
    // bt.insert(std::make_pair('k',4));
    // bt.insert(std::make_pair('o',2));
    // bt.insert(std::make_pair('l',7));
    // bt.insert(std::make_pair('f',1));
    // bt.insert(std::make_pair('r',3));
    // bt.insert(std::make_pair('y',5));
    
>>>>>>> d9b2a39 (local changes)
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
<<<<<<< HEAD
    
    bt.print();
    /*
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
=======
    // bt.print();
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');
>>>>>>> d9b2a39 (local changes)

    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // bt.print();

    // bt.remove('d');
    // bt.print();

<<<<<<< HEAD
    bt.remove('a');
    bt.print();*/
=======
    // bt.remove('a');
    // bt.print();
>>>>>>> d9b2a39 (local changes)

/*
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    cout << "Erasing a" << endl;
    bt.remove('a');

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
*/
/*
    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
*/
    return 0;
}
