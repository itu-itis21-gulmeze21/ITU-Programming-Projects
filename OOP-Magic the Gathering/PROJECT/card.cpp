//
// Created by erceg on 14.05.2021.
//

#include "card.h"

card::card():nameOfTheCard(" "),typeOfTheCard(" "){
}
card::card(std::string notc, std::string totc,std::vector<char> mc):nameOfTheCard(notc),typeOfTheCard(totc){
    for(int i=0;i<mc.size();i++){
        manacosts.push_back(mc[i]);
    }
}
std::string card::getType() {
    return typeOfTheCard;
}

std::string card::getName() {
    return nameOfTheCard;
}

void card::play(std::shared_ptr<player> onePlayer,std::shared_ptr<player> opponent) {
}
void card::tapCard() {
}
void card::decraseHP(int decraselevel) {
}
void card::increaseHP(int increaseLevel) {
}
void card::decraseAttackPower(int decraseLevel) {
}
void card::increaseAttackPower(int increaseLevel) {
}
int card::getHP() {
    return 0;
}
int card::getAttackPower() {
    return 0;
}
void card::controlIfCreatureIsDead() {
}
std::string card::getColor() {
    return " ";
}
void card::gainFirstStrikeAbility() {
}
void card::loseFirstStrikeAbility() {
}
void card::gainTrampleAbility() {
}
void card::loseTrampleAbility() {
}
bool card::isItDestroyed() {
    return false;
}
bool card::doesItHaveFirstStrike() {
    return false;
}
bool card::doesItHaveTrample() {
    return false;
}
void card::makeLandCardDestroyed() {
}
void card::makeEnchantmentCardDestroyed() {
}
void card::useEffect(std::shared_ptr<card> aCard) {
}

void card::combatWithCreatureCard(std::shared_ptr<card> defender,std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
}

void card::makeCreatureCardDestroyed() {
}

void card::combatWithPlayer(std::shared_ptr<player> opponent) {
}

void card::untapCard(std::shared_ptr<player> aPlayer) {
}

//void card::negativeEffect(std::shared_ptr<card> aCard) {
//}

bool card::isItTapped() {
    return true;
}

void card::effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard) {
}

int card::getBaseAP() {
    return 0;
}

std::string card::getAffectedCreatureName() {
    return " ";
}


creature::creature(std::string notc, std::vector<char> mc, std::string c, int ap, int hp, bool hta,
                   bool hfsa): card(notc,"Creature",mc),colourOfTheCard(c),attackPower(ap),HP(hp),hasTrampleAbility(hta),hasFirstStrikeAbility(hfsa) {
    istapped= false;
    isdestroyed= false;
    baseHP=hp;
    baseAttackPower=ap;
}

void creature::decraseHP(int decraselevel) {
    HP-=decraselevel;
}

int creature::getHP() {
    return HP;
}

void creature::controlIfCreatureIsDead() {
    if(HP<=0){
        isdestroyed=true;
    }
}

std::string creature::getColor() {
    return colourOfTheCard;
}

void creature::increaseHP(int increaseLevel) {
    HP+=increaseLevel;
}

void creature::decraseAttackPower(int decraseLevel) {
    attackPower-=decraseLevel;
}

void creature::increaseAttackPower(int increaseLevel) {
    attackPower+=increaseLevel;
}

void creature::gainFirstStrikeAbility() {
    hasFirstStrikeAbility=true;
}

void creature::loseFirstStrikeAbility() {
    hasFirstStrikeAbility=false;
}

void creature::gainTrampleAbility() {
    hasTrampleAbility=true;
}

void creature::loseTrampleAbility() {
    hasTrampleAbility=false;
}

void creature::displayCard() {
    std::cout<<nameOfTheCard<<", HP:"<<HP<<"/";
}

bool creature::isItDestroyed() {
    return isdestroyed;
}

bool creature::doesItHaveFirstStrike() {
    return hasFirstStrikeAbility;
}

