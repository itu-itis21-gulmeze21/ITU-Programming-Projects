#include <iostream>
#include <vector>
#include "card.h"
#include "effect.h"
#include "player.h"
#include <algorithm>


int main() {
    std::vector<char> soldiermanas={'W'};
    std::vector<char> pegasusmanas={'1','W'};
    std::vector<char> whiteknightmanas={'W','W'};
    std::vector<char> angrybearmanas={'2','G'};
    std::vector<char> guardmanas={'2','W','W'};
    std::vector<char> werewolfmanas={'2','G','W'};
    std::vector<char> skeletonManas={'B'};
    std::vector<char> ghostManas={'1','B'};
    std::vector<char> blackknightManas={'B','B'};
    std::vector<char> orcmaniacMAnas={'2','R'};
    std::vector<char> hobgoblinManas={'1','R','B'};
    std::vector<char> vampireManas={'3','B'};
    std::vector<char> reanimateManas={'B'};
    std::vector<char> disenchantManas={'1','B'};
    std::vector<char> lightningboltManas={'1','G'};
    std::vector<char> floodManas={'1','G','W'};
    std::vector<char> plagueManas={'2','B'};
    std::vector<char> terrorManas={'1','B'};
    std::vector<char> rageManas={'G'};
    std::vector<char> HolyWarManas={'1','W'};
    std::vector<char> HolyLightManas={'1','W'};
    std::vector<char> UnholyWarManas={'1','B'};
    std::vector<char> RestrainManas={'2','R'};
    std::vector<char> SlowManas={'B'};


    returnOneCardFromDiscardToHand reanimateEffect("Reanimate Effect");
    destroyEnchantmentEffect disenchantEffect("Disenchant Effect");
    dealDamageToCreatures lightningboltEffect1("Lightning Bolt Effect");
    deal2DamageToPlayer lightningboltEffect2("Lightning Bolt Effect");
    destroyLandEffect floodEffect("Flood Effect");
    dealDamageToCreatures plagueEffect("Plague Effect");
    destroyCreatureEffect terrorEffect("Terror Effect");
    creatureGetsTrample rageEffect("Rage Effect");
    allOfWhiteCreaturesGet1 holywarEffect("Holy War Effect");
    allOfBlackCreaturesLose1 holylightEffect("Holy Light Effect");
    allOfBlackCreaturesGet2Attack unholywarEffect("Unholy War Effect");
    allOfGreenCreaturesLoseTrample restrainEffect("Restrain Effect");
    creatureLosesFirstStrike slowEffect("Slow Effect");


    //Player 1 lines

    // Lands
    std::shared_ptr<land> plain1=std::make_shared<land>("Plains", 'W');
    std::shared_ptr<land> plain2=std::make_shared<land>("Plains", 'W');
    std::shared_ptr<land> plain3=std::make_shared<land>("Plains", 'W');
    std::shared_ptr<land> plain4=std::make_shared<land>("Plains", 'W');
    std::shared_ptr<land> plain5=std::make_shared<land>("Plains", 'W');
    std::shared_ptr<land> forest1=std::make_shared<land>("Forest",'G');
    std::shared_ptr<land> forest2=std::make_shared<land>("Forest",'G');
    std::shared_ptr<land> forest3=std::make_shared<land>("Forest",'G');
    std::shared_ptr<land> islandp1=std::make_shared<land>("Island",'L');

    //Creatures
    std::shared_ptr<creature> soldier1=std::make_shared<creature>("Soldier",soldiermanas,"White",1,1,false,false);
    std::shared_ptr<creature> soldier2=std::make_shared<creature>("Soldier",soldiermanas,"White",1,1,false,false);
    std::shared_ptr<creature> soldier3=std::make_shared<creature>("Soldier",soldiermanas,"White",1,1,false,false);
    std::shared_ptr<creature> armoredPegasus1=std::make_shared<creature>("ArmoredPegasus",pegasusmanas,"White",1,2,false,false);
    std::shared_ptr<creature> armoredPegasus2=std::make_shared<creature>("ArmoredPegasus",pegasusmanas,"White",1,2,false,false);
    std::shared_ptr<creature> whiteKnight1=std::make_shared<creature>("WhiteKnight",whiteknightmanas,"White",2,2,false,true);
    std::shared_ptr<creature> whiteKnight2=std::make_shared<creature>("WhiteKnight",whiteknightmanas,"White",2,2,false,true);
    std::shared_ptr<creature> angryBear1=std::make_shared<creature>("AngryBear",angrybearmanas,"Green",3,2,true,false);
    std::shared_ptr<creature> guard1=std::make_shared<creature>("Guard",guardmanas,"White",2,5,false,false);
    std::shared_ptr<creature> werewolf1=std::make_shared<creature>("Werewolf",werewolfmanas,"Green",4,6,true,false);


    //Sorceries
    std::shared_ptr<Disenchant> disenchant1=std::make_shared<Disenchant>(disenchantManas,disenchantEffect);
    std::shared_ptr<LigthningBolt> lightningBolt1=std::make_shared<LigthningBolt>(lightningboltManas,lightningboltEffect1,lightningboltEffect2);
    std::shared_ptr<Flood> flood1=std::make_shared<Flood>(floodManas,floodEffect);
    std::shared_ptr<Flood> flood2=std::make_shared<Flood>(floodManas,floodEffect);


    //Enchantments
    std::shared_ptr<Rage> rage1=std::make_shared<Rage>(rageManas, rageEffect);
    std::shared_ptr<HolyWar> holywar1=std::make_shared<HolyWar>(HolyWarManas, holywarEffect);
    std::shared_ptr<HolyLight> holylight1=std::make_shared<HolyLight>(HolyLightManas, holylightEffect);


    //Player 1 deck placement
    std::vector<std::shared_ptr<card>> Player1Cards;
    Player1Cards.emplace_back(plain1);
    Player1Cards.emplace_back(plain2);
    Player1Cards.emplace_back(plain3);
    Player1Cards.emplace_back(plain4);
    Player1Cards.emplace_back(plain5);
    Player1Cards.emplace_back(forest1);
    Player1Cards.emplace_back(forest2);
    Player1Cards.emplace_back(forest3);
    Player1Cards.emplace_back(islandp1);
    Player1Cards.emplace_back(soldier1);
    Player1Cards.emplace_back(soldier2);
    Player1Cards.emplace_back(soldier3);
    Player1Cards.emplace_back(armoredPegasus1);
    Player1Cards.emplace_back(armoredPegasus2);
    Player1Cards.emplace_back(whiteKnight1);
    Player1Cards.emplace_back(whiteKnight2);
    Player1Cards.emplace_back(angryBear1);
    Player1Cards.emplace_back(guard1);
    Player1Cards.emplace_back(werewolf1);
    Player1Cards.emplace_back(disenchant1);
    Player1Cards.emplace_back(lightningBolt1);
    Player1Cards.emplace_back(flood1);
    Player1Cards.emplace_back(flood2);
    Player1Cards.emplace_back(rage1);
    Player1Cards.emplace_back(holywar1);
    Player1Cards.emplace_back(holylight1);

    //Player 2 lines

    //Lands
    std::shared_ptr<land> swamp1=std::make_shared<land>("Swamp",'B');
    std::shared_ptr<land> swamp2=std::make_shared<land>("Swamp",'B');
    std::shared_ptr<land> swamp3=std::make_shared<land>("Swamp",'B');
    std::shared_ptr<land> swamp4=std::make_shared<land>("Swamp",'B');
    std::shared_ptr<land> swamp5=std::make_shared<land>("Swamp",'B');
    std::shared_ptr<land> mountain1=std::make_shared<land>("Mountain",'R');
    std::shared_ptr<land> mountain2=std::make_shared<land>("Mountain",'R');
    std::shared_ptr<land> mountain3=std::make_shared<land>("Mountain",'R');
    std::shared_ptr<land> island1=std::make_shared<land>("Island",'L');


    //Creatures
    std::shared_ptr<creature> skeleton1=std::make_shared<creature>("Skeleton",skeletonManas,"Black",1,1, false, false);
    std::shared_ptr<creature> skeleton2=std::make_shared<creature>("Skeleton",skeletonManas,"Black",1,1, false, false);
    std::shared_ptr<creature> skeleton3=std::make_shared<creature>("Skeleton",skeletonManas,"Black",1,1, false, false);
    std::shared_ptr<creature> ghost1=std::make_shared<creature>("Ghost",ghostManas,"Black",2,1, false, false);
    std::shared_ptr<creature> ghost2=std::make_shared<creature>("Ghost",ghostManas,"Black",2,1, false, false);
    std::shared_ptr<creature> blackknight1=std::make_shared<creature>("BlackKnight",blackknightManas,"Black",2,2, false,true);
    std::shared_ptr<creature> blackknight2=std::make_shared<creature>("BlackKnight",blackknightManas,"Black",2,2, false,true);
    std::shared_ptr<creature> orcmaniac1=std::make_shared<creature>("OrcManiac",orcmaniacMAnas,"Red",4,1, false,false);
    std::shared_ptr<creature> hobgoblin1=std::make_shared<creature>("Hobgoblin",hobgoblinManas,"Red",3,3, false,false);
    std::shared_ptr<creature> vampire1=std::make_shared<creature>("Vampire",vampireManas,"Black",6,3, false,false);


    //Sorceries
    std::shared_ptr<Reanimate> reanimate1=std::make_shared<Reanimate>(reanimateManas,reanimateEffect);
    std::shared_ptr<Plague> plague1=std::make_shared<Plague>(plagueManas,plagueEffect);
    std::shared_ptr<Terror> terror1=std::make_shared<Terror>(terrorManas, terrorEffect);
    std::shared_ptr<Terror> terror2=std::make_shared<Terror>(terrorManas, terrorEffect);


    //Enchantments
    std::shared_ptr<UnholyWar> unholyWar1=std::make_shared<UnholyWar>(UnholyWarManas, unholywarEffect);
    std::shared_ptr<Restrain>  restrain1=std::make_shared<Restrain>(RestrainManas, restrainEffect);
    std::shared_ptr<Slow> slow1=std::make_shared<Slow>(SlowManas, slowEffect);


    //Player 2 deck placement
    std::vector<std::shared_ptr<card>> Player2Cards;
    Player2Cards.emplace_back(swamp1);
    Player2Cards.emplace_back(swamp2);
    Player2Cards.emplace_back(swamp3);
    Player2Cards.emplace_back(swamp4);
    Player2Cards.emplace_back(swamp5);
    Player2Cards.emplace_back(mountain1);
    Player2Cards.emplace_back(mountain2);
    Player2Cards.emplace_back(mountain3);
    Player2Cards.emplace_back(island1);
    Player2Cards.emplace_back(skeleton1);
    Player2Cards.emplace_back(skeleton2);
    Player2Cards.emplace_back(skeleton3);
    Player2Cards.emplace_back(ghost1);
    Player2Cards.emplace_back(ghost2);
    Player2Cards.emplace_back(blackknight1);
    Player2Cards.emplace_back(blackknight2);
    Player2Cards.emplace_back(orcmaniac1);
    Player2Cards.emplace_back(hobgoblin1);
    Player2Cards.emplace_back(vampire1);
    Player2Cards.emplace_back(reanimate1);
    Player2Cards.emplace_back(plague1);
    Player2Cards.emplace_back(terror1);
    Player2Cards.emplace_back(terror2);
    Player2Cards.emplace_back(unholyWar1);
    Player2Cards.emplace_back(restrain1);
    Player2Cards.emplace_back(slow1);

    //players
    std::shared_ptr<player> player1=std::make_shared<player>(1,Player1Cards);
    std::shared_ptr<player> player2=std::make_shared<player>(2,Player2Cards);
    player1->shuffleDeck();
    player2->shuffleDeck();

    //GAME BEGINS
    std::cout<<"Welcome to a game of Magic:The Gathering!"<<std::endl;
    std::cout<<"!!!While playing the game make sure you give the right input. Enter all the card names starting with a capital letter!!!"<<std::endl;
    std::cout<<"!!!If you don't want to play a card in any phases, please write 'pass'!!!"<<std::endl;
    std::cout<<"!!!If you want to play a card that has more than one words in its name, don't put a space between words.(White Knight=WhiteKnight)"<<std::endl;
    std::cout<<"Enjoy the game!"<<std::endl;
    player1->moveTheCardFromLibraryToHand();
    player1->moveTheCardFromLibraryToHand();
    player1->moveTheCardFromLibraryToHand();
    player1->moveTheCardFromLibraryToHand();
    player1->moveTheCardFromLibraryToHand();
    player2->moveTheCardFromLibraryToHand();
    player2->moveTheCardFromLibraryToHand();
    player2->moveTheCardFromLibraryToHand();
    player2->moveTheCardFromLibraryToHand();
    player2->moveTheCardFromLibraryToHand();

    int roundNumber=1;//loop un sonunda increment et

    while(player1->getHp()>0 && player2->getHp()>0){
        //draw card phase
        if (roundNumber>1 && player1->getHandSize()<7 && player1->getLibrarySize()>0){
            player1->moveTheCardFromLibraryToHand();
        }
        //untap phase
        for(int a=0;a<player1->getInPlaySize();a++){
            player1->makeInPlayCardsUntapped(player1);
        }
        std::cout<<"           -ROUND "<<roundNumber<<"-"<<std::endl;
        std::cout<<"Player1's Turn:"<<std::endl;
        std::cout<<"Player1's cards in play: ";
        player1->displayInPlay();
        std::cout<<std::endl;
        std::cout<<"Player2's cards in play: ";
        player2->displayInPlay();
        std::cout<<std::endl;
        std::cout<<"Player1's cards in hand: ";
        player1->displayHand();
        std::cout<<std::endl;
        std::cout<<"Player2's cards in hand: ";
        player2->displayHand();
        std::cout<<std::endl;
        std::cout<<"HP of Player1: "<<player1->getHp()<<std::endl;
        std::cout<<"HP of Player2: "<<player2->getHp()<<std::endl;
        std::cout<<"FIRST PLAY PHASE!"<<std::endl;
        std::cout<<"Player1, please enter the name of the land card you want to play: "<<std::endl;
        std::string choice;
        std::cin>>choice;
        if(choice!="pass"){
            player1->getCardFromPile(choice)->play(player1,player2);
        }
        std::cout<<"Now you have these manas: ";
        player1->displayCurrentMana();
        std::cout<<std::endl;
        while(player1->getCurrentManaSize()!=0){
            std::cout<<"Which non-land card do you want to play with your current mana?"<<std::endl;
            std::cin>>choice;
            if(choice!="pass"){
                player1->getCardFromPile(choice)->play(player1,player2);
                player1->newlyEnteredCreatureGetsCurrentEffects(player1->getTheLastCardFromInplayPile(),player2);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
                std::cout<<"Now you have these manas: ";
                player1->displayCurrentMana();
                std::cout<<std::endl;
            }
            else{
                break;
            }
        }
        if(player2->getHp()<=0 || player1->getHp()<=0){
            break;
        }
        //combat
        std::cout<<"COMBAT TIME!"<<std::endl;
        std::cout<<"Player 1, enter the number of creatures you want to use to attack: "<<std::endl;
        int count;
        std::cin>>count;
        for(int a=0;a<count;a++){
            std::cout<<"Player 1,enter the creature you want to attack with!"<<std::endl;
            std::string attacker;
            std::cin>>attacker;
            std::cout<<"Player 2,enter the creature you want to defend with or enter 'player' to take the damage to yourself!"<<std::endl;
            std::string choice3;
            std::cin>>choice3;
            if(choice3=="player"){
                player1->getCardFromInplayPile(attacker)->combatWithPlayer(player2);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
            }
            else{
                player1->getCardFromInplayPile(attacker)->combatWithCreatureCard(player2->getCardFromInplayPile(choice3),player1,player2);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
            }
        }
        if(player2->getHp()<=0 || player1->getHp()<=0){
            break;
        }
        //2. play phase
        std::cout<<"SECOND PLAY PHASE!"<<std::endl;
        std::cout<<"Player 1, if you haven't played a land card in this turn, you can enter the land you want to play!"<<std::endl;
        std::cout<<"If you have played a land card before or you don't want to play a Land card right now, enter 'pass'!"<<std::endl;
        std::string choice4;
        std::cin>>choice4;
        if(choice4!="pass"){
            player1->getCardFromPile(choice4)->play(player1,player2);
        }
        std::cout<<"Now you have these manas: ";
        player1->displayCurrentMana();
        std::cout<<std::endl;
        while(player1->getCurrentManaSize()!=0){
            std::cout<<"Which non-land card do you want to play with your current mana?"<<std::endl;
            std::cin>>choice;
            if(choice!="pass"){
                player1->getCardFromPile(choice)->play(player1,player2);
                player1->newlyEnteredCreatureGetsCurrentEffects(player1->getTheLastCardFromInplayPile(),player2);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
                std::cout<<"Now you have these manas: ";
                player1->displayCurrentMana();
                std::cout<<std::endl;
            }
            else{
                break;
            }
        }
        if(player2->getHp()<=0 || player1->getHp()<=0){
            break;
        }
        //end phase
        std::cout<<"END PHASE!"<<std::endl;
        player1->displayCurrentMana();
        std::cout<<std::endl;
        //2. oyuncu turn birebir aynısı
        if (roundNumber>1 && player2->getHandSize()<7 && player2->getLibrarySize()>0){
            player2->moveTheCardFromLibraryToHand();
        }
        //untap phase
        for(int a=0;a<player1->getInPlaySize();a++){
            player2->makeInPlayCardsUntapped(player2);
        }
        std::cout<<"Player2's Turn:"<<std::endl;
        std::cout<<"Player2's cards in play: ";
        player2->displayInPlay();
        std::cout<<std::endl;
        std::cout<<"Player1's cards in play: ";
        player1->displayInPlay();
        std::cout<<std::endl;
        std::cout<<"Player2's cards in hand: ";
        player2->displayHand();
        std::cout<<std::endl;
        std::cout<<"Player1's cards in hand: ";
        player1->displayHand();
        std::cout<<std::endl;
        std::cout<<"HP of Player1: "<<player1->getHp()<<std::endl;
        std::cout<<"HP of Player2: "<<player2->getHp()<<std::endl;
        std::cout<<"Player2, please enter the name of the land card you want to play: "<<std::endl;
        std::string player2choice;
        std::cin>>player2choice;
        if(player2choice!="pass"){
            player2->getCardFromPile(player2choice)->play(player2,player1);
        }
        std::cout<<"Now you have these manas: ";
        player2->displayCurrentMana();
        std::cout<<std::endl;
        while(player2->getCurrentManaSize()!=0){
            std::cout<<"Which non-land card do you want to play with your current mana?"<<std::endl;
            std::cin>>player2choice;
            if(player2choice!="pass"){
                player2->getCardFromPile(player2choice)->play(player2,player1);
                player2->newlyEnteredCreatureGetsCurrentEffects(player2->getTheLastCardFromInplayPile(),player1);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
                std::cout<<"Now you have these manas: ";
                player2->displayCurrentMana();
                std::cout<<std::endl;
            }
            else{
                break;
            }
        }
        if(player2->getHp()<=0 || player1->getHp()<=0){
            break;
        }
        //combat
        std::cout<<"COMBAT TIME!"<<std::endl;
        std::cout<<"Player 2, enter the number of creatures you want to use to attack: "<<std::endl;
        int player2count;
        std::cin>>player2count;
        for(int a=0;a<player2count;a++){
            std::cout<<"Player 2,enter the creature you want to attack with!"<<std::endl;
            std::string attacker;
            std::cin>>attacker;
            std::cout<<"Player 1,enter the creature you want to defend with or enter 'player' to take the damage to yourself!"<<std::endl;
            std::string choice3;
            std::cin>>choice3;
            if(choice3=="player"){
                player2->getCardFromInplayPile(attacker)->combatWithPlayer(player1);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
            }
            else{
                player2->getCardFromInplayPile(attacker)->combatWithCreatureCard(player1->getCardFromInplayPile(choice3),player2,player1);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
            }
        }
        if(player2->getHp()<=0 || player1->getHp()<=0){
            break;
        }
        //2. play phase
        std::cout<<"SECOND PLAY PHASE!"<<std::endl;
        std::cout<<"Player 2, if you haven't played a land card in this turn, you can enter the land you want to play!"<<std::endl;
        std::cout<<"If you have played a land card before or you don't want to play a Land card right now, enter 'pass'!"<<std::endl;
        std::string choice5;
        std::cin>>choice5;
        if(choice5!="pass"){
            player2->getCardFromPile(choice5)->play(player2,player1);
        }
        std::cout<<"Now you have these manas: ";
        player2->displayCurrentMana();
        std::cout<<std::endl;
        while(player2->getCurrentManaSize()!=0){
            std::cout<<"Which non-land card do you want to play with your current mana?"<<std::endl;
            std::cin>>player2choice;
            if(player2choice!="pass"){
                player2->getCardFromPile(player2choice)->play(player2,player1);
                player2->newlyEnteredCreatureGetsCurrentEffects(player2->getTheLastCardFromInplayPile(),player1);
                if(player2->getHp()<=0 || player1->getHp()<=0){
                    break;
                }
                std::cout<<"Now you have these manas: ";
                player2->displayCurrentMana();
                std::cout<<std::endl;
            }
            else{
                break;
            }
        }
        if(player2->getHp()<=0 || player1->getHp()<=0){
            break;
        }
        //end phase
        std::cout<<"END PHASE!"<<std::endl;
        player2->displayCurrentMana();
        std::cout<<std::endl;
        std::cout<<"END OF ROUND "<<roundNumber<<"!"<<std::endl;
        roundNumber++;
    }
    std::cout<<"Player1's HP:"<<player1->getHp()<<std::endl;
    std::cout<<"Player2's HP:"<<player2->getHp()<<std::endl;
    return 0;
}
