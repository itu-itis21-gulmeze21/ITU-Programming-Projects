//
// Created by erceg on 14.05.2021.
//

#ifndef PROJECT_CARD_H
#define PROJECT_CARD_H

#include <vector>
#include "iostream"
#include "effect.h"
#include "player.h"




class card {
protected:
    std::string nameOfTheCard;
    std::string typeOfTheCard;
    std::vector<char> manacosts;
public:
    card();
    card(std::string notc, std::string totc,std::vector<char> mc);
    virtual std::string getType();
    virtual void displayCard()=0;
    virtual std::string getName();
    virtual void play(std::shared_ptr<player> onePlayer,std::shared_ptr<player> opponent);
    virtual void tapCard();
    virtual void untapCard(std::shared_ptr<player> aPlayer);
    virtual void decraseHP(int decraselevel);
    virtual void increaseHP(int increaseLevel);
    virtual void decraseAttackPower(int decraseLevel);
    virtual void increaseAttackPower(int increaseLevel);
    virtual int getHP();
    virtual int getBaseAP();
    virtual int getAttackPower();
    virtual void controlIfCreatureIsDead();
    virtual std::string getColor();
    virtual void gainFirstStrikeAbility();
    virtual void loseFirstStrikeAbility();
    virtual void gainTrampleAbility();
    virtual void loseTrampleAbility();
    virtual bool isItDestroyed();
    virtual bool doesItHaveFirstStrike();
    virtual bool doesItHaveTrample();
    virtual void makeLandCardDestroyed();
    virtual void makeCreatureCardDestroyed();
    virtual void makeEnchantmentCardDestroyed();
    virtual void useEffect(std::shared_ptr<card> aCard);
    virtual void combatWithCreatureCard(std::shared_ptr<card> defender,std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent);
    virtual void combatWithPlayer(std::shared_ptr<player> opponent);
    //virtual void negativeEffect(std::shared_ptr<card> aCard);
    virtual bool isItTapped();
    virtual void effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard);
    virtual std::string getAffectedCreatureName();
};
class creature:public card{
protected:
    std::string colourOfTheCard;
    int attackPower;
    int HP;
    int baseAttackPower;
    int baseHP;
    bool isdestroyed;//card discard pile a gider
    bool istapped;
    bool hasTrampleAbility;
    bool hasFirstStrikeAbility;
public:
    creature(std::string notc, std::vector<char> mc,std::string c,int ap,int hp,bool hta,bool hfsa);
    void displayCard()override;
    void decraseHP(int decraselevel)override;
    void increaseHP(int increaseLevel)override;
    void decraseAttackPower(int decraseLevel)override;
    void increaseAttackPower(int increaseLevel)override;
    int getHP()override;
    int getAttackPower()override;
    void controlIfCreatureIsDead()override;
    std::string getColor()override;
    void gainFirstStrikeAbility()override;
    void loseFirstStrikeAbility()override;
    void gainTrampleAbility()override;
    void loseTrampleAbility()override;
    bool isItDestroyed()override;
    bool doesItHaveFirstStrike()override;
    bool doesItHaveTrample()override;
    std::string getType()override;
    void play(std::shared_ptr<player> onePlayer,std::shared_ptr<player> opponent)override;
    void tapCard()override;
    void untapCard(std::shared_ptr<player> aPlayer)override;
    void makeCreatureCardDestroyed()override;
    void combatWithCreatureCard(std::shared_ptr<card> defender,std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
    void combatWithPlayer(std::shared_ptr<player> opponent)override;
    bool isItTapped()override;
    int getBaseAP()override;
};
class land:public card{
protected:
    bool istapped;
    char manaValue;
    bool isDestroyed;
public:
    land(std::string notc,char mv);
    char getManaValue();
    void makeLandCardDestroyed()override;
    void displayCard()override;
    std::string getType()override;
    void play(std::shared_ptr<player> onePlayer,std::shared_ptr<player> opponent)override;
    void tapCard()override;
    void untapCard(std::shared_ptr<player> aPlayer)override;
    bool isItTapped()override;
};
class enchantment:public card{
protected:
    std::string color;
    bool isDestroyed;
public:
    enchantment(std::string notc,std::vector<char> mc, std::string c,bool id);
    void displayCard()override;
    std::string getType()override;
    void makeEnchantmentCardDestroyed()override;
    bool isItDestroyed()override;
    void tapCard()override;
};
class Rage:public enchantment{
protected:
    creatureGetsTrample cardEffect;
    std::string affectedCreatureName;
public:
    Rage(std::vector<char> mc,creatureGetsTrample ce);
    creatureGetsTrample getTrampleAbility();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> oneplayer ,std::shared_ptr<player> opponent)override;
    std::string getAffectedCreatureName()override;
};
class HolyWar:public enchantment{
protected:
    allOfWhiteCreaturesGet1 cardEffect;
public:
    HolyWar(std::vector<char> mc, allOfWhiteCreaturesGet1 ce);
    allOfWhiteCreaturesGet1 getCreaturesPlusOne();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
    //void negativeEffect(std::shared_ptr<card> aCard)override;
    void effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard)override;
};