bool creature::doesItHaveTrample() {
    return hasTrampleAbility;
}

std::string creature::getType() {
    return "Creature";
}

int creature::getAttackPower() {
    return attackPower;
}

void creature::play(std::shared_ptr<player> onePlayer,std::shared_ptr<player> opponent) {
    onePlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    int tapCount=0;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                onePlayer->deleteManaFromCurrentMana(chosenMana);
                tapCount++;
            }
        }
        else{
            onePlayer->deleteManaFromCurrentMana(manacosts[i]);
            tapCount++;
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this creature card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<tapCount;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < onePlayer->getInPlaySize() ; j++) {
            onePlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}

void creature::tapCard() {
    istapped=true;
}

void creature::makeCreatureCardDestroyed() {
    isdestroyed= true;
}

void creature::combatWithCreatureCard(std::shared_ptr<card> defender,std::shared_ptr<player> aPlayer, std::shared_ptr<player> opponent) {//discarda gitme olayını ekle ,coutları eklesek mi?
    istapped= true;
    if(doesItHaveTrample()){
        int excessAttackPower= attackPower-defender->getHP();
        opponent->changeHp(-excessAttackPower);
        std::cout<<"Attacking creature has Trample ability, excess attack power that is dealt to opponent is "<<excessAttackPower<<"!"<<std::endl;
        if (opponent->getHp()<=0){
            opponent->makePlayerDestroyed();
            std::cout<<"Opponent has been destroyed,GAME OVER!"<<std::endl;
        } else{
            std::cout<<"Opponent's HP is decreased to "<<opponent->getHp()<<"!"<<std::endl;
        }
    }
    if(doesItHaveFirstStrike()){
        if(defender->doesItHaveFirstStrike()){
            defender->decraseHP(attackPower);
            decraseHP(defender->getAttackPower());
            std::cout<<"Both creatures have First Strike Ability, normal attack procedure!"<<std::endl;
            std::cout<<"Attacker's updated HP: "<<HP<<std::endl;
            std::cout<<"Defender's updated HP: "<<defender->getHP()<<std::endl;
            if(defender->getHP()<=0){
                defender->makeCreatureCardDestroyed();
                opponent->moveTheCardFromInplayToDiscard(defender->getName());
                std::cout<<defender->getName()<<" is destroyed and sent to the discard pile!"<<std::endl;
            }
            if(HP<=0){
                isdestroyed=true;
                aPlayer->moveTheCardFromInplayToDiscard(nameOfTheCard);
                std::cout<<nameOfTheCard<<" is destroyed and sent to the discard pile!"<<std::endl;
            }
        }
        else if(!defender->doesItHaveFirstStrike()){
            defender->decraseHP(attackPower);
            std::cout<<"Attacker has First Strike ability, Opponent doesn't. Attacker attacked first!"<<std::endl;
            std::cout<<"Attacker's updated HP: "<<HP<<std::endl;
            std::cout<<"Defender's updated HP: "<<defender->getHP()<<std::endl;
            if(defender->getHP()<=0){
                defender->makeCreatureCardDestroyed();
                opponent->moveTheCardFromInplayToDiscard(defender->getName());
                std::cout<<defender->getName()<<" is destroyed and sent to the discard pile!"<<std::endl;
            }
            else{
                decraseHP(defender->getAttackPower());
                std::cout<<"Attacker couldn't destroy the defender. Now, the defender attacks!"<<std::endl;
                std::cout<<"Attacker's updated HP: "<<HP<<std::endl;
                std::cout<<"Defender's updated HP: "<<defender->getHP()<<std::endl;
                if(HP<=0){
                    isdestroyed=true;
                    aPlayer->moveTheCardFromInplayToDiscard(nameOfTheCard);
                    std::cout<<nameOfTheCard<<" is destroyed and sent to the discard pile!"<<std::endl;
                }
            }
        }
    }
    else if(!doesItHaveFirstStrike()){
        if(defender->doesItHaveFirstStrike()){
            decraseHP(defender->getAttackPower());
            std::cout<<"Attacker doesn't have First Strike Ability, but Defender has. Defender attacks first!"<<std::endl;
            std::cout<<"Attacker's updated HP: "<<HP<<std::endl;
            std::cout<<"Defender's updated HP: "<<defender->getHP()<<std::endl;
            if(HP<=0){
                isdestroyed= true;
                aPlayer->moveTheCardFromInplayToDiscard(nameOfTheCard);
                std::cout<<nameOfTheCard<<" is destroyed and sent to the discard pile!"<<std::endl;
            }
            else{
                defender->decraseHP(attackPower);
                std::cout<<"Defender couldn't destroy the defender. Now, the Attacker attacks!"<<std::endl;
                std::cout<<"Attacker's updated HP: "<<HP<<std::endl;
                std::cout<<"Defender's updated HP: "<<defender->getHP()<<std::endl;
                if(defender->getHP()<=0){
                    defender->makeCreatureCardDestroyed();
                    opponent->moveTheCardFromInplayToDiscard(defender->getName());
                    std::cout<<defender->getName()<<" is destroyed and sent to the discard pile!"<<std::endl;
                }
            }
        }
        else if(!defender->doesItHaveFirstStrike()){
            std::cout<<"Both creatures don't have First Strike Ability, normal attack procedure!"<<std::endl;
            defender->decraseHP(attackPower);
            decraseHP(defender->getAttackPower());
            std::cout<<"Attacker's updated HP: "<<HP<<std::endl;
            std::cout<<"Defender's updated HP: "<<defender->getHP()<<std::endl;
            if(defender->getHP()<=0){
                defender->makeCreatureCardDestroyed();
                opponent->moveTheCardFromInplayToDiscard(defender->getName());
                std::cout<<defender->getName()<<" is destroyed and sent to the discard pile!"<<std::endl;
            }
            if(HP<=0){
                isdestroyed=true;
                aPlayer->moveTheCardFromInplayToDiscard(nameOfTheCard);
                std::cout<<nameOfTheCard<<" is destroyed and sent to the discard pile!"<<std::endl;
            }
        }
    }
}

