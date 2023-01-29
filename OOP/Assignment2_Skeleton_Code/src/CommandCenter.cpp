//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------//
#include "CommandCenter.h"
#include "Robot.h"
#include <iostream>
using namespace std;
/*
****************
BEGIN: CREW CLASS FUNCTION DECLARATIONS 
****************
*/
Crew::Crew(int maxe,int maxm,int ecs,int mcs){
    //checking the given sizes and assigning the suitable sizes
    if(maxe<1 || maxe>5){
        maxExplorers=2;
    }
    else{
        maxExplorers=maxe;
    }
    if(maxm<1 || maxm>5){
        maxMiners=2;
    }
    else{
        maxMiners=maxm;
    }
    if(ecs<0 || ecs>maxExplorers){
        explorerCrewSize=maxExplorers;
    }
    else{
        explorerCrewSize=ecs;
    }
    if(mcs<0 || mcs>maxMiners){
        minerCrewSize=maxMiners;
    }
    else{
        minerCrewSize=mcs;
    }
    crewMaintenanceCost=0;
    ExplorerCrew=new Explorer*[maxExplorers];//initializing the crews
    MinerCrew=new Miner*[maxMiners];
    for(int i=0;i<maxExplorers;i++){
        if(i>=explorerCrewSize){//if there are empty spaces in the crew at the construction, make it null
            *(ExplorerCrew+i)=NULL;
        }
        else//manufacture the robot and add it to the crew. since manufacture function returns a pointer to a robot, static casting is used
            *(ExplorerCrew+i)=static_cast<Explorer*> (manufactureRobot("explorer"));
    }
    for(int i=0;i<maxMiners;i++){//same logic with the explorer crew
        if(i>=minerCrewSize){
            *(MinerCrew+i)=NULL;
        }
        else
            *(MinerCrew+i)=static_cast<Miner*> (manufactureRobot("miner"));
    }
    crewManufactureCost=explorerCrewSize*3000 + minerCrewSize*5000;//calculating the crews total manufacture cost at the beginning
    
}
Crew::~Crew(){//deletes the first layer and the second layer of pointers
    for(int i=0;i<maxExplorers;i++){
        delete ExplorerCrew[i];
    }
    delete[] ExplorerCrew;
    for(int i=0;i<maxMiners;i++){
        delete MinerCrew[i];
    }
    delete[] MinerCrew;
}
Robot* Crew::manufactureRobot(string type){//takes a default parameter which is set to "explorer" but it is not important since the type is given everytime when a robot is manufactured
    if(crewMaintenanceCost!=0){//this blocks checks if this function is called in the beginning of the game while constructing the crew since an input is not necessary at that phase
        string input;
        cout<<"Type: ";
        cin>>input;
        type=input;
    }
    //constructing the robot according to the given type
    if(type=="explorer"){
        int randomDurability = 1 + (rand() % 5);
        float randomSpeed = 1.5 + static_cast<float> (rand())/(static_cast<float> (RAND_MAX/(2.5-1.5))); 
        return new Explorer("explorer",randomSpeed,randomDurability);;
    }
    else{
        int randomDurability = 1 + (rand() % 5);
        float randomSpeed = 1.0 + static_cast<float> (rand())/(static_cast<float> (RAND_MAX/(1.5-1.0)));
        return new Miner("miner",randomSpeed,randomDurability);;
    } 
}
void Crew::initMovement(){//canMove is set true for all robots
    for(int i=0;i<explorerCrewSize;i++){
        ExplorerCrew[i]->setCanMove(true);
    }
    for(int i=0;i<minerCrewSize;i++){
        MinerCrew[i]->setCanMove(true);
    }
}
void Crew::updateDurability(){
    cout<<"Explorer durability is being updated"<<endl;
    for(int i=0;i<explorerCrewSize;i++){
        ExplorerCrew[i]->setDurability(ExplorerCrew[i]->getDurability()-1);//decrease the durability by one
        if(ExplorerCrew[i]->getDurability()!=0){//if the durability of the robot is not 0, do nothing
            
        }
        else{//otherwise set canMove false and call the -= operator. -= will delete that robot unless it is the last robot remaining in the crew
            ExplorerCrew[i]->setCanMove(false);
            cout<<ExplorerCrew[i]->getName()<<"'s durability=0"<<endl;
            this->operator-=(ExplorerCrew[i]->getName());
        }
    }
    cout<<"Miner durability is being updated"<<endl;
    for(int i=0;i<minerCrewSize;i++){//same logic with the explorer 
        MinerCrew[i]->setDurability(MinerCrew[i]->getDurability()-1);
        if(MinerCrew[i]->getDurability()!=0){
            
        }
        else{
            MinerCrew[i]->setCanMove(false);
            cout<<MinerCrew[i]->getName()<<"'s durability=0"<<endl;
            this->operator-=(MinerCrew[i]->getName());
        }
    }
}
void Crew::operator+=(const Robot* r){
    if(r->getType()=="explorer"){
        if(explorerCrewSize<maxExplorers){//check if there is enough space
            ExplorerCrew[explorerCrewSize]=static_cast<Explorer*> (const_cast<Robot*> (r));//add the robot
            ExplorerCrew[explorerCrewSize]->setCanMove(false);//it can not move when it is added
            explorerCrewSize++;
            crewManufactureCost+=3000;
        }
        else{
            cout<<"This robot cannot be added, check maximum size of the crew"<<endl;
            delete r;//delete the given robot to prevent memory leak
        }
    }
    else{
        if(minerCrewSize<maxMiners){
            MinerCrew[minerCrewSize]=static_cast<Miner*> (const_cast<Robot*> (r));
            MinerCrew[minerCrewSize]->setCanMove(false);
            minerCrewSize++;
            crewManufactureCost+=5000;
        }
        else{
            cout<<"This robot cannot be added, check maximum size of the crew"<<endl;
            delete r;
        }
    }
}
void Crew::operator-=(string name){
    if(name[0]=='e'){//checks the type by looking at its name
        if(explorerCrewSize>1){//checks if it is the last robot or not
                int index;
            for(int i=0;i<explorerCrewSize;i++){
                if(ExplorerCrew[i]->getName()==name){
                    index=i;//finds the index of the robot that ill be removed
                }
            }
            delete ExplorerCrew[index];//delete that robot
            ExplorerCrew[index]=NULL;//set it to null for further usage and to prevent memory leak
            for(int i=index;i<explorerCrewSize-index;i++){//shift the objects in the array
                ExplorerCrew[i]=ExplorerCrew[1+i];
            }
            
            explorerCrewSize--;
        }
        cout<<name<<": Goodbye"<<endl;
    }
    else{
        if(minerCrewSize>1){
                int index;
            for(int i=0;i<minerCrewSize;i++){
                if(MinerCrew[i]->getName()==name){
                    index=i;
                }
            }
            delete MinerCrew[index];
            MinerCrew[index]=NULL;
            for(int i=index;i<minerCrewSize-index;i++){
                MinerCrew[i]=MinerCrew[i+1];
            }
            
            minerCrewSize--;
        } 
        cout<<name<<": Goodbye"<<endl;
    }
}
void Crew::showInfo()const{
    cout<<"explorerCrew Size:"<<explorerCrewSize<<endl;
    cout<<"minerCrew Size:"<<minerCrewSize<<endl;
    for(int i=0;i<explorerCrewSize;i++){
        ExplorerCrew[i]->showInfo();
    }
    for(int i=0;i<minerCrewSize;i++){
        MinerCrew[i]->showInfo();
    }
    cout<<"Total manufacture cost: "<<crewManufactureCost<<endl;
    cout<<"Total maintenance cost: "<<crewMaintenanceCost<<endl;
}

