#include "Pqueue.h"

Pqueue::Pqueue(){}

void Pqueue::insert(passenger p){
    if (this->isEmpty()){//if the queue is empty, simply add the passenger to the queue without checking if the structure is affected or not
        passengers.emplace_back(p);
    }
    else{
        passengers.emplace_back(p);
        int pIndex=passengers.size() - 1;//index of the newly added passenger
        while(pIndex!=0){//until this passenger becomes the root
            if(passengers[pIndex]>passengers[(pIndex-1)/2]){//check if it is bigger(prioritized) than its parent
                swap(passengers[pIndex],passengers[(pIndex-1)/2]);//if it is bigger, simply swap them
                pIndex=(pIndex-1)/2;//update the newly added passengers index for further parent-child checks
            }
            else{//if it is smaller than its parent, break the loop since the structure is correct, no more swapping is needed
                break;
            }
        }
    }
}
void Pqueue::pop(){
    if(passengers.size()==1){//if it is the only passenger in the queue, just pop it back
        passengers.pop_back();
    }
    else{
        swap(passengers[0],passengers[passengers.size()-1]);//swap it with the last item on the queue
        passengers.pop_back();//remove the last item
        if(passengers.size()!=1){//if there are more than 1 elements left on the queue, check if the structure is affected
            int index=0;
            while (int(passengers.size()) > 2*index +1)//while the left child exists
            {
                if(int(passengers.size()) > 2*index + 2){//if the right child exists
                    if(passengers[2*index +1]> passengers[2*index +2] && passengers[2*index +1]>passengers[index]){//if the left child is the biggest among its parent and the parents children
                        swap(passengers[2*index +1],passengers[index]);//swap them
                        index=2*index +1;//update the index for further checks
                    }
                    else if(passengers[2*index +2]> passengers[2*index +1] && passengers[2*index +2]>passengers[index]){//if the right child is the biggest among its parent and the parents children
                        swap(passengers[2*index +2],passengers[index]);//swap them
                        index=2*index +2;//update the index for further checks
                    }
                    else{//if the structure is correct, simply break the loop, no more swapping is needed
                        break;
                    }
                }
                else{//if the right child does not exist
                    if(passengers[2*index +1]>passengers[index]){//check if it is smaller than the left child
                        swap(passengers[2*index +1],passengers[index]);//swap them
                        index=2*index +1;//update the index
                    }
                    else{//if the structure is correct, simply break the loop, no more swapping is needed
                        break;
                    }
                }

            }
            
        }
    }
}
passenger Pqueue::top(){//returns the most prioritized passenger who is on the top of the max heap(zeroth element in the vector)
    return passengers[0];
}
int Pqueue::getSize(){//size of the passenger vector
    return passengers.size();
}
bool Pqueue::isEmpty(){//checks if the priority queue is empty
    return passengers.empty();
}