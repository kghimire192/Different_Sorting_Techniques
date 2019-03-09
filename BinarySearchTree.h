/**
 * @file BinarySearchTree.h
 * The header file for the Binary Search Tree class
 * @author Kanchan Ghimire
 * @date November 2016
 */

#ifndef CPSC_2500_PROJECT_3_KGHIMIRE92_BINARYSEARCHTREE_H
#define CPSC_2500_PROJECT_3_KGHIMIRE92_BINARYSEARCHTREE_H


#include "TreeNode.h"
#include <stdexcept>
using namespace std;

class BinarySearchTree {

private:
    /** pointer to the root node of the tree */
    TreeNode* root;
    /** returned by findNode if not found */
    string NOT_FOUND_MESSAGE;

public:

    /**
     * Standard constructor for an empty tree
     */
    BinarySearchTree();

    /**
     * Standard destructor for the tree
     */
    ~BinarySearchTree();

    /**
     * Determines if a tree is empty
     * @return true if there are no nodes, false if there are node
     */
    bool isEmpty() const;

    /**
     * Search for a node and set the pointers for the node itself, and it's parent.
     * Used by insertNode, deleteNode, fetchNode and indirectly by updateNode.
     * NOTE:  *& means "pass address by reference" so we can change the value of node/parent
     * to point to where we want, and they can be accessed back in main.
     * @param key the item we are searching for
     * @param node a pointer to the node containing that item (or nullptr if not found)
     * @param parent a pointer to the parent of the node (or nullptr)
     */
    void findNode(string key, TreeNode*& node, TreeNode*& parent) const;

    /**
     * Insert a new node (will create a new TreeNode), following the Binary
     * Search Tree rules.
     * @param newData the information to insert into the node
     * @throws a logic_error if a duplicate node is inserted
     */
    void insertNode(string newData) throw(logic_error);

    /**
     * Remove and return the contents of a node, restructuring the tree
     * according to the Binary Search Tree rules.
     * @param key the identifying information for the node to delete
     * @return the contents of a node, or NOT_FOUND_MESSAGE
     */
    string deleteNode(string key);

    /**
     * Search for and return the contents of a node.
     * @param key the item to search for
     * @return the contents of the node (currently just the key), or NOT_FOUND_MESSAGE
     */
    string fetchNode(string key) const;

    /**
     * Search for the old contents, remove it, then add the new contents.
     * Implemented as a delete followed by an insert.  TODO:  should throw
     * an exception if we can't find the old contents
     * @param oldContents the item to remove
     * @param newContents the item to add
     */
    void updateNode(string oldContents, string newContents);


    /**
     * In order tree traversal, appending the contents to a string which is returned
     * @param myArray[] the array to sort
     * @param nextIndx passing it by reference
     * @return a string representing the contents of the tree
     */
    void inorderTraversal(string myArray[], int& nextIndx) const;

private:
    /**
     * private method for an inorder tree traversal (recursive)
     * @param thisNode node that we are currently at (where we are starting this time)
     * @param outString the final string, where we "visit" by concatenating the contents (modified by this function)
     * @param myArray[] array to sort
     * @param nextIndx passing the next index by reference
     */
    void inorder(TreeNode* thisNode, string myArray[], int& nextIndx) const;

};
#endif //CPSC_2500_PROJECT_3_KGHIMIRE92_BINARYSEARCHTREE_H
