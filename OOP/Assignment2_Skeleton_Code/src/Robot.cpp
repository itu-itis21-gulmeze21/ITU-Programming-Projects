//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------/

#include <iostream>
using namespace std;
#include "Robot.h"



/*
****************
BEGIN: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/
int Robot::unqID=1;//static member initialized 
Robot::Robot(string t,float s,int d,int manuC,float mainC): RobotType(t),speed(s),durability(d),manufactureCost(manuC),maintenanceCost(mainC){//simple constructor for robot
    if(t=="explorer"){//setting the name
        RobotName="exp-" + to_string(Robot::unqID);
    }
    else{
        RobotName="mnr-" + to_string(Robot::unqID);
    }
    canMove=true;
    unqID++;//static member is incremented for the next robot
}
Robot::Robot(string t,int m):RobotType(t),manufactureCost(m){//another constructor which is written for default constructors of explorer and miner
    speed=0;
    durability=0;
    maintenanceCost=0;
    canMove=true;
    RobotName=" ";
}
Robot& Robot::operator=(const Robot& r){//basic assignment operator
    this->canMove=r.canMove;
    this->durability=r.durability;
    this->maintenanceCost=r.maintenanceCost;
    this->speed=r.speed;
    this->RobotName=r.RobotName;
    return *this;
}
void Robot::showInfo()const{
    cout<<"Name: "<<RobotName<<endl;
    cout<<"Type: "<<RobotType<<endl;
    cout<<"Speed: "<<speed<<endl;
    cout<<"Durability: "<<durability<<endl;
    cout<<"ManufactureCost: "<<manufactureCost<<endl;
    cout<<"MaintenanceCost: "<<maintenanceCost<<endl;
    cout<<"Can Move: "<<canMove<<endl;
}
/*
****************
END: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/
float Explorer::totalExploredArea=0;//static member initialized
int Explorer::totalNumberOfSeleniumArea=0;//static member initialized
Explorer::Explorer(string t,float s,int d):Robot(t,s,d,3000,450/s){
    exploredArea=0;
    detectedSelenium=false;
}
Explorer::Explorer():Robot("explorer",3000){//default constructor
    exploredArea=0;
    detectedSelenium=false;
}
bool Explorer::move()const{
    return this->getCanMove();
}
void Explorer::explore(){//explore function based on the given criteria
    int randomNumber = 0 + (rand() % 101);
    if(randomNumber>=40){
        detectedSelenium=true;
        totalExploredArea+=1500;
        exploredArea=1500;
        totalNumberOfSeleniumArea++;
    }
    else{
        detectedSelenium=false;
        totalExploredArea+=1500;
        exploredArea=1500;
    }
    //setCanMove(false);
}
Explorer& Explorer::operator=(const Explorer& e){
    Robot::operator=(e);//first calling the base class' operator
    exploredArea=e.exploredArea;
    detectedSelenium=e.detectedSelenium;
    return *this;
}
void Explorer::showInfo()const{
    Robot::showInfo();
    cout<<"explored area: "<<exploredArea<<endl;
}
/*
****************
END: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: MINER CLASS FUNCTION DECLARATIONS 
****************
*/
int Miner::totalGatheredSelenium=0;//static member initialized
Miner::Miner(string t,float s,int d):Robot(t,s,d,5000,750/s){
    gatheredSelenium=0;
}
Miner::Miner():Robot("miner",5000){//default constructor
    gatheredSelenium=0;
}
void Miner::mine(){
    int randomNumber = 10 + (rand() % 91) ;
    gatheredSelenium=5*randomNumber;
    totalGatheredSelenium+=gatheredSelenium;
    Explorer::totalNumberOfSeleniumArea--;//when an area is mined, total area found by explorers at that turn is decremented
}
bool Miner::move()const{
    return Explorer::totalNumberOfSeleniumArea!=0 && getCanMove();
}
Miner& Miner::operator=(const Miner& m){
    Robot::operator=(m);
    gatheredSelenium=m.gatheredSelenium;
    return *this;
}
void Miner::showInfo()const{
    Robot::showInfo();
    cout<<"# of gathered selenium: "<<gatheredSelenium<<endl;
}
/*
****************
END: MINER CLASS FUNCTION DECLARATIONS 
****************
*/

