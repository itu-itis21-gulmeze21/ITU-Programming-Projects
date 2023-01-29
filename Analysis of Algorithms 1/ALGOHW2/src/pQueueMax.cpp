#include "pQueueMax.h"
#include <iostream>
#include <cmath>
//algorithms are explained in the report
pQueueMax::pQueueMax(){}

float pQueueMax::parent(float i){
    return floor(i/2);
}
float pQueueMax::leftChild(float i){
    return 2*i + 1;
}
float pQueueMax::rightChild(float i){
    return 2*i +2;
}
void pQueueMax::maxHeapify(float i){
    float l = leftChild(i);
    float r = rightChild(i);
    float largest = i;
    if(l<=array.size()-1 && array[l]>array[i]){
        largest=l;
    } 
    if(r<=array.size()-1 && array[r]>array[largest]){
        largest=r;
    }
    if(largest != i){
        swap(array[i],array[largest]);
        maxHeapify(largest);
    }
}

void pQueueMax::insert(float p){
    if (this->isEmpty()){
        array.emplace_back(p);
    }
    else{
        array.emplace_back(p);
        int pIndex=array.size() - 1;
        while(pIndex!=0){
            if(array[pIndex]>array[(pIndex-1)/2]){
                swap(array[pIndex],array[(pIndex-1)/2]);
                pIndex=(pIndex-1)/2;
            }
            else{
                break;
            }
        }
    }
}
float pQueueMax::extractMax(){
    float max = array[0];
    array[0] = array[array.size()-1];
    array.pop_back();
    this->maxHeapify(0);
    return max;
}
float pQueueMax::max(){
    return array[0];
}
float pQueueMax::getSize(){
    return array.size();
}
float pQueueMax::mean(){
    float total=0;
    for(long unsigned int i=0;i<array.size();i++){
        total+=array[i];
    }
    return total/array.size();
}
float pQueueMax::standardDeviation(){
    float distances=0;
    float mean = this->mean();
    for(long unsigned int i=0;i<array.size();i++){
        distances+=pow((array[i]-mean),2);
    }
    return sqrt(distances/array.size());
}
bool pQueueMax::isEmpty(){
    return array.empty();
}
vector<float> pQueueMax::getVector(){
    return array;
}

void pQueueMax::print(){
    for(auto i:array){
        cout<<i<<" ";
    }
}