#include <iostream>
#include <stdio.h>
#pragma once
using namespace std;


class Node{
    private:
        int burstTime;
        Node* left;
        Node* right;
        Node* parent;
        string color;
        string name;
        bool isCompleted;
    public://simple getters and setters
        int arrivalTime;
        int vtime;
        Node(int,string,int);
        void set_burstTime(int);
        int get_burstTime();
        void set_left(Node*);
        Node* get_left();
        void set_right(Node*);
        Node* get_right();
        void set_parent(Node*);
        Node* get_parent();
        string get_color();
        void set_color(string);
        void set_name(string);
        string get_name();
        void set_completed();
        void printNode();
};

