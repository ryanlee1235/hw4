#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    /*
    BinarySearchTree<char,int> bt;
    char letter = 'a';
    for(int i = 0; i < 30; i++)
    {
        bt.insert(std::make_pair(letter + i, i));
    }
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
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    
    bt.print();
    */
    /*
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // bt.print();

    // bt.remove('d');
    // bt.print();

    bt.remove('a');
    bt.print();*/

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

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));
    

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    at.print();
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    at.insert(std::make_pair('d',1));
    at.print();

    at.insert(std::make_pair('e',1));
    at.print();

    at.insert(std::make_pair('g',1));
    at.print();

    at.insert(std::make_pair('c',1));
    at.print();

    at.insert(std::make_pair('f',1));
    at.print();

    at.insert(std::make_pair('k',1));
    at.insert(std::make_pair('h',1));
    at.insert(std::make_pair('j',1));
    at.insert(std::make_pair('l',1));
    at.print();

    cout << "Erasing b" << endl;
    at.remove('b');
    at.print();

    at.remove('f');
    at.print();

    at.remove('c');
    at.print();

    at.remove('a');
    at.print();

    return 0;
}
