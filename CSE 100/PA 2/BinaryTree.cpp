#include "BinaryTree.h"

int height(BinaryTree::Node* current)
{
    if (current == nullptr)
        return 0;
    else
    {
        int leftC = height(current->leftChild);
        int rightC = height(current->rightChild);

        if (leftC > rightC)
            return (leftC+1);
        else
            return (rightC+1);
    }
}

void getMap(BinaryTree::Node* current, unordered_map<int,int>& treeMap)
{
    if (current == nullptr)
        return;
    
    getMap(current->leftChild, treeMap);
    int bal = height(current->rightChild) - height(current->leftChild);
    treeMap.insert({current->label, bal});
    getMap(current->rightChild, treeMap);
}

/**
 * Implement balanceFactors() correctly
 */
unordered_map<int,int> BinaryTree::balanceFactors() {
    unordered_map<int,int> balFactors;
    getMap(root, balFactors);
    return balFactors;
}
