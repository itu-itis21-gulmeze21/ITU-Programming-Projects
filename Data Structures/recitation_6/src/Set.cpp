/* @Author
Student Name: Erce Gülmez
Student ID : 150210728
Date: 25/05/2022 */
#include <vector>
#include <bits/stdc++.h>
#include "Set.h"


vector<int> Set::get_intersection(BT* bt1, BT* bt2)
{
    vector<int> intersections;
    unordered_map<int,int> m;//defined an unordered map

    traverse(bt1->get_root(),m);//gets the datas from tree and puts them in a map
    traverse(bt2->get_root(),m);//gets the datas from tree and puts them in a map

    for(auto i : m){
        if(i.second==2){//if the value of a key(node datas are stored as keys) is 2, it means that it exist in both trees
            intersections.emplace_back(i.first);//put them in a vector
        }
    }

    return intersections;
    
}

vector<int> Set::get_union(BT* bt1, BT* bt2)
{
    vector<int> unions;
    unordered_map<int,int> m;//defined an unordered map

    traverse(bt1->get_root(),m);//gets the datas from tree and puts them in a map
    traverse(bt2->get_root(),m);//gets the datas from tree and puts them in a map
    
    for(auto i : m){
        unions.emplace_back(i.first);//since the map contains all the elements in both of the trees, without looking at their values we can add them to the union vector
    }

    return unions;
}

void Set::traverse(Node* root,unordered_map<int,int> &d){//a function that takes a node pointer and a reference to map object
    if(root!=NULL){//preorder traversal
        d[root->get_data()]++;//adds the data in the root as a key to the map
        this->traverse(root->get_left(),d);
        this->traverse(root->get_right(),d);
    }
    
}