void creature::combatWithPlayer(std::shared_ptr<player> opponent) {
    opponent->changeHp(-attackPower);
    if(opponent->getHp()<=0){
        opponent->makePlayerDestroyed();
        std::cout<<"Opponent has been destroyed,GAME OVER!"<<std::endl;
    }
    else{
        std::cout<<"Opponent's HP is decreased to "<<opponent->getHp()<<"!"<<std::endl;
    }
}

void creature::untapCard(std::shared_ptr<player> aPlayer) {
    istapped= false;
    HP=baseHP;
}

bool creature::isItTapped() {
    return istapped;
}

int creature::getBaseAP() {
    return baseAttackPower;
}

land::land(std::string notc, char mv) :manaValue(mv){
    nameOfTheCard=notc;
    typeOfTheCard="Land";
    std::vector<char> temp(1,0);
    manacosts=temp;
    istapped=false;
    isDestroyed= false;
}
char land::getManaValue() {
    return manaValue;
}

void land::makeLandCardDestroyed() {
    isDestroyed=true;
}
void land::displayCard(){
    std::cout<<nameOfTheCard<<"/";
}

std::string land::getType() {
    return "Land";
}

void land::play(std::shared_ptr<player> onePlayer,std::shared_ptr<player> opponent) {
    onePlayer->addMana(manaValue);
    onePlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    std::cout<<nameOfTheCard<<" is moved to the inplay pile!"<<std::endl;
}

void land::tapCard() {
    istapped=true;
}

void land::untapCard(std::shared_ptr<player> aPlayer) {
    istapped= false;
    aPlayer->addMana(manaValue);
}

bool land::isItTapped() {
    return istapped;
}


enchantment::enchantment(std::string notc, std::vector<char> mc, std::string c,bool id) :card(notc,"Enchantment",mc),color(c),isDestroyed(false){
}

