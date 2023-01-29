#include "BSTtree.h"
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

BSTtree::BSTtree()
{
    root=NULL;
}

void BSTtree::remove(int data){
    if(this->root==NULL || !this->contains(data)){
        return;
    }
    Node* child;
    Node* par=find_par(data, &child);
    
    child=child->get_left();
}
Node* BSTtree::find_par(int data,Node** child){
    if(this->root->get_data()==data){
        return NULL;
    }
    Node* temp=root;
    while (temp!=NULL)
    {
        if(temp->get_left()->get_data()==data ){
            *child = temp->get_left();
            return temp;
        }
        if(temp->get_right()->get_data()==data){
            *child = temp->get_right();
            return temp;
        }
        if(temp->get_data()>data){
            temp=temp->get_left();
        }
        else if(temp->get_data()<data){
            temp=temp->get_right();
        }
        else{
            return NULL;
        }
    }
    return NULL;
}
void BSTtree::add(int data){
    Node* n=new Node(data);
    if(root==NULL){
        root=n;
        return;
    }
    Node* temp=root;
    while (temp!=NULL)
    {
        if(temp->get_data()>data){
            if(temp->get_left()==NULL){
                temp->set_left(n);
                return;
            }
            temp=temp->get_left();
        }
        else if(temp->get_data()<data){
            if(temp->get_right()==NULL){
                temp->set_right(n);
                return;
            }
            temp=temp->get_right();
        }
        else{
            delete n;
            return;
        }
    }
    
}
bool BSTtree::contains(int data){
    if(root==NULL){
        return false;
    }
    Node* temp=root;
    while (temp!=NULL)
    {
        if(temp->get_data()>data){
            temp=temp->get_left();
        }
        else if(temp->get_data()<data){
            temp=temp->get_right();
        }
        else{
            return true;
        }
    }
    return false;
}
BSTtree::~BSTtree(){
    if(this->root != NULL)
        this->postorder_destruct(this->root);
    this->root=NULL;
}

void BSTtree::postorder_destruct(Node* n){
    if(n!=NULL){
        this->postorder_destruct(n->get_left());
        this->postorder_destruct(n->get_right());
        delete n;
    }
}

void BSTtree::preorder_traverse(Node* n){

    if(n!=NULL){
        cout<<n->get_data()<<" ";
        this->preorder_traverse(n->get_left());
        this->preorder_traverse(n->get_right());
    }

}

void BSTtree::inorder_traverse(Node* n){

    if(n!=NULL){
        this->inorder_traverse(n->get_left());
        cout<<n->get_data()<<" ";
        this->inorder_traverse(n->get_right());
    }

}

void BSTtree::postorder_traverse(Node* n){

    if(n!=NULL){
        this->postorder_traverse(n->get_left());
        this->postorder_traverse(n->get_right());
        cout<<n->get_data()<<" ";
    }

}

void BSTtree::printPreOrder(){
    this->preorder_traverse(this->root);
    cout<<endl;
}

void BSTtree::printInOrder(){
    this->inorder_traverse(this->root);
    cout<<endl;
}

void BSTtree::printPostOrder(){
    this->postorder_traverse(this->root);
    cout<<endl;
}


void BSTtree::printBreadthFirst(){
    Node* temp;
    queue<Node*> q;
    if(this->root == NULL)
        return;

    q.push(this->root);

    while(!q.empty()){
        temp = q.front();
        q.pop();
        cout<<temp->get_data()<<" ";
        if(temp->get_left()!=NULL)
            q.push(temp->get_left());

        if(temp->get_right()!=NULL)
            q.push(temp->get_right());
    }

    cout<<endl;
}
int BSTtree::sumOfTree(Node* n){
    if(n==NULL){
        return 0;
    }
    return n->get_data() + sumOfTree(n->get_left()) + sumOfTree(n->get_right());
}