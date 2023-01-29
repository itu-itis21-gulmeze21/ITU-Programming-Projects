
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

class pQueueMin{//priority queue implementation using min heap
private:
    vector<float> array;
public:
    int parent(int);
    int leftChild(int);
    int rightChild(int);
    pQueueMin();
    void minHeapify(float);
    void insert(float);
    float extractMin();
    float min();
    float getSize();
    float mean();
    float standardDeviation();
    bool isEmpty();
    vector<float> getVector();
    void print();
};