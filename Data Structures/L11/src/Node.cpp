#include "Node.h"
#include <stdlib.h>

Node::Node(int data)
{
    this->data=data;
    this->left=NULL;
    this->right=NULL;
}
void Node::set_data(int d){
    this->data=d;
}
char Node::get_data(){
    return this->data;
}
void Node::set_left(Node* l){
    this->left=l;
}
Node* Node::get_left(){
    return this->left;
}
void Node::set_right(Node* r){
    this->right=r;
}
Node* Node::get_right(){
    return this->right;
}