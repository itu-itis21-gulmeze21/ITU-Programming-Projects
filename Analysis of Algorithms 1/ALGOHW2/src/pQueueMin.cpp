#include "pQueueMin.h"
#include <iostream>
#include <cmath>
//the algorithms are explained in the report.
pQueueMin::pQueueMin(){}

int pQueueMin::parent(int i){
    return floor(i/2);
}
int pQueueMin::leftChild(int i){
    return 2*i + 1;
}
int pQueueMin::rightChild(int i){
    return 2*i +2;
}
void pQueueMin::minHeapify(float i){
    int l = leftChild(i);
    int r = rightChild(i);
    int smallest = i;
    if(l<=int(array.size())-1 && array[l]<array[i]){
        smallest=l;
    } 
    if(r<=int(array.size())-1 && array[r]<array[smallest]){
        smallest=r;
    }
    if(smallest != i){
        swap(array[i],array[smallest]);
        minHeapify(smallest);
    }
}

void pQueueMin::insert(float p){
    if (this->isEmpty()){//if the queue is empty, simply add the number to the queue without checking if the structure is affected or not
        array.emplace_back(p);
    }
    else{
        array.emplace_back(p);
        int pIndex=array.size() - 1;//index of the newly added item
        while(pIndex!=0){//until this item becomes the root
            if(array[pIndex]<array[(pIndex-1)/2]){//check if it is bigger(prioritized) than its parent
                swap(array[pIndex],array[(pIndex-1)/2]);//if it is bigger, simply swap them
                pIndex=(pIndex-1)/2;//update the newly added items index for further parent-child checks
            }
            else{//if it is smaller than its parent, break the loop since the structure is correct, no more swapping is needed
                break;
            }
        }
    }
}
float pQueueMin::extractMin(){
    float min = array[0];
    array[0] = array[array.size()-1];
    array.pop_back();
    this->minHeapify(0);
    return min;
}
float pQueueMin::min(){
    return array[0];
}
float pQueueMin::getSize(){
    return array.size();
}
float pQueueMin::mean(){
    float total=0;
    for(long unsigned int i=0;i<array.size();i++){
        total+=array[i];
    }
    return total/array.size();
}
float pQueueMin::standardDeviation(){
    float distances=0;
    float mean = this->mean();
    for(long unsigned int i=0;i<array.size();i++){
        distances+=pow((array[i]-mean),2);
    }
    return sqrt(distances/array.size());
}
bool pQueueMin::isEmpty(){
    return array.empty();
}

vector<float> pQueueMin::getVector(){
    return array;
}

void pQueueMin::print(){
    for(auto i:array){
        cout<<i<<" ";
    }
}