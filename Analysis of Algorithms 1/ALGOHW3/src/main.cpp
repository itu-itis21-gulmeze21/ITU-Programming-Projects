#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include "Node.h"
#include "RBTree.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]){

    fstream inputfile;
    inputfile.open(argv[1], ios::in);

    ofstream outputFile("output.txt");

    int NumOfProcesses, SimulatorRunTime;
    vector<Node*> processes;//stores the processes before inserting them into the rbtree
    string ProcessID;
    int TimeOfArrival;
    int BurstTime; 

    inputfile>>NumOfProcesses>>SimulatorRunTime;

    for (int i=0;i<NumOfProcesses;i++){
        inputfile>>ProcessID>>TimeOfArrival>>BurstTime;
        processes.emplace_back(new Node(BurstTime,ProcessID,TimeOfArrival));//construct the processes as nodes
    }

    vector<string> completedTasks;

    RBTree tree;
    Node* runningTask = nullptr;//running task is null at the beginning
    int minvruntime = 0;
    int clock = 0;
    auto start = high_resolution_clock::now();//start of the clock for the execution time.
    while(clock != SimulatorRunTime){//until it hits the deadline
        for( auto i : processes) {//insert the processes that has the arrival time == clock
            if(i->arrivalTime == clock){
                tree.insert_node(i);
            }
        }
        
        
        if(!tree.isEmpty()){
            
            if(runningTask == nullptr){//if there is no current running task
                minvruntime = tree.findMinvruntime();//find the leftmost childs vruntime
                Node* temp = tree.get_root();
                while(temp->get_left()->get_left() != nullptr){//gets that leftmost child and assigns it as the running task
                    temp = temp->get_left();
                }
                runningTask = temp;
                outputFile<<clock<<","<<runningTask->get_name()<<","<<runningTask->vtime<<","<<minvruntime<<",";
                tree.inorder_traverse(tree.get_root(),outputFile);
                if(runningTask->vtime+1 == runningTask->get_burstTime()){
                    outputFile<<", Complete";
                }
                else{
                    outputFile<<", Incomplete";
                }
                outputFile<<endl;
                runningTask->vtime++;//after printing the round status, increment the vruntime of the running task
            }
            else{//if there exists a running task
                //minvruntime has 2 options: running tasks vruntime or its parents vruntime
                Node* parentOfRunningTask = runningTask->get_parent();
                if(parentOfRunningTask->vtime < runningTask->vtime){
                    minvruntime = parentOfRunningTask->vtime;
                }
                else{
                    minvruntime = runningTask->vtime;
                }
                if(runningTask->vtime <= minvruntime){//if the process still has the min vruntime

                    outputFile<<clock<<","<<runningTask->get_name()<<","<<runningTask->vtime<<","<<minvruntime<<",";
                    tree.inorder_traverse(tree.get_root(),outputFile);
                    if(runningTask->vtime+1 == runningTask->get_burstTime()){
                        outputFile<<", Complete";
                    }
                    else{
                        outputFile<<", Incomplete";
                    }
                    outputFile<<endl;
                    runningTask->vtime++;
                }
                else{//if the parent of the currently running task's vruntime is the minimum
                    tree.delete_node(runningTask);//delete and insert again
                    tree.insert_node(runningTask);
                    Node* temp = tree.get_root();
                    while(temp->get_left()->get_left() != nullptr){//find the new running task
                        temp = temp->get_left();
                    }
                    runningTask = temp;
                    outputFile<<clock<<","<<runningTask->get_name()<<","<<runningTask->vtime<<","<<minvruntime<<",";
                    tree.inorder_traverse(tree.get_root(),outputFile);
                    if(runningTask->vtime+1 == runningTask->get_burstTime()){
                        outputFile<<", Complete";
                    }
                    else{
                        outputFile<<", Incomplete";
                    }
                    outputFile<<endl;
                    runningTask->vtime++;
                } 
            }
        }
        else{
            outputFile<<clock<<",-,-,-,-,-,-"<<endl;
        }
        if(runningTask != nullptr && runningTask->vtime == runningTask->get_burstTime()){//check if the running task is completed
                tree.delete_node(runningTask);
                completedTasks.emplace_back(runningTask->get_name());
                runningTask = nullptr;
        }
        
        clock++;
        
    }
    outputFile<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    outputFile<<"Scheduling finished in "<<duration.count()<<" ms."<<endl;
    outputFile<<completedTasks.size()<<" of "<<NumOfProcesses<<" processes are completed."<<endl;
    outputFile<<"The order of completion of the tasks: ";
    for(auto i:completedTasks){
        if(i == completedTasks.back()){
            outputFile<<i;
        }
        else{
            outputFile<<i<<"-";
        }
    }






    return EXIT_SUCCESS;
}