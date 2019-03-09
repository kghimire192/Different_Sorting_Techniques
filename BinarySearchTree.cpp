/**
 * @file BinarySearchTree.cpp
 * The implementation file for the Binary Search Tree class
 * @author Kanchan Ghimire
 * @date November 2016
 */
#include "BinarySearchTree.h"
#include <stdexcept>

using namespace std;


// Standard constructor for an empty tree
BinarySearchTree::BinarySearchTree() {
    // set the tree to empty
    root = nullptr;
    NOT_FOUND_MESSAGE = "Did not locate node in tree.";
}

// Standard destructor for the tree
BinarySearchTree::~BinarySearchTree() {
    TreeNode* thisNode = nullptr;           // current node in traversal


    // start at root
    thisNode = root;

    // do a postorder tree traversal with delete
    // TODO: postorderDelete(root);

    // reset root to nullptr
    root = nullptr;
    // TODO if (DEBUG) cout << "Tree is now empty." << endl;

    // we are done with this recursive function
    return;
}

// Determines if a tree is empty,
// returns true if there are no nodes, false if there are node
bool BinarySearchTree::isEmpty() const {
    if (root == nullptr)
        return true;
    else
        return false;
}

// Search for a node and set the pointers for the node itself, and it's parent.
// Used by insertNode, deleteNode, fetchNode and indirectly by updateNode
// key is the item we are searching for
// node will be a pointer to the node containing that item (or nullptr if not found)
// parent will be a pointer to the parent of the node (or nullptr)
// NOTE:  *& means "pass address by reference" so we can change the value of node/parent
//        * to point to where we want, and they can be accessed back in main.
void BinarySearchTree::findNode(string key, TreeNode*& node, TreeNode*& parent) const {
    // start at the root
    node = root;            // start looking at the root node
    parent = nullptr;       // root has no parent

    // loop through the tree, until we find it (or not)
    while(node != nullptr) {
        // is this node the one we are looking for?
        if (node->getData() == key) {
            // yup!  we found it
            // note that in the special case of the key being in the first node,
            // we'll have parent == nullptr
            // node and parent are already set, so we are ok.
            return;
        } else {
            // nope, move to the next one
            // set parent to this node
            parent = node;
            // move to the next one, either left or right
            if (key < node->getData()) { // less than
                // move left
                node = node->getLeft();
            } else { // greater than
                // move right
                node = node->getRight();
            }
        }
        // note that if we've reached the end of this branch without finding
        // anything, we'll have node = nullptr and parent = leaf
    }
    // NOTE:  in the case of an empty tree, with root == nullptr,
    // this function returns node == nullptr and parent == nullptr
}

// Insert a new node (will create a new TreeNode), following the Binary
// Search Tree rules.
void BinarySearchTree::insertNode(string newData) throw(logic_error) {
    TreeNode* newNode = nullptr;            // the new node we are adding
    TreeNode* searchNode = nullptr;         // search for where this node will go
    TreeNode* parentNode = nullptr;         // will point to the parent where this node will go

    // create node and fill the new node with data
    newNode = new TreeNode();               // get the memory
    newNode->setData(newData);               // store the new data

    // find where this node belongs in the tree by doing a search for it
    findNode(newData, searchNode, parentNode);  // note that searchNode and parentNode will change

    // searchNode should be null, otherwise we have a duplicate -- throw an error
    if (searchNode != nullptr) {
        // oops, this number is already in the tree
        throw logic_error("Error -- cannot insert a duplicate node into a binary search tree!");
    }
    // if the search was successful, and parentNode will be the parent for this node
    // special case -- if the tree is empty, prentNode will be nullptr
    if (parentNode == nullptr) {
        // set root to be this new node
        root = newNode;
    } else {
        // otherwise, figure if newNode should be a left or right child of this parentNode
        if (newData < parentNode->getData()) {
            // insert on the left
            parentNode->setLeft(newNode);
        } else {
            // insert on right
            parentNode->setRight(newNode);
        }
    }
}

