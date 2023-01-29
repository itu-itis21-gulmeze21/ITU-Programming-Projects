#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Coordinate{
    public:
    int xCor;
    int yCor;
    Coordinate(int x,int y):xCor(x),yCor(y){}
    void print(){
        cout<<"("<<xCor<<","<<yCor<<")"<<" ";
    }

};

class CoordinateComparator{
    public:
    bool operator()(Coordinate& c1,Coordinate& c2){
        if(c1.xCor>c2.xCor){
            return true;
        }
        return false;
    }
};



void heap_stl();
void priority_queues();
void comparator_examples(){
    vector<Coordinate> v;
    v.push_back(Coordinate(6,2));
    v.push_back(Coordinate(3,5));
    v.push_back(Coordinate(4,4));
    v.push_back(Coordinate(5,8));
    v.push_back(Coordinate(1,1));
    v.push_back(Coordinate(7,0));

    CoordinateComparator cc;

    //sort(v.begin(),v.end(),cc);

    sort(v.begin(),v.end(),[](Coordinate& c1,Coordinate& c2)->bool{
        return(c1.yCor<c2.yCor);
    }
    );
    for(auto c:v){
        c.print();
    }
}

int main(){

    //heap_stl();
    //priority_queues();
    comparator_examples();
    

    return EXIT_SUCCESS;
}
void priority_queues(){
    priority_queue<int,vector<int>,std::greater<int>> mypq;

    mypq.push(30);
    mypq.push(20);
    mypq.push(40);
    mypq.push(10);
    mypq.push(400);

    while (!mypq.empty())
    {
        cout<<mypq.top()<<" ";
        mypq.pop();
    }
    
}

void heap_stl(){
    vector<int> v1 = {12,35,21,10,11,8,22,23,30};

    make_heap(v1.begin(),v1.end(),std::greater<>{});

    v1.push_back(45);

    push_heap(v1.begin(),v1.end());
    pop_heap(v1.begin(),v1.end());
    v1.pop_back();

    //sort_heap(v1.begin(),v1.end());
    if(is_heap(v1.begin(),v1.end()))
        cout<<"This is a heap"<<endl;

    for(int i:v1){
        cout<<i<<" ";
    }
    cout<<endl;

    
}