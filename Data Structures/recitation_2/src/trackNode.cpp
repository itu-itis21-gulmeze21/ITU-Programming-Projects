/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 24/03/2022 */

#include "trackNode.h"
#include <stdio.h>
#include <iostream>
using namespace std;


TrackNode::TrackNode(int views, string name, string artist_name, string kwd, string url)//simple constructor
{
    this->views=views;
    this->name=name;
    this->artist_name=artist_name;
    this->kwd=kwd;
    this->url=url;
    prev=NULL;
    next=NULL;

}

TrackNode::~TrackNode()
{   
    if(this->next!=NULL){//deletes the node if its next is not null. tail's next is set to null in the linkedlist destructor, so it will stop there
        delete this->next;
    }
    
}

void TrackNode::set_name(string s)
{
    this->name = s;
}

void TrackNode::set_views(int views)
{
    this->views = views;
}

string TrackNode::get_name()
{
    return this->name;
}

string TrackNode::get_artist_name()
{
    return this->artist_name;
}

string TrackNode::get_kwd()
{
    return this->kwd;
}

void TrackNode::set_kwd(string kwd){
    this->kwd = kwd;
}

int TrackNode::get_views()
{
    return this->views;
}

TrackNode* TrackNode::get_next()
{
    return this->next;
}

TrackNode* TrackNode::get_prev()
{
    return this->prev;
}

TrackNode* TrackNode::step_node(bool isReverse)
{
    if (isReverse)
        return this->get_prev();
    else
        return this->get_next();
}

void TrackNode::set_next(TrackNode* node)
{
    this->next = node;
}

void TrackNode::set_prev(TrackNode* node)
{
    this->prev = node;
}

void TrackNode::get_node_info()
{
    cout << this->artist_name << " - " << this->name << endl;
    cout << "Views: " << this->views << ", Keyword: " << this->kwd << endl;
    cout << "URL: " << this->url << endl;
}

KwdNode::KwdNode(string kwd)
{
    this->kwd=kwd;
    next=NULL;

}

KwdNode::~KwdNode()
{
    delete this->get_next(); 

}

string KwdNode::get_keyword()
{
    return this->kwd;
}

void KwdNode::set_keyword(string kwd)
{
    this->kwd = kwd;
}

KwdNode* KwdNode::get_next()
{
    return this->next;
}

void KwdNode::set_next(KwdNode* node)
{
    this->next = node;
}

int KwdNode::get_count()
{
    return this->count;
}

void KwdNode::update_count(int count)
{
    this->count += count;
}