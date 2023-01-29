#pragma once
class passenger//a class for passengers
{
public:
    int ID;
    int milesFlown;
    bool isPregnant;
    bool isDisabled;
    int enqueueTime;
    int checkinTime;
public:
    passenger(int,int,bool,bool,int,int);
    bool operator> (const passenger &);

};

class agent{//a class for agents
public:
    int ID;//id
    bool isAvailable;//showing if he is busy with a passenger
    int busyFor;//showing how many minutes he is busy for
public:
    agent(int,bool,int);
};


