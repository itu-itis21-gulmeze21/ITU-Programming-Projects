/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 28/03/2022 */

#pragma once
#include "MultiNode.h"
#include <string>

using namespace std;

class MultiList{
    private:
        DateNode* head;
        DateNode* tail;

    public:
        MultiList();
        ~MultiList();
        void add_node(string,string,string);
        void remove_node(string,string);
        void print_list();
        DateNode* search_prev_date(string);//a function to search for the desired place in the linkedList's dates
        TSiteNode* search_prev_tsite(string,string);//a function to search for the desired place in the linkedList's Tsites
        //You can add any function.

};