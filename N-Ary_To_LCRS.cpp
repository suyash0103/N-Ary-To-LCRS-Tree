// Refer to this: https://en.wikipedia.org/wiki/Left-child_right-sibling_binary_tree
// Test case taken here is the same as that mentioned in above wiki page

#include<bits/stdc++.h>
#include<vector>

using namespace std;

// Below struct will represent the initial N-Ary tree. children is a vector which will have list of all child nodes of a node
struct TernaryNode {
    int val;
    vector<TernaryNode*> children;
    TernaryNode(int x) : val(x) {}
};

// LCRS Node structure. Sibling is analogous to right pointer in a binary tree
struct LCRSNode {
    int val;
    LCRSNode *left;
    LCRSNode *sibling;
    LCRSNode(int x) : val(x) {}
};

LCRSNode* convertToLCRS(TernaryNode* node) {
    // Return null if node is null
    if(node == NULL) {
        return NULL;
    }

    LCRSNode* head = NULL;
    LCRSNode* tail = NULL;

    // Loop over all children of node
    if(node->children.size() > 0) {
        for(int i = 0; i < node->children.size(); i++) {
            LCRSNode* currentNode = convertToLCRS(node->children[i]);

            // If head is null, it means we are at the left most child, mark this as head and tail, for further children, keep assigning them as siblings of their previous node (like a linked list)
            if(head == NULL) {
                head = currentNode;
                tail = currentNode;
            } else {
                tail->sibling = currentNode;
                tail = currentNode;
            }
        }
    }

    // Assign head node formed above as the left child of current node, which is passed as parameter of function, after converting it to LCRSNode
    LCRSNode* convertedNode = new LCRSNode(node->val);
    convertedNode->left = head;

    return convertedNode;
}

// PreOrder traversal
void preOrder(LCRSNode* node) {
    if(node == NULL) {
        return;
    }

    cout << node->val << endl;
    preOrder(node->left);
    preOrder(node->sibling);
}

int main() {
    cout << "Program Started" << endl;

    TernaryNode* root = new TernaryNode(1);
    TernaryNode* node2 = new TernaryNode(2);
    TernaryNode* node3 = new TernaryNode(3);
    TernaryNode* node4 = new TernaryNode(4);
    TernaryNode* node5 = new TernaryNode(5);
    TernaryNode* node6 = new TernaryNode(6);
    TernaryNode* node7 = new TernaryNode(7);
    TernaryNode* node8 = new TernaryNode(8);
    TernaryNode* node9 = new TernaryNode(9);

    vector<TernaryNode*> v1;
    v1.push_back(node2);
    v1.push_back(node3);
    v1.push_back(node4);

    vector<TernaryNode*> v2;
    v2.push_back(node5);
    v2.push_back(node6);

    vector<TernaryNode*> v3;
    v3.push_back(node7);

    vector<TernaryNode*> v4;
    v4.push_back(node8);
    v4.push_back(node9);

    root->children = v1;
    node2->children = v2;
    node4->children = v3;
    node7->children = v4;

    LCRSNode* convRoot = convertToLCRS(root);

    preOrder(convRoot);
}