void enchantment::displayCard() {
    std::cout<<nameOfTheCard<<"/";
}

std::string enchantment::getType() {
    return "Enchantment";
}

void enchantment::makeEnchantmentCardDestroyed() {
    isDestroyed=true;
}

bool enchantment::isItDestroyed() {
    return isDestroyed;
}

void enchantment::tapCard() {
}

Rage::Rage(std::vector<char> mc,creatureGetsTrample ce): enchantment("Rage",mc,"Green", false),cardEffect(ce) {
    affectedCreatureName=" ";
}

creatureGetsTrample Rage::getTrampleAbility() {
    return cardEffect;
}

void Rage::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.getTrample(aCard);
}

void Rage::play(std::shared_ptr<player> oneplayer,std::shared_ptr<player> opponent) {
    oneplayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                oneplayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            oneplayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Enchantment card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<1;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < oneplayer->getInPlaySize() ; j++) {
            oneplayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<"On which card do you want to use this effect?"<<std::endl;
    std::string choice;
    std::cin>>choice;
    affectedCreatureName=choice;
    for(int a=0;a<oneplayer->inplay.size();a++){
        if(oneplayer->inplay[a]->getName()==choice){
            useEffect(oneplayer->inplay[a]);
            std::cout<<choice<<" gained Trample ability!"<<std::endl;
            break;
        }
    }
    std::cout<<"Updated inplay pile: ";
    oneplayer->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}

std::string Rage::getAffectedCreatureName() {
    return affectedCreatureName;
}

HolyWar::HolyWar(std::vector<char> mc, allOfWhiteCreaturesGet1 ce): enchantment("HolyWar", mc, "White", false), cardEffect(ce) {
}

allOfWhiteCreaturesGet1 HolyWar::getCreaturesPlusOne() {
    return cardEffect;
}

void HolyWar::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.creaturesget1(aCard);
}

void HolyWar::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    aPlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Enchantment card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<2;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    for(int i=0;i<aPlayer->inplay.size();i++){
        useEffect(aPlayer->inplay[i]);
    }
    std::cout<<"Player "<<aPlayer->getNum()<<"'s all white creatures gained +1/+1!"<<std::endl;
    std::cout<<"Updated inplay pile: ";
    aPlayer->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}

//void HolyWar::negativeEffect(std::shared_ptr<card> aCard) {
//    if(aCard->getColor()=="White"){
//        aCard->decraseHP(1);
//        aCard->decraseAttackPower(1);
//
//    }
//}

void HolyWar::effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard) {
    if(aCard->getColor()=="White"){
        aCard->increaseHP(1);
        aCard->increaseAttackPower(1);
        std::cout<<"Newly entered card has been affected by the existing Holy War!"<<std::endl;
    }
}

HolyLight::HolyLight(std::vector<char> mc, allOfBlackCreaturesLose1 ce): enchantment("HolyLight", mc, "White", false), cardEffect(ce) {
}

allOfBlackCreaturesLose1 HolyLight::getCreaturesMinusOne() {
    return cardEffect;
}

void HolyLight::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.creatureslose1(aCard);
}

void HolyLight::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    aPlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Enchantment card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<2;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    for(int i=0;i<opponent->inplay.size();i++){
        useEffect(opponent->inplay[i]);
    }
    std::cout<<"Player "<<opponent->getNum()<<"'s all Black creatures gained -1/-1!"<<std::endl;
    for(int a=0;a<opponent->inplay.size();a++ ){
        if(opponent->inplay[a]->getHP()<=0 && opponent->inplay[a]->getType()=="Creature"){
            opponent->inplay[a]->makeCreatureCardDestroyed();
            opponent->moveTheCardFromInplayToDiscard(opponent->inplay[a]->getName());
            std::cout<<opponent->inplay[a]->getName()<<" has been destroyed and moved to the discard pile!"<<std::endl;
        }
    }
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}

