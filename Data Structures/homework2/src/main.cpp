#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Pqueue.h"
#include "passenger.h"

using namespace std;

bool allAvailable(vector<agent> &agents){//checks if all the agents are available(necessary for checking if the check-in process is done or not)
    bool flag=true;
    for(int i=0;i<int(agents.size());i++){
        if(!agents[i].isAvailable){
            flag=false;
            break;
        }
    }
    return flag;
}

int main(int argc, char** argv){
    //getting the inputs from the txt files and creating the objects accordingly

    int numberOfPassengers;
    int numberOfAgents;
    bool isInternational;

    vector<agent> agents;//agents
    
    vector<passenger> people;//all the people who came for a flight

    fstream infile;                
    infile.open(argv[1], ios::in);

    if(infile.is_open()){
        string input;
        infile>>input;
        numberOfPassengers=stoi(input);
        infile>>input;
        numberOfAgents=stoi(input);
        infile>>input;
        isInternational=stoi(input);

        for(int i=0;i<numberOfAgents;i++){
            agents.emplace_back(agent(i+1,1,0));
        }

        for(int i=0;i<numberOfPassengers;i++){
            string ID;
            string milesFlown;
            string isPregnant;
            string isDisabled;
            string enqueueTime;
            string checkinTime;
            infile>>ID>>milesFlown>>isPregnant>>isDisabled>>enqueueTime>>checkinTime;
            people.emplace_back(passenger(stoi(ID),stoi(milesFlown),stoi(isPregnant),stoi(isDisabled),stoi(enqueueTime),stoi(checkinTime)));
        }
    }

    infile.close();

    Pqueue checkInQueue;

    int minute=1;

    //these 3 vectors will be used for keeping the process information (which agent took which passenger at what time)
    vector<int> agentids;
    vector<int> passengerids;
    vector<int> mins;

    while(minute<=10000){//we will go minute by minute and see what happens in each minute
        for(int i=0;i<int(agents.size());i++){//if an agent finishes his work, he will be set as available
            if(agents[i].busyFor==0){
                agents[i].isAvailable=true;
            }
        }
        if(people.empty() && allAvailable(agents) && checkInQueue.isEmpty()){//if there are no people left, all agents are available and there is nobody in the queue
            break;//process is finished, break the loop
        }
        for(int i=0;i<int(people.size());i++){//look at every passenger 
            if(people[i].enqueueTime==minute){//if a passenger enters the queue in this minute
                checkInQueue.insert(people[i]);//add him to the queue
                swap(people[i],people[people.size()-1]);//swap the added passenger with the last passenger in the people vector
                people.pop_back();//remove that passenger from the people vector since he entered the queue
                i--;//stay at that index since the passenger at that index is swapped with the last passenger before
            }
        }
        for(int i=0;i<numberOfAgents;i++){//look at all the agents
            if(agents[i].isAvailable && !checkInQueue.isEmpty()){//if this agent is available and there is somebody waiting at the queue
                agentids.emplace_back(agents[i].ID);
                passengerids.emplace_back(checkInQueue.top().ID);
                mins.emplace_back(minute);
                agents[i].isAvailable=false;//passenger is assigned to this agent
                agents[i].busyFor=checkInQueue.top().checkinTime;//agent will be busy for the passenger's checkintime
                checkInQueue.pop();//remove this passenger from the queue
            }
        }
        minute++;//increment the minute
        for(int i=0;i<int(agents.size());i++){//decrement the agent's busyfor if he is dealing with a passenger
            if(!(agents[i].isAvailable)){
                agents[i].busyFor--;
            }
        }
    }
    if(isInternational){//if this flight is an international flight
        if(minute<=180){//if the process is ended in time, print the check-in info 
            for(int i=0;i<int(agentids.size());i++){
                cout<<"Agent "<<agentids[i]<<" takes passenger "<<passengerids[i]<<" at minute "<<mins[i]<<endl;
            }
            cout<<endl;
            cout<<"Check-in is complete on time in "<<minute<<" minutes."<<endl;
        }
        else{//if it failed, just print the fail message
            cout<<"Check-in failed to be completed on time, it took "<<minute<<" minutes."<<endl;
        }
    }
    else{//same logic with the international flight
        if(minute<=120){
            for(int i=0;i<int(agentids.size());i++){
                cout<<"Agent "<<agentids[i]<<" takes passenger "<<passengerids[i]<<" at minute "<<mins[i]<<endl;
            }
            cout<<endl;
            cout<<"Check-in is complete on time in "<<minute<<" minutes."<<endl;
        }
        else{
            cout<<"Check-in failed to be completed on time, it took "<<minute<<" minutes."<<endl;
        }
    }

    return EXIT_SUCCESS;
}