/*
****************
END: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/
CommandCenter::CommandCenter(int seleniumAim,float exploreArea,int seleniumWorth):neededSelenium(seleniumAim),searchArea(exploreArea),seleniumWorth(seleniumWorth){//basic construtor
    turnCount=1;
    totalCrewMaintenanceCost=0;
    profit=0;
}
bool CommandCenter::isGameEnded()const{//checking the criteria for ending the game
    bool flag;
    if(searchArea==Explorer::totalExploredArea){
        flag=true;
        cout<<"Area has been fully explored."<<endl;
        cout<<"Aim: "<<neededSelenium<<" selenium."<<endl;
        cout<<"Collected: "<<Miner::totalGatheredSelenium<<endl;
        if(profit>0 && neededSelenium<=Miner::totalGatheredSelenium){//if the game is ended, check if mission is failed or not
            cout<<"Congrats!"<<endl;
        }
        else{
            cout<<"Mission Failed!"<<endl;
        }
    }
    else{
        flag=false;
    }
    return flag;
}
float CommandCenter::calculateProfit(Crew& c){//calculates the profit based on the given criteria
    float revenue= Miner::totalGatheredSelenium * seleniumWorth;
    float expenses= c.crewMaintenanceCost + c.crewManufactureCost;
    profit=revenue-expenses;
    cout<<"Profit:"<<revenue-expenses<<endl;
    cout<<"Expenses:"<<expenses<<endl;
    cout<<"Selenium Revenue:"<<revenue<<endl;
    return profit;
}
void CommandCenter::operator++(){
    turnCount++;
}
void CommandCenter::showInfo()const{
    cout<<"Current turn: "<<turnCount<<endl;
    cout<<"Aim: "<<neededSelenium<<" selenium."<<endl;
    cout<<"Collected: "<<Miner::totalGatheredSelenium<<endl;
    cout<<"Total Search Area: "<<searchArea<<endl;
    cout<<"Explored Area: "<<Explorer::totalExploredArea<<endl;
    cout<<"Currently, there are "<<Explorer::totalNumberOfSeleniumArea<<" area/s that include selenium."<<endl;
    if(Explorer::totalNumberOfSeleniumArea!=0){
        cout<<"Mine these areas if miners have not finished their turn! If you cannot cope with mining, you can always add new miners!"<<endl;
    }
}
/*
****************
END: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/