/* @Author
Student Name: Erce Gülmez
Student ID : 150210728
Date: 10/05/2022 */
#include <list>
#include <vector>
#include "Node.h"
using namespace std;

class BinSTree{
    private:
        
        void preorder_traverse(Node*);
        void inorder_traverse(Node*);
        void postorder_traverse(Node*);
        void postorder_destruct(Node*);
        Node* find_par(int, Node***);
        void inorder_construct(Node*,list<int>&);
    
    public:
        Node* root;
        BinSTree();
        BinSTree(list<int> v);
        ~BinSTree();


        void add(int);
        bool contains(int);
        void remove(int);


        void printPreOrder();
        void printInOrder();
        void printPostOrder();
        void printBreadthFirst();

        void storeBSTNodes(Node*, vector<Node*> &);
        Node* buildTreeUtil(vector<Node*> &, int, int);
        Node* buildTree();

};