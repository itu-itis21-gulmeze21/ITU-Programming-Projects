/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 28/03/2022 */

#include <iostream>
#include <string>
#include "MultiList.h"

using namespace std;

MultiList::MultiList()
{
    head=NULL;
    tail=NULL;
}

MultiList::~MultiList()
{
    DateNode* p1 = head;
    DateNode* n1 = head;
    TSiteNode* p2 = NULL;
    TSiteNode* n2 = NULL;

    while(n1!=NULL){
        n2 = n1->get_up();
        p2 = n2->get_up();
        while(n2!=NULL)
        {
            n2 = p2->get_up();
            delete p2;
            p2 = n2;
        }
        n1=p1->get_next();
        delete p1;
        p1=n1;
    }
}


void MultiList::add_node(string date,string time,string site_name)
{
    DateNode* prev_date=this->search_prev_date(date);//search for a spot 

    if(prev_date==NULL){//if the linkedList is empty
        DateNode* new_node=new DateNode(date);
        head=new_node;
        tail=new_node;
        TSiteNode* new_tsite= new TSiteNode(time,site_name);
        new_node->set_up(new_tsite);
    }
    else if(prev_date==head){//to add to the beginning
        if(prev_date->get_date().compare(date) == 0){//if that date already exists as a node in the linkedList
            TSiteNode* prev_tsite= this->search_prev_tsite(date,time);//search a spot fom the upper nodes
            if(prev_tsite==NULL){//if the desired spot is the beginning of the Tsite nodes(it works for both "no element" and "beginning of the list" cases) 
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                new_tsite->set_up(prev_date->get_up());
                prev_date->set_up(new_tsite);
            }
            else if (prev_tsite->get_up()==NULL){//if just 1 tsite node exists
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                prev_tsite->set_up(new_tsite);
            }
            else{//any other case
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                new_tsite->set_up(prev_tsite->get_up());
                prev_tsite->set_up(new_tsite);
            }
        }
        else{//if that date doesn't exist as a node in the linkedList
            DateNode* new_node=new DateNode(date);
            new_node->set_next(head);
            head->set_prev(new_node);
            head=new_node;
            TSiteNode* new_tsite= new TSiteNode(time,site_name);
            new_node->set_up(new_tsite);
        }
    }
    else if(prev_date==tail){//tail case is similar to the head case except updating the tail instead of the head if a new date node is added
        if(prev_date->get_date().compare(date)==0){
            TSiteNode* prev_tsite= this->search_prev_tsite(date,time);
            if(prev_tsite==NULL){
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                new_tsite->set_up(prev_date->get_up());
                prev_date->set_up(new_tsite);
            }
            else if (prev_tsite->get_up()==NULL){
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                prev_tsite->set_up(new_tsite);
            }
            else{
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                new_tsite->set_up(prev_tsite->get_up());
                prev_tsite->set_up(new_tsite);
            }
        }
        else{
            DateNode* new_node=new DateNode(date);
            new_node->set_prev(tail);
            tail->set_next(new_node);
            tail=new_node;
            TSiteNode* new_tsite= new TSiteNode(time,site_name);
            new_node->set_up(new_tsite);
        }
    }
    else{//the in between situation. similar to other cases
        if(prev_date->get_next()->get_date().compare(date)==0){
            TSiteNode* prev_tsite= this->search_prev_tsite(date,time);
            if(prev_tsite==NULL){
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                new_tsite->set_up(prev_date->get_next()->get_up());
                prev_date->get_next()->set_up(new_tsite);
            }
            else if (prev_tsite->get_up()==NULL){
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                prev_tsite->set_up(new_tsite);
            }
            else{
                TSiteNode* new_tsite= new TSiteNode(time,site_name);
                new_tsite->set_up(prev_tsite->get_up());
                prev_tsite->set_up(new_tsite);
            }
        }
        else{
            DateNode* new_node=new DateNode(date);
            new_node->set_next(prev_date->get_next());
            new_node->set_prev(prev_date);
            prev_date->set_next(new_node);
            new_node->get_next()->set_prev(new_node);
            TSiteNode* new_tsite= new TSiteNode(time,site_name);
            new_node->set_up(new_tsite);
        }
    }
}
    