class HolyLight: public enchantment{
protected:
    allOfBlackCreaturesLose1 cardEffect;
public:
    HolyLight(std::vector<char> mc, allOfBlackCreaturesLose1 ce);
    allOfBlackCreaturesLose1 getCreaturesMinusOne();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;//creature ın destroyed olup olmadıgına bak.
    //void negativeEffect(std::shared_ptr<card> aCard)override;
    void effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard)override;
};

class UnholyWar: public enchantment{
protected:
    allOfBlackCreaturesGet2Attack cardEffect;
public:
    UnholyWar(std::vector<char> mc, allOfBlackCreaturesGet2Attack ce);
    allOfBlackCreaturesGet2Attack getCreaturesPlusTwo();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
    //void negativeEffect(std::shared_ptr<card> aCard)override;
    void effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard)override;
};

class Restrain: public enchantment{
protected:
    allOfGreenCreaturesLoseTrample cardEffect;
public:
    Restrain(std::vector<char> mc, allOfGreenCreaturesLoseTrample ce);
    allOfGreenCreaturesLoseTrample getColorLosesTrample();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
    //void negativeEffect(std::shared_ptr<card> aCard)override;
    void effectOnNewlyEnteredCreature(std::shared_ptr<card> aCard)override;
};

class Slow: public enchantment {
protected:
    creatureLosesFirstStrike cardEffect;
    std::string affectedCreatureName;
public:
    Slow(std::vector<char> mc, creatureLosesFirstStrike ce);

    creatureLosesFirstStrike getSlowed();

    void useEffect(std::shared_ptr<card> aCard) override;

    void play(std::shared_ptr<player> aPlayer, std::shared_ptr<player> opponent) override;

    std::string getAffectedCreatureName() override;
    //void negativeEffect(std::shared_ptr<card> aCard)override;
};
class sorcery:public card{
protected:
    std::string color;
public:
    sorcery(std::string notc,std::vector<char> mc, std::string c);
    void displayCard()override;
    std::string getType()override;
    void tapCard()override;
};
class Disenchant:public sorcery{
protected:
    destroyEnchantmentEffect cardEffect;
public:
    Disenchant( std::vector<char> mc, destroyEnchantmentEffect ce);
    destroyEnchantmentEffect getDestroyEnchantment();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
};
class Flood:public sorcery{
protected:
    destroyLandEffect cardEffect;
public:
    Flood( std::vector<char> mc, destroyLandEffect ce);
    destroyLandEffect getDestroyLand();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
};
class Plague:public sorcery{
protected:
    dealDamageToCreatures cardEffect;
public:
    Plague( std::vector<char> mc,  dealDamageToCreatures ce);
    dealDamageToCreatures getDealDamageToCreatures();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
};
class Terror:public sorcery{
protected:
    destroyCreatureEffect cardEffect;
public:
    Terror( std::vector<char> mc, destroyCreatureEffect ce);
    destroyCreatureEffect getDestroyCreature();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
};
class LigthningBolt:public sorcery{
protected:
    dealDamageToCreatures cardEffect;
    deal2DamageToPlayer cardEffect2;
public:
    LigthningBolt(std::vector<char> mc, dealDamageToCreatures ce,deal2DamageToPlayer d2tp);
    dealDamageToCreatures getDealDamageToCreatures();
    deal2DamageToPlayer getDeal2DamageToPlayer();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
};
class Reanimate:public sorcery{
protected:
    returnOneCardFromDiscardToHand cardEffect;
public:
    Reanimate( std::vector<char> mc,returnOneCardFromDiscardToHand rocfdth);
    returnOneCardFromDiscardToHand getReturnOneCardEffect();
    void useEffect(std::shared_ptr<card> aCard)override;
    void play(std::shared_ptr<player> aPlayer,std::shared_ptr<player> opponent)override;
};
#endif //PROJECT_CARD_H