//void HolyLight::negativeEffect(std::shared_ptr<card> aCard) {
//    if(aCard->getColor()=="Black"){
//        aCard->increaseHP(1);
//        aCard->increaseAttackPower(1);
//    }
//}

void HolyLight::effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard) {
    if(aCard->getColor()=="Black"){
        aCard->decraseHP(1);
        aCard->decraseAttackPower(1);
        std::cout<<"Newly entered card has been affected by the existing Holy Light!"<<std::endl;
    }
}


UnholyWar::UnholyWar(std::vector<char> mc, allOfBlackCreaturesGet2Attack ce): enchantment("UnholyWar", mc, "Black", false), cardEffect(ce) {
}

allOfBlackCreaturesGet2Attack UnholyWar::getCreaturesPlusTwo() {
    return cardEffect;
}

void UnholyWar::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.creaturesget2(aCard);
}

void UnholyWar::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    aPlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Enchantment card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<2;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    for(int i=0;i<aPlayer->inplay.size();i++){
        useEffect(aPlayer->inplay[i]);
    }
    std::cout<<"Player "<<aPlayer->getNum()<<"'s all Black creatures gained +2/+0!"<<std::endl;
    std::cout<<"Updated inplay pile: ";
    aPlayer->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}

//void UnholyWar::negativeEffect(std::shared_ptr<card> aCard) {
//    if(aCard->getColor()=="Black"){
//        aCard->decraseAttackPower(2);
//    }
//}
void UnholyWar::effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard) {
    if(aCard->getColor()=="Black"){
        aCard->increaseAttackPower(2);
        std::cout<<"Newly entered card has been affected by the existing Unholy War!"<<std::endl;
    }
}

Restrain::Restrain(std::vector<char> mc, allOfGreenCreaturesLoseTrample ce): enchantment("Restrain", mc, "Red", false), cardEffect(ce) {
}

allOfGreenCreaturesLoseTrample Restrain::getColorLosesTrample() {
    return cardEffect;
}

void Restrain::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.thisColorLosesTrample(aCard);
}

void Restrain::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    aPlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Enchantment card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<3;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    for (int i = 0; i < opponent->inplay.size(); i++) {
        useEffect(opponent->inplay[i]);
    }
    std::cout<<"Player "<<opponent->getNum()<<"'s all Green creatures lost Trample ability!"<<std::endl;
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}

//void Restrain::negativeEffect(std::shared_ptr<card> aCard) {
//    if(aCard->getColor()=="Green"){
//        aCard->gainTrampleAbility();
//    }
//}
void Restrain::effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard) {
    if(aCard->getColor()=="Green"){
        aCard->loseTrampleAbility();
        std::cout<<"Newly entered card has been affected by the existing Restrain!"<<std::endl;
    }
}

Slow::Slow(std::vector<char> mc,creatureLosesFirstStrike ce): enchantment("Slow",mc,"Black",false),cardEffect(ce) {
    affectedCreatureName=" ";
}

creatureLosesFirstStrike Slow::getSlowed() {
    return cardEffect;
}

void Slow::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.loseFirstStrike(aCard);
}

void Slow::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    aPlayer->moveTheCardFromHandToInplay(nameOfTheCard);
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Enchantment card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<1;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::string cardName;
    std::cout<<"On which creature card do you want to use this effect?"<<std::endl;
    std::cin>>cardName;
    affectedCreatureName=cardName;
    for(int i=0;i<opponent->inplay.size();i++){
        if(opponent->inplay[i]->getName()==cardName){
            useEffect(opponent->inplay[i]);
            break;
        }
    }
    std::cout<<cardName<<" lost First Strike ability!"<<std::endl;
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the inplay pile by paying its mana cost!"<<std::endl;
}
std::string Slow::getAffectedCreatureName() {
    return affectedCreatureName;
}

//void Slow::negativeEffect(std::shared_ptr<card> aCard) {
//    aCard->gainFirstStrikeAbility();
//}