void MultiList::remove_node(string date,string time)
{
    DateNode* prev_date=this->search_prev_date(date);

    if(prev_date==head && prev_date->get_date().compare(date)==0){//for the head node(removing from the second datenode is another case but in both cases, the search function returns head. so an additional condition is necessary;part after &&)
        TSiteNode* prev_tsite= this->search_prev_tsite(date,time);
        if(prev_tsite==NULL){
            TSiteNode* temp=prev_date->get_up();
            prev_date->set_up(temp->get_up());
            delete temp;
        }
        else if(prev_tsite->get_up()->get_up()==NULL){
            TSiteNode* temp=prev_tsite->get_up();
            prev_tsite->set_up(NULL);
            delete temp;
        }
        else{
            TSiteNode* temp=prev_tsite->get_up();
            prev_tsite->set_up(temp->get_up());
            delete temp;
        }
    }
    else{//for any other cases
        prev_date=prev_date->get_next();
        TSiteNode* prev_tsite= this->search_prev_tsite(date,time);
        if(prev_tsite==NULL){
            TSiteNode* temp=prev_date->get_up();
            prev_date->set_up(temp->get_up());
            delete temp;
        }
        else if(prev_tsite->get_up()->get_up()==NULL){
            TSiteNode* temp=prev_tsite->get_up();
            prev_tsite->set_up(NULL);
            delete temp;
        }
        else{
            TSiteNode* temp=prev_tsite->get_up();
            prev_tsite->set_up(temp->get_up());
            delete temp;
        }
    }
}

void MultiList::print_list()
{
    DateNode* p_hor=head;
    TSiteNode* p_ver;
    
    while(p_hor)
    {
        cout<<p_hor->get_date()<<":"<<endl;
        p_ver=p_hor->get_up();
        while(p_ver)
        {
            cout<<p_ver->get_time()<<"->"<<p_ver->get_site_name()<<endl;
            p_ver=p_ver->get_up();
        }
        p_hor=p_hor->get_next();
    }

}

DateNode* MultiList::search_prev_date(string d){
    DateNode* p=head;// to start with a pointer that points to the first element

    if(head==NULL){//if the linkedList is empty, the head is empty, so it will return NULL
        return NULL;
    }
    else if(head->get_date().compare(d)>=0){//if the desired place is the beginning of the linkedList, it returns head
        return head;
    }
    else{//for any other case
        while(p->get_next()){//while there is a next element
            if(p->get_next()->get_date().compare(d)>=0 ){//classic search function
                return p;
            }
            p=p->get_next();
        }
        return p;
    }
}

TSiteNode* MultiList::search_prev_tsite(string d,string t){//to search a spot for the given time 
    DateNode* ondate= this->search_prev_date(d);//the first thing is to find the date for that time
    if(ondate==head && ondate->get_next()==NULL){//if there is a single date, ondate pointer will be the head

    }
    else if(ondate==head && ondate->get_next()!=NULL){//if there are more than one dates and the desired date is the second node, this must be handled differently since the previous case's ondate is also the head
        if(ondate->get_date().compare(d)!=0){
            ondate=ondate->get_next();//update the ondate
        }
    } 
    else if(ondate!=head && ondate->get_next()!=NULL){//if the date is somewhere in between
        ondate=ondate->get_next();//since the searc function returns the previous date, we have to update ondate
    }
    else{//tail case is simple, no need for an update

    }
    TSiteNode* p = ondate->get_up();//p pointer points to the first TsiteNode of the desired date
    if(p==NULL){//just date exists, no upper nodes(this happens when every TsiteNode is removed from that date)
        return NULL;
    }
    if(p->get_time().compare(t)>=0){//if the desired spot is first place 
        return NULL;
    }
    else{//simple searching algorithm
        while(p->get_up()){
            if(p->get_up()->get_time().compare(t)>=0){
                return p;
            }
            p=p->get_up();
        }
        return p;
    }
}