// Remove and return the contents of a node, or NOT_FOUND_MESSAGE, restructuring the tree
// according to the Binary Search Tree rules.
string BinarySearchTree::deleteNode(string key) {
    TreeNode* searchNode = nullptr;    // used with findNode to find the target node
    TreeNode* parentNode = nullptr;    // parent of the target node
    TreeNode* tempPtr = nullptr;       // used if the deleted node has two children
    TreeNode* tempParent = nullptr;    // used if the deleted node has two children
    string returnValue = "";           // value to return
    bool rootFlag = false;             // true if we are deleting the root node

    // find the node to be deleted
    findNode(key, searchNode, parentNode);

    // if node is not present, return NOT_FOUND_MESSAGE
    if (searchNode == nullptr) {
        return NOT_FOUND_MESSAGE;
    }

    // store data so we can return it
    returnValue = searchNode->getData();

    // if the node is a root, then we have a special case!
    if (searchNode == root) {
        rootFlag = true;
    }

    // determine how to delete this node, based on number of children
    if (searchNode->getLeft() == nullptr && searchNode->getRight() == nullptr) {
        /////// this node is just a leaf ///////
        // handle special case of root
        if (rootFlag == true) {
            root = nullptr; // no nodes in the tree
        } else if (parentNode->getLeft() == searchNode) {
            // if the node to delete is the left child of the parent, then
            // need to set that left pointer to null
            parentNode->setLeft(nullptr);
        } else {
            // searchNode must be on the right side of the parent
            parentNode->setRight(nullptr);
        }
        // delete the node
        delete(searchNode);
        searchNode = nullptr;
    } else if (searchNode->getLeft() != nullptr && searchNode->getRight() == nullptr)
    {   /////// if there is only a left child of searchNode... /////
        // handle special case of root
        if (rootFlag == true) {
            root = searchNode->getLeft(); // root node is now left child
        } else if (parentNode->getLeft() == searchNode) {
            // if the node to delete is the left child of the parent, then
            // connect SearchNode's child to the left side of parent node
            parentNode->setLeft(searchNode->getLeft());
        } else {
            // searchNode must be on the right side of the parent
            parentNode->setRight(searchNode->getLeft());
        }
        // now we can delete this node
        delete(searchNode);
        searchNode = nullptr;

    } else if (searchNode->getLeft() == nullptr && searchNode->getRight() != nullptr) {
        /////// if there is only a right child of searchNode... /////
        // handle special case of root
        if (rootFlag == true) {
            root = searchNode->getRight(); // root node is now right child
        } else if (parentNode->getLeft() == searchNode) {
            // if the node to delete is the left child, then
            // connect to the left side of parent node
            parentNode->setLeft(searchNode->getRight());
        } else {
            // searchNode must be on the right side of the parent
            parentNode->setRight(searchNode->getRight());
        }
        // now we can delete this node
        delete(searchNode);
        searchNode = nullptr;
    } else {
        // if the node has two children, find the deleted node’s LEFT descendant that has the LARGEST
        // value, then move that node to where the deleted node is
        // (Note -- no need for special case for root node here, since we aren't deleting it, just copying)

        // use tempPtr and tempParent to move to left child of searchNode
        tempPtr = searchNode->getLeft();
        tempParent = searchNode;
        // now move tempPtr all the way to the right most leaf
        while (tempPtr->getRight() != nullptr) {
            tempParent = tempPtr;
            tempPtr = tempPtr->getRight();
        }
        // now tempPtr points to a leaf, and tempParent is the leaf's parent
        // we want the contents of this leaf to move to where searchNode is
        searchNode->setData(tempPtr->getData());
        // now, instead of deleting searchNode, we delete this leaf!
        // need to determine if we are deleting a left or right child of tempParent
        if (tempParent->getLeft() == tempPtr) {
            // tempPtr is the left child
            tempParent->setLeft(nullptr);
        } else {
            // tempPtr is the right child
            tempParent->setRight(nullptr);
        }
        // now delete it
        delete(tempPtr);
        tempPtr = nullptr;
    }

    // return the data
    return returnValue;
}

// Search for and return the contents of a node, or NOT_FOUND_MESSAGE.
string BinarySearchTree::fetchNode(string key) const {
    // need temp pointers for the node and the parent node
    TreeNode* targetNode = nullptr;         // will point to the node we want
    TreeNode* parentNode = nullptr;         // will poitn to the parent node (we don't use this here)

    // search for the node using findNode
    findNode(key, targetNode, parentNode);

    // if we find it, return the targetNode's key
    if (targetNode != nullptr) {
        return targetNode->getData();
    } else {
        return NOT_FOUND_MESSAGE;
    }
}

// Search for the old contents, remove it, then add the new contents.
// Implemented as a delete followed by an insert.  TODO:  should throw
// an exception if we can't find the old contents
void BinarySearchTree::updateNode(string oldContents, string newContents) {
    // delete the old one
    deleteNode(oldContents);
    // add the new one
    insertNode(newContents);
}


//In order tree traversal, appending the contents to a string which is returned
void BinarySearchTree::inorderTraversal(string myArray[], int& nextIndx) const {

    // traverse the tree in order (move left, visit, move right)
    // recursive function call, starting at root
    inorder(root,myArray,nextIndx);
}


//private method for an inorder tree traversal (recursive)
void BinarySearchTree::inorder(TreeNode* thisNode, string myArray[], int& nextIndx) const {

    // BASE CASE == when we have moved off the end of the tree
    if (thisNode == nullptr) {
        // reached the end, do nothing
        return;
    }

    // RECURSIVE CASE == a non-leaf tree node
    // move left
    if (thisNode->getLeft() != nullptr) {
        inorder(thisNode->getLeft(),myArray,nextIndx);
    }
    // visit
    myArray[nextIndx] = thisNode->getData();
    nextIndx++;

    // move right
    if (thisNode->getRight() != nullptr) {
        inorder(thisNode->getRight(), myArray,nextIndx);
    }

    // done with this node
    return;
}