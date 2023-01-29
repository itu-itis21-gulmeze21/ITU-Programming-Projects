//
// Created by erceg on 14.05.2021.
//

#include "effect.h"
#include "card.h"
#include "player.h"

effect::effect(std::string note):nameOfTheEffect(note) {}

effect::effect():nameOfTheEffect(" ") {
}
void destroyCreatureEffect::destroyCreature(std::shared_ptr<card> creatureCard) {
    int health=creatureCard->getHP();
    creatureCard->decraseHP(health);
    creatureCard->controlIfCreatureIsDead();
}
destroyCreatureEffect::destroyCreatureEffect(std::string note) : effect(note) {
}
void destroyLandEffect::destroyLand(std::shared_ptr<card> landCard) {
    landCard->makeLandCardDestroyed();
}

destroyLandEffect::destroyLandEffect(std::string note) : effect(note) {
}
//vectorden emin degilim, creaturelara tek tek bakıyor rengi girilen renkte ise ozellikleri 1 arttırıyor  bunu kullanırken destedeki kartların typelarına bakıp creature olanlara kullanıcaz
void allOfWhiteCreaturesGet1::creaturesget1(std::shared_ptr<card> creaturecards) {
    if(creaturecards->getColor()=="White"){
        creaturecards->increaseAttackPower(1);
        creaturecards->increaseHP(1);
    }
}
allOfWhiteCreaturesGet1::allOfWhiteCreaturesGet1(std::string note) : effect(note) {
}
allOfBlackCreaturesLose1::allOfBlackCreaturesLose1(std::string note) : effect(note) {
}
//vectorden emin degilim, creaturelara tek tek bakıyor rengi girilen renkte ise ozellikleri 1 azaltıyor   bunu kullanırken destedeki kartların typelarına bakıp creature olanlara kullanıcaz
void allOfBlackCreaturesLose1::creatureslose1(std::shared_ptr<card> creaturecards) {
    if(creaturecards->getColor()=="Black"){
        creaturecards->decraseAttackPower(1);
        creaturecards->decraseHP(1);
    }
}
creatureGetsFirstStrike::creatureGetsFirstStrike(std::string note) : effect(note) {
}
// hasfirststrike=true
void creatureGetsFirstStrike::getFirstStrike(std::shared_ptr<card> creatureCard) {
    creatureCard->gainFirstStrikeAbility();
}
creatureLosesFirstStrike::creatureLosesFirstStrike(std::string note) : effect(note) {
}
// hasfirststrike=false
void creatureLosesFirstStrike::loseFirstStrike(std::shared_ptr<card> creatureCard) {
    creatureCard->loseFirstStrikeAbility();
}

creatureGetsTrample::creatureGetsTrample(std::string note) : effect(note) {
}
// hastrample=true
void creatureGetsTrample::getTrample(std::shared_ptr<card> creatureCard) {//template i card yap, card base'ine getTrample ekle creature hariç diğer classlarda bir şey yapmasın.
    creatureCard->gainTrampleAbility();
}

creatureLosesTrample::creatureLosesTrample(std::string note) : effect(note) {
}
// hastrample=false
void creatureLosesTrample::loseTrample(std::shared_ptr<card> creatureCard) {
    creatureCard->loseTrampleAbility();
}
allOfGreenCreaturesLoseTrample::allOfGreenCreaturesLoseTrample(std::string note) : effect(note) {
}

void allOfGreenCreaturesLoseTrample::thisColorLosesTrample(std::shared_ptr<card> creatureCards) {
    if(creatureCards->getColor()=="Green"){
        creatureCards->loseTrampleAbility();
    }
}

dealDamageToCreatures::dealDamageToCreatures(std::string note) : effect(note) {
}

void dealDamageToCreatures::dealDamage(std::shared_ptr<card> creatureCard) {
    creatureCard->decraseHP(1);
}
void allOfBlackCreaturesGet2Attack::creaturesget2(std::shared_ptr<card> creaturecards) {
    if(creaturecards->getColor()=="Black"){
        creaturecards->increaseAttackPower(2);
    }
}
allOfBlackCreaturesGet2Attack::allOfBlackCreaturesGet2Attack(std::string note) : effect(note) {
}

destroyEnchantmentEffect::destroyEnchantmentEffect(std::string note) : effect(note) {
}

void destroyEnchantmentEffect::destroyTheEnchantmentCard(std::shared_ptr<card> enchantmentCard) {
    enchantmentCard->makeEnchantmentCardDestroyed();
}

deal2DamageToPlayer::deal2DamageToPlayer(std::string note) : effect(note) {
}

void deal2DamageToPlayer::damageToPlayer(std::shared_ptr<player> onePlayer) {
    onePlayer->changeHp(-2);
}

returnOneCardFromDiscardToHand::returnOneCardFromDiscardToHand(std::string note) : effect(note) {
}

void returnOneCardFromDiscardToHand::returnCard(std::shared_ptr<player> aPlayer,std::shared_ptr<card> aCard) {
    aPlayer->moveTheCardFromDiscardToHand(aCard);
}