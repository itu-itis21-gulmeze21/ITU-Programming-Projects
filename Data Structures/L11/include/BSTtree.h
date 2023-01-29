#include "Node.h"

class BSTtree
{
private:
    Node* root;
    void preorder_traverse(Node*);
    void inorder_traverse(Node*);
    void postorder_traverse(Node*);
    void postorder_destruct(Node*);
    Node* find_par(int,Node**);
public:
    BSTtree();
    ~BSTtree();

    void add(int);
    bool contains(int);
    void remove(int);

    void printPreOrder();
    void printInOrder();
    void printPostOrder();
    void printBreadthFirst();
    int sumOfTree(Node*);
    Node* getRoot(){
        return root;
    }
};




