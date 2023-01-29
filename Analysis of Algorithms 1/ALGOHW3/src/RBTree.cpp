#include "RBTree.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

RBTree::RBTree(){
    
    NIL = new Node(0,"NIL",0);//create the NIL
    NIL->set_color("black");
    root = NIL;

}

Node* RBTree::get_root()
{
    return this->root;
}

void RBTree::set_root(Node* n){
    root = n;
}

bool RBTree::isEmpty(){
    if(root == NIL){
        return true;
    }
    return false;
}

int RBTree::findMinvruntime(){//find the min vruntime by looking at the leftmost childs vruntime
    Node* temp = root;
    while(temp->get_left()->get_left() != nullptr){
        temp = temp->get_left();
    }
    return temp->vtime;
}

void RBTree::inorder_traverse(Node* n, ofstream &output){//simple inorder traverse algorithm but it prints the nodes to the outputfile
    Node* rightMost = root;
    while(rightMost->get_right()->get_right() != nullptr){
        rightMost = rightMost->get_right();
    }
    if(n!=NULL){
        this->inorder_traverse(n->get_left(),output);
        if(n->get_name() != "NIL"){
            if(n == rightMost){
                output<<n->get_name()<<":"<<n->vtime<<"-"<<n->get_color();
            }
            else{
                output<<n->get_name()<<":"<<n->vtime<<"-"<<n->get_color()<<";";
            }
        }
        this->inorder_traverse(n->get_right(),output);
    } 
}

void RBTree::right_rotate(Node* n){
    Node* p = n->get_left();
    if(n->get_parent() != nullptr){//if n has a parent
        if(n == n->get_parent()->get_right()){//if n is the right child of its parent
            p->set_parent(n->get_parent());
            n->get_parent()->set_right(p);
            n->set_left(p->get_right());
            p->set_right(n);
            n->set_parent(p);
            n->get_left()->set_parent(n);
            
            
        }
        else{//if n is the left child of its parent
            p->set_parent(n->get_parent());
            n->get_parent()->set_left(p);
            n->set_left(p->get_right());
            p->set_right(n);
            n->set_parent(p);
            n->get_left()->set_parent(n);
            
        }
    }
    else{//if n is the root
        n->set_left(p->get_right());
        p->set_right(n);
        n->set_parent(p);
        n->get_left()->set_parent(n);
        this->set_root(p);
        p->set_parent(nullptr);
    }
    
}

void RBTree::left_rotate(Node* n){
    Node* p = n->get_right();
    n->set_right(p->get_left());//connect the left child of n's rightchild and n
    p->get_left()->set_parent(n);
    p->set_left(n);
    if(n->get_parent() != nullptr){//if n is an internal node
        p->set_parent(n->get_parent());//connection between its parent and its right child
        if(p->get_parent()->get_left() == n){
            p->get_parent()->set_left(p);
        }
        else{
            p->get_parent()->set_right(p);
        }

    }
    else{//if n is the root
        this->set_root(p);
        p->set_parent(nullptr);
    }
    n->set_parent(p);
}

void RBTree::insert_fixup(Node* n){//maintain the rbtree properties after insertion
    if(n != this->get_root()){
        while(n->get_parent()->get_color() == "Red"){
            if(n->get_parent() == n->get_parent()->get_parent()->get_left()){//if n's parent is the left child of n's grandparent
                Node* p = n->get_parent()->get_parent()->get_right();
                if(p->get_color() == "Red"){//if the inserted node's uncle is red
                    n->get_parent()->set_color("Black");
                    p->set_color("Black");
                    n->get_parent()->get_parent()->set_color("Red");
                    n = n->get_parent()->get_parent();
                }
                else{
                    if(n == n->get_parent()->get_right()){//if n's uncle is black and n is the right child of its parent
                        n = n->get_parent();
                        left_rotate(n);
                    }
                    //if n's uncle is black and n is the left child of its parent
                    n->get_parent()->set_color("Black");
                    n->get_parent()->get_parent()->set_color("Red");
                    right_rotate(n->get_parent()->get_parent());
                }
            }
            else{//if n's parent is the left child of n's grandparent, same process with the upper algorithm except the lefts are changes to right
                Node* p = n->get_parent()->get_parent()->get_left();
                if(p->get_color() == "Red"){
                    n->get_parent()->set_color("Black");
                    p->set_color("Black");
                    n->get_parent()->get_parent()->set_color("Red");
                    n = n->get_parent()->get_parent();
                }
                else{
                    if(n == n->get_parent()->get_left()){
                        n = n->get_parent();
                        right_rotate(n);
                    }
                    n->get_parent()->set_color("Black");
                    n->get_parent()->get_parent()->set_color("Red");
                    left_rotate(n->get_parent()->get_parent());
                }
                
            }
            if(n == root){//if n is the root do nothing
                break;
            }   
        }
    }
    root->set_color("Black");//maintain the color of the root property
}

