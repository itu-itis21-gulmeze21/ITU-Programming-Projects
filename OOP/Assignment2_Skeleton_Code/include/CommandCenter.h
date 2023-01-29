#include <iostream>
#include "Robot.h"
using namespace std;
class Crew{
	private:
		friend class CommandCenter;
		int maxExplorers;
		int maxMiners;
		int crewManufactureCost;
		float crewMaintenanceCost;
		int explorerCrewSize;
		int minerCrewSize;
		Explorer **ExplorerCrew;
		Miner **MinerCrew;
	public:
		Crew(int,int,int,int);
		~Crew();
		Robot* manufactureRobot(string type="explorer");
		void initMovement();
		void updateDurability();
		void operator+=(const Robot*);
		void operator-=(string name);
		void showInfo()const;
		//needed getters and setters
		int getExplorerCrewSize()const{
			return explorerCrewSize;
		}
		int getMinerCrewSize()const{
			return minerCrewSize;
		}
		Explorer** getExplorers()const{
			return ExplorerCrew;
		}
		Miner** getMiners()const{
			return MinerCrew;
		}
		float getCrewMaintenanceCost()const{
			return crewMaintenanceCost;
		}
		void setCrewMaintenanceCost(float cost){
			crewMaintenanceCost=cost;
		}

};

class CommandCenter{
	private:
		const int neededSelenium;
		const float searchArea;
		const int seleniumWorth;
		int turnCount;
		float totalCrewMaintenanceCost;
		float profit;
	public:
		CommandCenter(int,float,int);
		bool isGameEnded()const;
		float calculateProfit(Crew&);
		void operator++();
		void showInfo()const;
};



