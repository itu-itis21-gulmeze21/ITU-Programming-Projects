#include <iostream>
#include <stdio.h>
#include "Node.h"
#pragma once
using namespace std;

class RBTree{
    private:
        Node* root;
        Node* NIL;//NIL that exists as the children of leaves
        
    public:
        RBTree();
        void inorder_traverse(Node*, ofstream&);
        Node* get_root();
        void set_root(Node*);
        void insert_node(Node*);
        void insert_fixup(Node*);
        void right_rotate(Node*);
        void left_rotate(Node*);
        void transplant(Node*,Node*);
        void delete_node(Node*);
        void delete_fixup(Node*);
        int findMinvruntime();
        bool isEmpty();
};