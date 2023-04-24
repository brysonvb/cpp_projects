#include "HCTree.hpp"
#include <string>
#include <stack>

bool bothChildrenNull(const HCNode* node)
{
    return (node->c0 == nullptr && node->c1 == nullptr);
}

HCNode* HCTree::makeNode(int count, unsigned char symbol, HCNode* left, HCNode* right) {
    HCNode* node = new HCNode(count, symbol);
    node->c0 = left;
    node->c1 = right;
    if (left != nullptr)
        left->p = node;
    if (right != nullptr)
        right->p = node;
    return node;
}

void clearNode(HCNode* node)
{
    if (node == nullptr)
        return;
    else
    {
        clearNode(node->c0);
        clearNode(node->c1);
        delete node;
        node = nullptr;
    }
}

HCTree::~HCTree()
{
  clearNode(root);
  if (bothChildrenNull(root))
    delete root;
}

void HCTree::build(const vector<int>& freqs)
{
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    
    // build queue and leaves hash table
    HCNode* temp;

    for (unsigned int i = 0; i < freqs.size(); i++)
    {    
        if (freqs[i] > 0) {
            unsigned char symbol = i;
            temp = makeNode(freqs[i], symbol,nullptr,nullptr);
            pq.push(temp);
            leaves[i] = temp;
        }
    }
 
    // build tree
    while (pq.size() > 1)
    {
        HCNode* c0 = pq.top();
        pq.pop();
        HCNode* c1 = pq.top();
        pq.pop();
        pq.push(makeNode((c0->count + c1->count), '\0', c0, c1));
    }
    root = pq.top();
    pq.pop();
}

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const
{
    HCNode* currNode = leaves.at(symbol);
    stack<unsigned char> code;
    
    if (currNode == root) 
        code.push(0);
    while (currNode->p != nullptr) {
        if (currNode->p->c1 == currNode) { // node is a 1 both Children Null
            code.push(1);
        }
        else {
            code.push(0);
        }
        currNode = currNode->p;
    }
    while (!code.empty()) {
        out.write_bit(code.top());
        code.pop();
    }
}

int HCTree::decode(FancyInputStream & in) const
{
    HCNode* currNode = root;
    int currBit;
    do {
        currBit = in.read_bit();
        if (currBit == 0 && !bothChildrenNull(currNode)) { 
            currNode = currNode->c0;
        }
        else if (currBit == 1 && !bothChildrenNull(currNode)) {
            currNode = currNode->c1;
        }
    } while(!bothChildrenNull(currNode) && currBit != -1);
  
    if (currBit != -1)
        return currNode->symbol;
    else
        return -1;
}
