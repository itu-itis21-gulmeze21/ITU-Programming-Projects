#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "passenger.h"

using namespace std;

class Pqueue{//priority queue implementation using max heap(most prioritized passenger will be on the top)
private:
    vector<passenger> passengers;
public:
    Pqueue();
    void insert(passenger);
    void pop();
    passenger top();
    int getSize();
    bool isEmpty();
};