sorcery::sorcery(std::string notc, std::vector<char> mc, std::string c):card(notc,"Sorcery",mc),color(c) {
}

void sorcery::displayCard() {
    std::cout<<nameOfTheCard<<"/";
}

std::string sorcery::getType() {
    return "Sorcery";
}

void sorcery::tapCard() {
}

Disenchant::Disenchant(std::vector<char> mc,  destroyEnchantmentEffect ce): sorcery("Disenchant", mc, "White"), cardEffect(ce) {
}

destroyEnchantmentEffect Disenchant::getDestroyEnchantment() {
    return cardEffect;
}

void Disenchant::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.destroyTheEnchantmentCard(aCard);
}

void Disenchant::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Sorcery card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<2;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<"Which enchantment card do you want to destroy?"<<std::endl;
    std::string choice;
    std::cin>>choice;
    std::string affectedCreatureNameForRageAndSlow;
    for(int i=0;i<opponent->inplay.size();i++){
        if(opponent->inplay[i]->getName()==choice){
            affectedCreatureNameForRageAndSlow=opponent->inplay[i]->getAffectedCreatureName();
            useEffect(opponent->inplay[i]);
            opponent->moveTheCardFromInplayToDiscard(opponent->inplay[i]->getName());
            break;
        }
    }
    aPlayer->moveTheCardFromHandToDiscard(nameOfTheCard);
    std::cout<<choice<<" is destroyed!"<<std::endl;
    if(choice=="HolyWar"){
        for(int a=0;a<opponent->inplay.size();a++){
            if(opponent->inplay[a]->getColor()=="White" && opponent->inplay[a]->getType()=="Creature"){
                opponent->inplay[a]->decraseHP(1);
                opponent->inplay[a]->decraseAttackPower(1);
                if(opponent->inplay[a]->getHP()<=0){
                    opponent->inplay[a]->makeCreatureCardDestroyed();
                    opponent->moveTheCardFromInplayToDiscard(opponent->inplay[a]->getName());
                    std::cout<<opponent->inplay[a]->getName()<<" has been destroyed!"<<std::endl;
                }
            }
        }
        std::cout<<"Opponent's all white creature cards lost 1/1 after Holy War being destroyed!"<<std::endl;
    }
    else if(choice=="HolyLight"){
        for(int a=0;a<aPlayer->inplay.size();a++){
            if(aPlayer->inplay[a]->getColor()=="Black" && aPlayer->inplay[a]->getType()=="Creature"){
                aPlayer->inplay[a]->increaseHP(1);
                aPlayer->inplay[a]->increaseAttackPower(1);
            }
        }
        std::cout<<"Your all black creature cards gained back +1/+1 after Holy Light being destroyed!"<<std::endl;
    }
    else if(choice=="UnholyWar"){
        for(int a=0;a<opponent->inplay.size();a++){
            if(opponent->inplay[a]->getColor()=="Black" && opponent->inplay[a]->getType()=="Creature"){
                opponent->inplay[a]->decraseAttackPower(2);
            }
        }
        std::cout<<"Opponent's all black creature cards lost 2/0 after Unholy War being destroyed!"<<std::endl;
    }
    else if(choice=="Restrain"){
        for(int a=0;a<aPlayer->inplay.size();a++){
            if(aPlayer->inplay[a]->getColor()=="Green" && aPlayer->inplay[a]->getType()=="Creature"){
                aPlayer->inplay[a]->gainTrampleAbility();
            }
        }
        std::cout<<"Your all green creatures gained Trample ability back again after Restrain being destroyed!"<<std::endl;
    }
    else if(choice=="Rage"){
        for (int i = 0; i < opponent->inplay.size(); i++) {
            if(opponent->inplay[i]->getName()==affectedCreatureNameForRageAndSlow){
                opponent->inplay[i]->loseTrampleAbility();
                std::cout<<opponent->inplay[i]->getName()<<" lost Trample Ability!"<<std::endl;
                break;
            }
        }
    }
    else if(choice=="Slow"){
        for (int i = 0; i < aPlayer->inplay.size(); i++) {
            if(aPlayer->inplay[i]->getName()==affectedCreatureNameForRageAndSlow){
                aPlayer->inplay[i]->gainFirstStrikeAbility();
                std::cout<<aPlayer->inplay[i]->getName()<<" gained First Strike Ability back again!"<<std::endl;
                break;
            }
        }
    }
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the discard pile by paying its mana cost!"<<std::endl;
}

