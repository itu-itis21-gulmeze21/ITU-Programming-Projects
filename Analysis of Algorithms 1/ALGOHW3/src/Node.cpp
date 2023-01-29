#include "Node.h"
#include <stdlib.h>

Node::Node(int burstTime,string name, int time)
{
    this->burstTime = burstTime;
    this->color = "Red";
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->name = name;
    this->isCompleted = false;
    this->arrivalTime = time;
    this->vtime = 0;
}

void Node::set_burstTime(int burstTime)
{
    this->burstTime = burstTime;
}

int Node::get_burstTime()
{
    return this->burstTime;
}

void Node::set_left(Node* node)
{
    this->left = node;
}

Node* Node::get_left()
{
    return this->left;
}

void Node::set_right(Node* node)
{
    this->right = node;
}

Node* Node::get_right()
{
    return this->right;
}

void Node::set_parent(Node* node)
{
    this->parent = node;
}

Node* Node::get_parent()
{
    return this->parent;
}

string Node::get_color(){
    return color;
}

void Node::set_color(string c){
    color = c;
}

string Node::get_name(){
    return name;
}

void Node::set_name(string n){
    name = n;
}

void Node::set_completed(){
    isCompleted = true;
}

void Node::printNode(){
    cout<<name<<" "<<arrivalTime<<" "<<burstTime<<endl;
}