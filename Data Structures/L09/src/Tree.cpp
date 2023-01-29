#include "Tree.h"
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;

Tree::Tree()
{
    this->root=NULL;
}
void Tree::preorder_traverse(TreeNode* n){
    if(n!=NULL){
        cout<<n->get_data();
        this->preorder_traverse(n->get_left());
        this->preorder_traverse(n->get_right());
    }
}
void Tree::inorder_traverse(TreeNode* n){
    if(n!=NULL){
        this->preorder_traverse(n->get_left());
        cout<<n->get_data();
        this->preorder_traverse(n->get_right());
    }
}
void Tree::postorder_traverse(TreeNode* n){
    if(n!=NULL){
        this->preorder_traverse(n->get_left());
        this->preorder_traverse(n->get_right());
        cout<<n->get_data();
    }
}
void Tree::printPreOrder(){
    this->preorder_traverse(this->root);
    cout<<endl;
}
void Tree::printInOrder(){
    this->inorder_traverse(this->root);
    cout<<endl;
}
void Tree::printPostOrder(){
    this->postorder_traverse(this->root);
    cout<<endl;
}
void Tree::printBreadthFirst(){
    TreeNode* temp;
    queue<TreeNode*> q;
    q.push(this->root);
    while(!q.empty()){
        temp=q.front();
        q.pop();
        cout<<temp->get_data();
        if(temp->get_left()!=NULL){
            q.push(temp->get_left());
        }
        if(temp->get_right()!=NULL){
            q.push(temp->get_right());
        }
    }
}