Flood::Flood( std::vector<char> mc,  destroyLandEffect ce) : sorcery("Flood", mc, "Green"), cardEffect(ce){
}

destroyLandEffect Flood::getDestroyLand() {
    return cardEffect;
}
void Flood::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.destroyLand(aCard);
}

void Flood::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Sorcery card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<3;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<"Which land card do you want to destroy?"<<std::endl;
    std::string choice;
    std::cin>>choice;
    for(int i=0;i<opponent->inplay.size();i++){
        if(opponent->inplay[i]->getName()==choice){
            useEffect(opponent->inplay[i]);
            opponent->moveTheCardFromInplayToDiscard(opponent->inplay[i]->getName());
            break;
        }
    }
    aPlayer->moveTheCardFromHandToDiscard(nameOfTheCard);
    std::cout<<choice<<" is destroyed!"<<std::endl;
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the discard pile by paying its mana cost!"<<std::endl;
}

Plague::Plague( std::vector<char> mc,  dealDamageToCreatures ce): sorcery("Plague", mc, "Black"), cardEffect(ce) {
}

dealDamageToCreatures Plague::getDealDamageToCreatures() {
    return cardEffect;
}
void Plague::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.dealDamage(aCard);
}

void Plague::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Sorcery card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<3;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    for(int a=0;a<opponent->inplay.size();a++){
        useEffect(opponent->inplay[a]);
    }
    std::cout<<"Player"<<opponent->getNum()<<"'s all creatures gained 1 damage!"<<std::endl;
    //ölen var mı?
    for(int a=0;a<opponent->inplay.size();a++){
        if(opponent->inplay[a]->getType()=="Creature" && opponent->inplay[a]->getHP()<=0){
            opponent->inplay[a]->makeCreatureCardDestroyed();
            opponent->moveTheCardFromInplayToDiscard(opponent->inplay[a]->getName());
            std::cout<<opponent->inplay[a]->getName()<<" is destroyed!"<<std::endl;
        }
    }
    aPlayer->moveTheCardFromHandToDiscard(nameOfTheCard);
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the discard pile by paying its mana cost!"<<std::endl;
}

Terror::Terror(std::vector<char> mc, destroyCreatureEffect ce) : sorcery("Terror", mc, "Black"), cardEffect(ce){
}

destroyCreatureEffect Terror::getDestroyCreature() {
    return cardEffect;
}
void Terror::useEffect(std::shared_ptr<card> aCard) {
    cardEffect.destroyCreature(aCard);
}

void Terror::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Sorcery card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<2;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<"On which creature card do you want to use this effect?"<<std::endl;
    std::string choice;
    std::cin>>choice;
    for(int i=0;i<opponent->inplay.size();i++){
        if(opponent->inplay[i]->getName()==choice){
            useEffect(opponent->inplay[i]);
            opponent->moveTheCardFromInplayToDiscard(opponent->inplay[i]->getName());
            break;
        }
    }
    std::cout<<choice<<" is destroyed!"<<std::endl;
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the discard pile by paying its mana cost!"<<std::endl;
    aPlayer->moveTheCardFromHandToDiscard(nameOfTheCard);
}

LigthningBolt::LigthningBolt(std::vector<char> mc,  dealDamageToCreatures ce,deal2DamageToPlayer d2tp) : sorcery("LightningBolt", mc, "Green"), cardEffect(ce),
                                                                                                         cardEffect2(d2tp){

}

