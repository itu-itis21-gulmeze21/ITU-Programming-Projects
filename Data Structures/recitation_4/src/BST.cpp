/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 22/04/2022 */

#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include "BST.h"

using namespace std;

BST::BST()
{
    root=NULL;
}

BST::~BST()//destructor using postorder_destruct function to destruct all the nodes starting from the root
{
    if(root!=NULL){
        this->postorder_destruct(this->root);
        root=NULL;
    } 

}

Node* BST::get_root()
{
    return this->root;
}

void BST::add(int data)
{
    if(this->contains(data)){//if this data already exists in the tree, do not add
        return;
    } 
    Node* newNode = new Node(data);//node that will be added
    if(this->root==NULL){//empty tree case
        root=newNode;
        cout<<"Adding "<<data<<endl;
        return;
    }
    else{
        Node* temp=root;//parent of the node that will be added
        while (temp!=NULL)
        {
            if(temp->get_data()>data){
                if(temp->get_left()==NULL){//check if the space is empty
                    temp->set_left(newNode);//add the node
                    cout<<"Adding "<<data<<endl;
                    return;
                }
                temp=temp->get_left();
            }
            else if(temp->get_data()<data){//same logic with the upper one
                if(temp->get_right()==NULL){
                    temp->set_right(newNode);
                    cout<<"Adding "<<data<<endl;
                    return;
                }
                temp=temp->get_right();
            }
        }
        
    }

}

void BST::corrupted_add(vector<int> data)
{
    queue<Node*> q;
    Node* temp;
    int turn = 0;    // Suggests the left turn
    while (!data.empty()){
        int num = data.back();
        data.pop_back();

        if (num == INT32_MIN){
            q.pop();
            continue;
        }

        Node* n = new Node(num);

        if (root == nullptr){
            root = n;
            q.push(root);
            q.push(root);
        }
        else{
            temp = q.front();
            q.pop();
            if(turn == 0){
                temp->set_left(n);
                turn = 1;
            }
            else if(turn == 1){
                temp->set_right(n);
                turn = 0;
            }
            q.push(n);
            q.push(n);
        }
    }
}

bool BST::contains(int data)
{
    if(this->root==NULL){//empty tree case
        return false;
    }

    Node* temp=root;
    while(temp!=NULL){
        if(temp->get_data()>data){
            temp=temp->get_left();
        }
        else if(temp->get_data()<data){
            temp=temp->get_right();
        }
        else{//data is equal to temp's data, so this tree contains this data
            return true;
        }
    }
    return false;

}

void BST::postorder_traverse(Node* n)//basic postorder algorithm
{
    if(n!=NULL){
        this->postorder_traverse(n->get_left());
        this->postorder_traverse(n->get_right());
        cout<<n->get_data()<<" ";
    } 

}

void BST::postorder_destruct(Node* n)//basic postorder algorithm
{
     if(n!=NULL){
        this->postorder_destruct(n->get_left());
        this->postorder_destruct(n->get_right());
        delete n;
    }

}

void BST::printPostOrder()//basic print function that uses postorder_traverse
{
    cout<<"Printing the tree with postorder traversal"<<endl;
    this->postorder_traverse(this->root);
    cout << endl;
}

int BST::maxSumBST(Node* node){
    // Find the sum of the Binary Search Tree with the maximum sum within the Binary Tree
    int sum = 0;
    int maxsum = 0;

    if(node!=NULL){
        if(this->isBST(node)){
            sum=this->findSum(node);
            if(sum>maxsum){
                maxsum=sum;
            }
        }
        int left=maxSumBST(node->get_left());
        if(left>maxsum){
            maxsum=left;
        }
        int right=maxSumBST(node->get_right());
        if(right>maxsum){
            maxsum=right;
        }
    }

    return maxsum;

}

int BST::findSum(Node* n){
    if(n==NULL){
        return 0;
    }
    return n->get_data() + findSum(n->get_left()) + findSum(n->get_right());
}

bool BST::isBST(Node* n){
    if(n==NULL){
        return true;
    }
    if(n->get_left()==NULL && n->get_right()!=NULL){
        return n->get_data()<n->get_right()->get_data() && isBST(n->get_right());
    }
    else if(n->get_left()!=NULL && n->get_right()==NULL){
        return n->get_data()<n->get_left()->get_data() && isBST(n->get_left());
    }
    else if(n->get_left()==NULL && n->get_right()==NULL){
        return true;
    }
    return n->get_data()>n->get_left()->get_data() && n->get_data()<n->get_right()->get_data() && isBST(n->get_left()) && isBST(n->get_right());
    
}

