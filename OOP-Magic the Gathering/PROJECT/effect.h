//
// Created by erceg on 14.05.2021.
//

#ifndef PROJECT_EFFECT_H
#define PROJECT_EFFECT_H
#include "iostream"
//#include "card.h"  //bunun yerine class card yazıp eklememiz gerekiyor
#include "vector"
#include "memory"

class card;
class creature;
class land;
class enchantment;
class sorcery;
class player;

class effect {
protected:
    std::string nameOfTheEffect;
public:
    effect();
    effect(std::string note);
};
class destroyCreatureEffect:public effect{
public:
    destroyCreatureEffect(std::string note);
    void destroyCreature(std::shared_ptr<card> creatureCard);
};
class destroyLandEffect:public effect{
public:
    destroyLandEffect(std::string note);
    void destroyLand(std::shared_ptr<card> landCard);
};
class allOfWhiteCreaturesGet1: public effect{
public:
    allOfWhiteCreaturesGet1(std::string note);
    void creaturesget1(std::shared_ptr<card> creaturecards);
};
class allOfBlackCreaturesLose1: public effect{
public:
    allOfBlackCreaturesLose1(std::string note);
    void creatureslose1(std::shared_ptr<card> creaturecards);
};
class creatureGetsFirstStrike:public effect{
public:
    creatureGetsFirstStrike(std::string note);
    void getFirstStrike(std::shared_ptr<card> creatureCard);
};
class creatureLosesFirstStrike:public effect{
public:
    creatureLosesFirstStrike(std::string note);
    void loseFirstStrike(std::shared_ptr<card> creatureCard);
};
class creatureGetsTrample:public effect{
public:
    creatureGetsTrample(std::string note);
    void getTrample(std::shared_ptr<card> creatureCard);
};
class creatureLosesTrample:public effect{
public:
    creatureLosesTrample(std::string note);
    void loseTrample(std::shared_ptr<card> creatureCard);
};
class allOfGreenCreaturesLoseTrample: public effect{
public:
    allOfGreenCreaturesLoseTrample(std::string note);
    void thisColorLosesTrample(std::shared_ptr<card> creatureCards);
};
class dealDamageToCreatures:public effect{
public:
    dealDamageToCreatures(std::string note);
    void dealDamage(std::shared_ptr<card> creatureCard);
};
class allOfBlackCreaturesGet2Attack: public effect{
public:
    allOfBlackCreaturesGet2Attack(std::string note);
    void creaturesget2(std::shared_ptr<card> creaturecards);
};
class destroyEnchantmentEffect: public effect{
public:
    destroyEnchantmentEffect(std::string note);
    void destroyTheEnchantmentCard(std::shared_ptr<card> enchantmentCard);
};
class deal2DamageToPlayer:public effect{
public:
    deal2DamageToPlayer(std::string note);
    void damageToPlayer(std::shared_ptr<player> onePlayer);
};
class returnOneCardFromDiscardToHand:public effect{
public:
    returnOneCardFromDiscardToHand(std::string note);
    void returnCard(std::shared_ptr<player> aPlayer,std::shared_ptr<card> aCard);
};
#endif //PROJECT_EFFECT_H
