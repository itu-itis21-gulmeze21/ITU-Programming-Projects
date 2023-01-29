#include "passenger.h"

passenger::passenger(int id,int mf,bool p,bool d,int et,int ci):ID(id),milesFlown(mf),isPregnant(p),isDisabled(d),enqueueTime(et),checkinTime(ci){}//simple constructor for passenger class

bool passenger::operator> (const passenger &p){//overloading the '>' operator to compare passengers by their priorities according to the given criteria
    if((this->isPregnant || this->isDisabled) && (!p.isDisabled && !p.isPregnant)){//if he is pregnant or disabled and the person who is compared with him is neither pregnant nor disabled
        return true;//he has the priority(passenger with the priority is bigger than the other)
    }
    else if((p.isPregnant || p.isDisabled) && (!this->isDisabled && !this->isPregnant)){//the reverse case
        return false;
    }

    if(this->milesFlown>p.milesFlown){//after checking the pregnant or disabled case, check the milesflown if necessary
        return true;//person with more milesflown is prioritized
    }
    else if(this->milesFlown<p.milesFlown){
        return false;
    }
    else if(this->ID<p.ID){
        return true;
    }
    return false;
}

agent::agent(int id,bool ia,int bf):ID(id),isAvailable(ia),busyFor(bf){}//simple constructor for agent
