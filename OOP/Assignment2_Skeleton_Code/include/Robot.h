//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//
#include <iostream>
#ifndef _H
#define _H
using namespace std;
class Robot {
	private:
		static int unqID;
		string RobotName;
		const string RobotType;
		float speed; 
		int durability; 
		const int manufactureCost; 
		float maintenanceCost;
		bool canMove;
	public:
		Robot(string,float,int,int,float);
		Robot(string,int);
		Robot& operator=(const Robot&);
		void showInfo()const;
		//needed getters and setters
		bool getCanMove()const{
			return canMove;
		}
		void setCanMove(bool flag){
			canMove=flag;
		}
		int getDurability()const{
			return durability;
		}
		void setDurability(int d){
			durability=d;
		}
		string getType()const{
			return RobotType;
		}
		string getName()const{
			return RobotName;
		}
		float getMaintenanceCost(){
			return maintenanceCost;
		}
		int getManufactureCost()const{
			return manufactureCost;
		}
		void setSpeed(float s){
			speed=s;
		}
}; 

class Explorer:public Robot{
	private:
		friend class CommandCenter;
		static float totalExploredArea;
		static int totalNumberOfSeleniumArea;
		float exploredArea;
		bool detectedSelenium;
		friend class Miner;
	public:
		Explorer(string,float,int);
		Explorer();
		bool move()const;
		void explore();
		Explorer& operator=(const Explorer&);
		void showInfo()const;
};

class Miner:public Robot{
	private:
		friend class CommandCenter;	
		static int totalGatheredSelenium;
		int gatheredSelenium;
	public:
		Miner(string,float,int);
		Miner();
		void mine();
		bool move()const;
		Miner& operator=(const Miner&);
		void showInfo()const;
};


#endif