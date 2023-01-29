//
// Created by erceg on 15.05.2021.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include "iostream"
#include "vector"
#include "memory"
#include <algorithm>

class card;
class creature;
class land;
class enchantment;
class sorcery;


class player {
protected:
    friend class Rage;
    friend class creature;
    friend class HolyWar;
    friend class HolyLight;
    friend class Restrain;
    friend class UnholyWar;
    friend class Slow;
    friend class returnOneCardFromDiscardToHand;
    friend class Reanimate;
    friend class LigthningBolt;
    friend class Disenchant;
    friend class Flood;
    friend class Plague;
    friend class Terror;
    friend class land;
    friend class enchantment;
    int playerNumber;
    int HP;
    int currentCardInHand;
    bool isDestroyed;
    std::vector<char> currentMana;
    std::vector<std::shared_ptr<card>> library;
    std::vector<std::shared_ptr<card>> hand;
    std::vector<std::shared_ptr<card>> inplay;
    std::vector<std::shared_ptr<card>> discard;
public:
    player(int num,std::vector<std::shared_ptr<card>> deck);
    void moveTheCardFromLibraryToHand();
    void moveTheCardFromHandToInplay(std::string cardName);
    void moveTheCardFromInplayToDiscard(std::string cardName);
    void moveTheCardFromHandToDiscard(std::string cardName);
    void moveTheCardFromDiscardToHand(std::shared_ptr<card> aCard);
    void addMana(char value);
    void tapCard(std::string cardName);
    void displayInPlay();
    void displayHand();
    void displayCurrentMana();
    void shuffleDeck();
    int getInPlaySize();
    void setNum(int newNum);
    int getHp();
    void setHp(int num);
    void changeHp(int change);
    int getNum();
    void deleteManaFromCurrentMana(char ch);
    bool isItCreature(int index);
    std::shared_ptr<card> getCardFromPile(std::string cardName);
    std::shared_ptr<card> getCardFromInplayPile(std::string cardName);
    void makePlayerDestroyed();
    int getHandSize();
    int getLibrarySize();
    void makeInPlayCardsUntapped(std::shared_ptr<player> aPlayer);
    int getCurrentManaSize();
    void cleanCurrentMana();
    void newlyEnteredCreatureGetsCurrentEffects(std::shared_ptr<card> aCard,std::shared_ptr<player> opponent);
    std::shared_ptr<card> getTheLastCardFromInplayPile();
};


#endif //PROJECT_PLAYER_H