dealDamageToCreatures LigthningBolt::getDealDamageToCreatures() {
    return cardEffect;
}

deal2DamageToPlayer LigthningBolt::getDeal2DamageToPlayer() {
    return cardEffect2;
}

void LigthningBolt::useEffect(std::shared_ptr<card> aCard) {

}

void LigthningBolt::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Sorcery card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<2;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<"Select player or creature card to deal damage:"<<std::endl;
    std::string choice;
    std::cin>>choice;
    if(choice=="player"){////??????
        cardEffect2.damageToPlayer(opponent);
        if (opponent->getHp()<=0){
            std::cout<<"Opponent has been destroyed,GAME OVER!"<<std::endl;
        }
    }
    else{
        std::cout<<"On which creature card do you want to use this effect?"<<std::endl;
        std::string choice2;
        std::cin>>choice2;
        std::cout<<choice2<<" gained 2 damage!!"<<std::endl;
        for(int i=0;i<opponent->inplay.size();i++){
            if(opponent->inplay[i]->getName()==choice2){
                cardEffect.dealDamage(opponent->inplay[i]);
                cardEffect.dealDamage(opponent->inplay[i]);
                if(opponent->inplay[i]->getHP()<=0){
                    opponent->inplay[i]->makeCreatureCardDestroyed();
                    opponent->moveTheCardFromInplayToDiscard(opponent->inplay[i]->getName());
                    std::cout<<choice2<<" is destroyed!"<<std::endl;
                }
                break;
            }
        }
    }
    std::cout<<"Updated inplay pile: ";
    opponent->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the discard pile by paying its mana cost!"<<std::endl;
    aPlayer->moveTheCardFromHandToDiscard(nameOfTheCard);
}

Reanimate::Reanimate(std::vector<char> mc,  returnOneCardFromDiscardToHand rocfdth): sorcery("Reanimate", mc, "Black"), cardEffect(rocfdth) {
}

returnOneCardFromDiscardToHand Reanimate::getReturnOneCardEffect() {
    return cardEffect;
}

void Reanimate::useEffect(std::shared_ptr<card> aCard) {
}

void Reanimate::play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent) {
    char chosenMana;
    for(int i=0;i<manacosts.size();i++){
        if(manacosts[i]>= 49 && manacosts[i]<= 51){
            int j = manacosts[i]-48;
            std::cout<<"What type of mana do you want use instead of colorless mana?"<<std::endl;
            for(int x=0; x< j; x++){
                std::cin >> chosenMana;
                aPlayer->deleteManaFromCurrentMana(chosenMana);
            }
        }
        else{
            aPlayer->deleteManaFromCurrentMana(manacosts[i]);
        }
    }
    std::cout<<"Which land cards do you want to tap in order to play this Sorcery card?"<<std::endl;
    std::string nameOfTheCardToTap;
    for(int i=0;i<1;i++){
        std::cin>>nameOfTheCardToTap;
        for (int j = 0; j < aPlayer->getInPlaySize() ; j++) {
            aPlayer->tapCard(nameOfTheCardToTap);
            break;
        }
    }
    std::cout<<"Which card do you want to return from the discard pile?"<<std::endl;
    std::string cardName;
    std::cin>>cardName;
    for(int i=0;i<aPlayer->discard.size();i++){
        if (aPlayer->discard[i]->getName()==cardName && aPlayer->hand.size()<7){
            cardEffect.returnCard(aPlayer,aPlayer->discard[i]);
            std::cout<<cardName<<" is moved from discard pile to hand pile!"<<std::endl;
            break;
        }
    }
    std::cout<<"Updated inplay pile: ";
    aPlayer->displayInPlay();
    std::cout<<std::endl;
    std::cout<< nameOfTheCard<<" is moved to the discard pile by paying its mana cost!"<<std::endl;
    aPlayer->moveTheCardFromHandToDiscard(nameOfTheCard);
}
