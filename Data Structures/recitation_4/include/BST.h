/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 22/04/2022 */
#ifndef BST_DEF
#define BST_DEF

#include <vector>
#include "BSTNode.h"

using namespace std;

class BST{
    private:
        Node* root;

        void postorder_traverse(Node*);
        void postorder_destruct(Node*);
        
        
    public:
        BST();
        ~BST();

        Node* get_root();
        void add(int);
        void corrupted_add(vector<int>);
        bool contains(int);
        int maxSumBST(Node*);
        void printPostOrder();
        bool isBST(Node*);
        int findSum(Node*);
};

#endif
