/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 24/03/2022 */

#include "trackLinkedList.h"
#include <stdio.h>
#include <iostream>
using namespace std;


TrackLinkedList::TrackLinkedList()//simply creating an empty list with null head and tail
{
    head=NULL;
    tail=NULL;
}

TrackLinkedList::~TrackLinkedList()//breaking the circularity by setting head's prev and tail's next to null and starting the deletion chain by deleting the head
{
    head->set_prev(NULL);
    tail->set_next(NULL);
    delete head;
    
}

void TrackLinkedList::print_list(bool isReverse)
{
    TrackNode* p;
    TrackNode* target;
    if (isReverse){
        p = this->tail;
        target = this->head;
    }
    else{
        p = this->head;
        target = this->tail;
    }
    
    if (p == NULL)
        return;

    int d = 0;
    while (p->step_node(isReverse) != target->step_node(isReverse)){
        cout << "----------------------" << d << "----------------------" << endl;
        p->get_node_info();
        p = p->step_node(isReverse);
        d++;
    }
    cout << "----------------------" << d << "----------------------" << endl;
    p->get_node_info();
}

TrackNode* TrackLinkedList::search(int view)
{
    TrackNode* p=head;
    if(head==NULL){//if the list is empty,return null
        return NULL;
    }
    else if(view>=head->get_views()){//return null if the desired spot is the beginning of the list
        return NULL;
    }
    else{
        while (p->get_next()!=head)//loop that goes until the last element since the last element's next is head again
        {
            if(view>=p->get_next()->get_views()){//finding the desired spot
                return p;
            }
            p=p->get_next();
        }
        return p;
    }

}

void TrackLinkedList::add_node(TrackNode* node)
{
    if(head==NULL){//the empty list situation
        head=node;
        tail=node;
        node->set_next(head);
        node->set_prev(tail);
    }
    else{
        TrackNode* p= this->search(node->get_views());
        if(p==NULL){//the beginning of the list situation
            node->set_next(head);
            node->set_prev(tail);
            head->set_prev(node);
            tail->set_next(node);
            head=node;
        }
        else{//any other situation
            node->set_next(p->get_next());
            node->set_prev(p);
            node->get_next()->set_prev(node);
            p->set_next(node);
            if(node->get_next()==head){//extra check for the last element since updating the tail is necessary
                tail=node;
            }
        }
    }

}

void TrackLinkedList::reduce_duplicates()
{
    TrackNode* p=head;
    if(head!=NULL){//preventing the empty list situation
        while (p->get_next()!=head)//loop that goes until the last element
        {
            int total_views=p->get_views();//integer to keep track of the total views 
            TrackNode* duplicate=p->get_next();//a pointer to go through the list
            TrackNode* nextdup=NULL;//extra pointer for more than one duplicate situations  
            while (duplicate!=head)//executes until the pointer that goes through the list reaches the head 
            {
                if(p->get_kwd().compare(duplicate->get_kwd())==0){//kwd comparison
                    total_views+=duplicate->get_views();//updating the views
                    duplicate->get_prev()->set_next(duplicate->get_next());
                    duplicate->get_next()->set_prev(duplicate->get_prev());
                    nextdup=duplicate->get_next();//storing the next node with nextdup since duplicate's next will be set to null below
                    if(duplicate==tail){
                        tail=duplicate->get_prev();
                    }
                    duplicate->set_next(NULL);
                    duplicate->set_prev(NULL);
                    delete duplicate;//removing the node
                    duplicate=nextdup;//updating the duplicate pointer
                }
                else{
                    duplicate=duplicate->get_next();//going to the next node if there is no kwd match
                }
                
            }
            p->set_views(total_views);//updating the views of p
            p=p->get_next();//same check for the next node
        }
    }
}

KwdLinkedList::KwdLinkedList()
{
    head=NULL;
    tail=NULL;

}

KwdLinkedList::~KwdLinkedList()
{
    if(head!=NULL){
        delete head;
    }
}

KwdNode* KwdLinkedList::search(string kwd)
{
    KwdNode* p=head;
    if (head==NULL){//no elements existing
        return NULL;
    }
    else if(head->get_next()==NULL){//just one element exists
        if(head->get_keyword()==kwd){
            return head;
        }
        return NULL;
    }
    else{//more than one elements exist
        while(p->get_next()){//loops until the last element check
            if(p->get_next()->get_keyword()==kwd){
                return p->get_next();
            }
            p=p->get_next();
        }
        return NULL;
    }

}

void KwdLinkedList::add_node(string kwd)
{
    //     ___     ___      _        _     
    //    | __|   |_ _|    | |      | |    
    //    | _|     | |     | |__    | |__  
    //   _|_|_    |___|    |____|   |____| 
    // _| """ | _|"""""| _|"""""| _|"""""| 
    // "`-0-0-' "`-0-0-' "`-0-0-' "`-0-0-' 

}

bool KwdLinkedList::contains(string kwd)
{
    bool flag=false;
    KwdNode* p=head;
    if (head==NULL){//no elements existing
        return flag;
    }
    else if(head->get_next()==NULL){//just one element exists
        if(head->get_keyword()==kwd){
            flag= true;
        }
        return flag;
    }
    else{//more than one elements exist
        while(p->get_next()){//loops until the last element check
            if(p->get_next()->get_keyword()==kwd){
                flag= true;
                return flag;
            }
            p=p->get_next();
        }
        return flag;
    } 

}