void RBTree::insert_node(Node* n){
    n->set_left(NIL);//set n's childern to NIL
    n->set_right(NIL);

    Node* y = nullptr;
    Node* x = this->get_root();
    while (x != NIL)//find the place to insert(BST properties)
    {
        y=x;
        if(n->vtime < x->vtime){
            x = x->get_left();
        }
        else{
            x = x->get_right();
        }
    }
    n->set_parent(y);
    if( y == nullptr){//root
        this->set_root(n);
    }
    else if(n->vtime < y->vtime){
        y->set_left(n);
    }
    else{
        y->set_right(n);
    }
    n->set_color("Red");//new inserted node must be red
    this->insert_fixup(n);//maintain the properties
}

void RBTree::transplant(Node* n, Node* p) {//transplant function for deletion
    if (n->get_parent() == nullptr) {//if n is the current root
        root = p;
    } 
    else if (n == n->get_parent()->get_left()) {//if n is the left child of its parent
      n->get_parent()->set_left(p);
    } 
    else {//if n is the right child of its parent
      n->get_parent()->set_right(p);
    }
    p->set_parent(n->get_parent());
}

void RBTree::delete_fixup(Node* n){
    
    Node* p = nullptr;
    while(n != root && n->get_color()=="Black"){
        if(n->get_parent()->get_left() == n){
            p = n->get_parent()->get_right();
            if(p->get_color()=="Red"){//if n's sibling is red
                p->set_color("Black");
                n->get_parent()->set_color("Red");
                this->left_rotate(n->get_parent());
                p = n->get_parent()->get_right();
            }
            if(p->get_left()->get_color()=="Black" && p->get_right()->get_color()=="Black"){//if n's sibling and its children are black
                p->set_color("Red");
                n = n->get_parent();
            }
            else if(p->get_right()->get_color()=="Black"){//if n's sibling and its right child is black but its left child is red
                p->get_left()->set_color("Black");
                p->set_color("Red");
                this->right_rotate(p);
                p = n->get_parent()->get_right();
            }
            else{//if n's sibling is black but its children are red
                p->set_color(n->get_parent()->get_color());
                n->get_parent()->get_parent()->set_color("Black");
                p->get_right()->set_color("Black");
                this->left_rotate(n->get_parent());
                root=n;
            }

        }
        else{//same procedure when n is the right child of its parent
            p = n->get_parent()->get_left();
            if(p->get_color()=="Red"){
                p->set_color("Black");
                n->get_parent()->set_color("Red");
                this->right_rotate(n->get_parent());
                p = n->get_parent()->get_left();
            }
            if(p->get_right()->get_color()=="Black" && p->get_left()->get_color()=="Black"){
                p->set_color("Red");
                n = n->get_parent();
            }
            else if(p->get_left()->get_color()=="Black"){
                p->get_right()->set_color("Black");
                p->set_color("Red");
                this->left_rotate(p);
                p = n->get_parent()->get_left();
            }
            else{
                p->set_color(n->get_parent()->get_color());
                n->get_parent()->get_parent()->set_color("Black");
                p->get_left()->set_color("Black");
                this->right_rotate(n->get_parent());
                root=n;
            }

        }
    }
    n->set_color("Black");
}

void RBTree::delete_node(Node* n){ 
    Node* p = nullptr;
    string colorOfDeleted = n->get_color();//store the color of the node to be deleted
    if(n->get_left() == NIL){//if the node to be deleted has no left child
        p = n->get_right();
        this->transplant(n,p);
    }
    else if(n->get_right() == NIL){//if the node to be deleted has no right child
        p = n->get_left();
        this->transplant(n,p);
    }
    else{//if the node to be deleted has both left and right child
        Node* temp = n->get_right();//find the smallest element of n's right subtree(the BST procedure)
        while(temp->get_left() != NIL){
            temp = temp->get_left();
        }
        colorOfDeleted = temp->get_color();
        p = temp->get_right();
        if(temp->get_parent() == n){
            n->set_parent(temp);
        }
        else{
            this->transplant(temp,temp->get_right());
        }
        this->transplant(n,temp);
        temp->set_color(colorOfDeleted);
    }
    if(colorOfDeleted=="Black"){
        this->delete_fixup(p);
    }
    
}
