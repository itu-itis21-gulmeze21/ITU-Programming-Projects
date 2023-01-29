//
// Created by erceg on 15.05.2021.
//

#include "player.h"
#include "vector"
#include "memory"
#include "card.h"
#include <ctime>
#include <algorithm>
#include <random>

player::player(int num, std::vector<std::shared_ptr<card>> deck):playerNumber(num) {
    currentCardInHand=0;
    HP=15;
    isDestroyed= false;
    currentMana=std::vector<char>(0);
    for(int i=0;i<deck.size();i++){
        library.emplace_back(deck[i]);
    }
    hand=std::vector<std::shared_ptr<card>>(0);
    inplay=std::vector<std::shared_ptr<card>>(0);
    discard=std::vector<std::shared_ptr<card>>(0);
}
int player::getNum() {
    return playerNumber;
}

void player::setNum(int newNum) {
    playerNumber = newNum;
}
int player::getHp() {
    return HP;
}
void player::setHp(int num) {
    HP = num;
}

void player::changeHp(int change) {
    HP += change;
}



void player::moveTheCardFromLibraryToHand() {
    hand.emplace_back(library[library.size()-1]);
    library.pop_back();
}

void player::moveTheCardFromHandToInplay(std::string cardName) {
    for(int i=0;i<hand.size();i++){
        if (hand[i]->getName()==cardName){
            inplay.emplace_back(hand[i]);
            hand.erase(hand.begin()+i);
            break;
        }
    }
}

void player::moveTheCardFromInplayToDiscard(std::string cardName) {
    for(int i=0;i<inplay.size();i++){
        if (inplay[i]->getName()==cardName){
            discard.emplace_back(inplay[i]);
            inplay.erase(inplay.begin()+i);
            break;
        }
    }
}

void player::addMana(char value) {
    currentMana.emplace_back(value);
}

void player::moveTheCardFromDiscardToHand(std::shared_ptr<card> aCard) {
    hand.emplace_back(aCard);
    for(int i=0;i<discard.size();i++){
        if (discard[i]->getName()==aCard->getName()){
            discard.erase(discard.begin()+i);
            break;
        }
    }
}

void player::deleteManaFromCurrentMana(char ch) {
    for(int i=0;i<currentMana.size();i++){
        if (ch==currentMana[i]){
            currentMana.erase(currentMana.begin()+i);
            break;
        }
    }
}

int player::getInPlaySize() {
    return inplay.size();
}

void player::tapCard(std::string cardName) {
    for(int i=0;i<inplay.size();i++){
        if(inplay[i]->getName()==cardName && !inplay[i]->isItTapped()){//tapped olup olmadığına bak
            inplay[i]->tapCard();
            break;
        }
    }
}
void player::displayInPlay() {
    for(int i =0; i< inplay.size();i++){
        inplay[i]->displayCard();
    }
}

void player::displayCurrentMana() {
    for(int i =0; i < currentMana.size();i++){
        std::cout << currentMana[i] << ",";
    }
}

bool player::isItCreature(int index) {
    if(inplay[index]->getType()=="Creature"){
        return true;
    }
    return false;
}

//std::shared_ptr<card> player::getCardFromPile(std::string cardName) {
//    for (int i = 0; i < inplay.size(); i++) {
//        if (inplay[i]->getName()==cardName){
//            return inplay[i];
//        }
//    };
//}

void player::moveTheCardFromHandToDiscard(std::string cardName) {
    for(int i=0;i<hand.size();i++){
        if (hand[i]->getName()==cardName){
            discard.emplace_back(hand[i]);
            hand.erase(hand.begin()+i);
            break;
        }
    }
}

void player::makePlayerDestroyed() {
    isDestroyed=true;
}

void player::displayHand() {
    for(int i=0;i<hand.size();i++){
        hand[i]->displayCard();
    }
}

void player::shuffleDeck() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    shuffle(library.begin(), library.end(), rng);
}

int player::getHandSize() {
    return hand.size();
}

int player::getLibrarySize() {
    return library.size();
}

void player::makeInPlayCardsUntapped(std::shared_ptr<player> aPlayer) {
    for(int a=0;a<inplay.size();a++){
        if(inplay[a]->isItTapped()){
            inplay[a]->untapCard(aPlayer);
        }
    }
}

std::shared_ptr<card> player::getCardFromPile(std::string cardName) {
    for(int a=0;a<hand.size();a++){
        if(cardName==hand[a]->getName()){
            return hand[a];
        }
    }
}

int player::getCurrentManaSize() {
    return currentMana.size();
}

std::shared_ptr<card> player::getCardFromInplayPile(std::string cardName) {
    for(int a=0;a<inplay.size();a++){
        if(cardName==inplay[a]->getName()){
            return inplay[a];
        }
    }
}

void player::cleanCurrentMana() {
    currentMana.clear();
}

void player::newlyEnteredCreatureGetsCurrentEffects(std::shared_ptr<card> aCard,std::shared_ptr<player> opponent) {
    for(int a=0;a<inplay.size();a++){
        if (inplay[a]->getName()=="HolyWar" || inplay[a]->getName()=="UnholyWar"){
            inplay[a]->effectOnNewlyEnteredCreature(aCard);
        }
    }
    for(int i=0;i<opponent->inplay.size();i++){
        if(opponent->inplay[i]->getName()=="HolyLight" || opponent->inplay[i]->getName()=="Restrain"){
            opponent->inplay[i]->effectOnNewlyEnteredCreature(aCard);
        }
    }
    if(aCard->getHP()<=0 && aCard->getType()=="Creature"){
        moveTheCardFromHandToDiscard(aCard->getName());
        aCard->makeCreatureCardDestroyed();
        std::cout<<aCard->getName()<<" has been destroyed and moved to the discard pile!"<<std::endl;
    }
}

std::shared_ptr<card> player::getTheLastCardFromInplayPile() {
    return inplay[inplay.size()-1];
}






