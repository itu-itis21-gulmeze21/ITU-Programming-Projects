#include <iostream>
#include <stdio.h>
#include "BSTtree.h"

using namespace std;

int main(int argc,char *argv[]){

    BSTtree* t = new BSTtree();

    t->add(5);
    t->add(8);
    t->add(3);
    t->add(9);
    t->add(2);

    cout<<t->sumOfTree(t->getRoot());

    return EXIT_SUCCESS;
}