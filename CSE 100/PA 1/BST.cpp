#include "BST.h"
#include <vector>

void deleteThis(BST::Node* temp)
{
    if (temp == nullptr)
        return;
    else
    {
        deleteThis(temp->leftChild);
        deleteThis(temp->rightChild);
        delete temp;
        temp = nullptr;
    }
}

/**
 * Implement the BST constructor
 */
BST::BST() {
    root = nullptr;
    numElements=0;
}

/**
 * Implement the BST destructor
 */
BST::~BST() {
    clear();
}

/**
 * Implement size() correctly
 */
unsigned int BST::size() const {
    return numElements;
}

/**
 * Implement clear() correctly without memory leaks
 */
void BST::clear() 
{
    deleteThis(root);
    root = nullptr;
    numElements = 0;
}

/**
 * Implement insert() correctly
 */
bool BST::insert(int element) {
    int direction = -1;
    bool loop = true;
    unsigned int number = 0;
    if (root == nullptr)
    {
        root = new BST::Node(element);
        numElements++;
        return true;
    }
    if (find(element))
        return false;
    else
    {
        BST::Node* current = root;
        while (number <= numElements && loop)
        {
            if (element > current->data)
            {
                if (current->rightChild == nullptr)
                {
                    loop = false;
                    direction = 0;
                }
                else
                    current = current->rightChild;
            }
            else if (element < current->data)
            {
                if (current->leftChild == nullptr)
                {
                    loop = false;
                    direction = 1;
                }
                else
                    current = current->leftChild;
            }
            number++;
        }
        if (number > numElements)
            return false;
        if (direction == 0)
        {
            current->rightChild = new BST::Node(element);
            current->rightChild->parent = current;
        }
        else
        {
            current->leftChild = new BST::Node(element);
            current->leftChild->parent = current;
        }
        numElements++;
        current = nullptr;
        return true;
    }
}

/**
 * Implement find() correctly
 */
bool BST::find(const int & query) const {
    BST::Node* current = root;
    if (current == nullptr)
        return false;
    if (current->data == query)
    {
        current = nullptr;
        return true;
    }
    else
    {
        for (unsigned int i = 0; i < numElements/2 + 1; i++)
        {
            if (current->data < query)
            {
                if (current->rightChild != nullptr)
                    current = current->rightChild;
                else
                    return false;
            }
            else if (current->data > query)
            {
                if (current->leftChild != nullptr)
                    current = current->leftChild;
                else
                    return false;
            }
            else if (current->data == query)
            {
                current = nullptr;
                return true;
            }
        }
    }
    current = nullptr;
    return false;
}

/**
 * Implement the getLeftMostNode() function correctly
 */
BST::Node* BST::getLeftMostNode() {
    if (root == nullptr)
        return nullptr; 
    BST::Node* leftNode = root;
    while (leftNode->leftChild != nullptr)
        leftNode = leftNode->leftChild;
    return leftNode;
}

/**
 * Implement the BST::Node successor function correctly
 */
BST::Node* BST::Node::successor() {
    BST::Node* current = this;
    if (current->rightChild != nullptr)
    {
        current = current->rightChild;
        while (current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }
    else
    {
        while (current->parent != nullptr)
        {
            if (current->parent->leftChild == current)
                return current->parent;
            else
                current = current->parent;
        }
        return nullptr;
    }

}
