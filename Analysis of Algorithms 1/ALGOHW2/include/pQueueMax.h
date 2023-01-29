
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

class pQueueMax{//priority queue implementation using max heap
private:
    vector<float> array;
public:
    float parent(float);
    float leftChild(float);
    float rightChild(float);
    pQueueMax();
    void maxHeapify(float);
    void insert(float);
    float extractMax();
    float max();
    float getSize();
    float mean();
    float standardDeviation();
    bool isEmpty();
    vector<float> getVector();
    void print();
};