/* @Author
Student Name: Erce Gülmez
Student ID : 150210728
Date: 10/05/2022 */
#include "Node.h"
#include <stdlib.h>


Node::Node(int data){
    this->data = data;
    this->left=NULL;
    this->right=NULL;
}


void Node::set_left(Node* left){
    this->left = left;
}

void Node::set_right(Node* right){
    this->right = right;
}

void Node::set_data(int data){
    this->data =data;
}

Node* Node::get_left(){
    return this->left;
}
Node* Node::get_right(){
    return this->right;
}

Node** Node::get_left_addr(){
    return &(this->left);
}
Node** Node::get_right_addr(){
    return &(this->right);
}
int Node::get_data(){
    return this->data;
}