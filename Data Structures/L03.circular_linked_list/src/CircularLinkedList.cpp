#include "CircularLinkedList.h"
#include <cstdlib>
#include <iostream>

CircularLinkedList::CircularLinkedList(){
    head=new DoubleNode(-1,true);
    tail=head;
}

CircularLinkedList::~CircularLinkedList(){
    DoubleNode* p=head;
    DoubleNode* n= head;
    
    while (n!=NULL)
    {
        n=p->get_next();
        delete p;
        p=n;
    }
}

DoubleNode* CircularLinkedList::contains(int data){
    DoubleNode* p=head->get_next();
    while(p!=NULL && p->get_data()!= data){
        p=p->get_next();
    }
    return p;
}

void CircularLinkedList::clear_list(){
    DoubleNode* p=head->get_next();
    DoubleNode* n= head->get_next();
    
    while (n!=NULL)
    {
        n=p->get_next();
        delete p;
        p=n;
    }
    head->set_next(NULL);
    tail=head;  
}

DoubleNode* CircularLinkedList::search_prev(int data){
    DoubleNode* p=head->get_next();

    if(p==NULL || data<=p->get_data()){
        return head;
    }
    else{
        while (p->get_next())
        {
            if(p->get_next()->get_data()>=data){
                return p;
            }
            p=p->get_next();
        }
        return p;
    }
}

void CircularLinkedList::add_node(int n){
    DoubleNode* new_node= new DoubleNode(n, false);
    
    
    DoubleNode* prev= this->search_prev(n);
    if(prev->get_next()==NULL){
        tail->set_next(new_node);
        new_node->set_prev(tail);
        tail=new_node;
    }
    else{
        new_node->set_prev(prev);
        new_node->set_next(prev->get_next());
        prev->set_next(new_node);
        new_node->get_next()->set_prev(new_node);
    }
    
}
void CircularLinkedList::remove_node(int n){
    DoubleNode* rem_node= this->contains(n);
    if(n==NULL){
        std::cout<<"Element not found"<<std::endl;
        return;
    }
    
    DoubleNode* prev=rem_node->get_prev();

    if(head==tail){
        delete head;
        head=NULL;
        tail=NULL;
    }
    else{
        if(rem_node==head){
            DoubleNode* old_head=head;
            head=head->get_next();
            delete old_head;
            head->set_prev(NULL);
        }
        else if(rem_node==tail){
            tail=prev;
            delete rem_node;
            tail->set_next(NULL);
        }
        else{
            prev->set_next(rem_node->get_next());
            rem_node->get_next()->set_prev(prev);
            delete rem_node;
        }
    }
}

void CircularLinkedList::print_list(){
    DoubleNode* p=head->get_next();

    while (p!=NULL)
    {
        std::cout<<p->get_data()<<std::endl;
        p=p->get_next();
    }
    if(p!=NULL){
        std::cout<<p->get_data()<<std::endl;
    }
    
}
void CircularLinkedList::reverse_print_list(){
    DoubleNode* p=tail;

    while (!p->get_prev()->is_sentinel())
    {
        std::cout<<p->get_data()<<std::endl;
        p=p->get_prev();
    }
    if(!p->is_sentinel()){
        std::cout<<p->get_data()<<std::endl;
    }
}