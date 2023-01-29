//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pokemon.h"

using namespace std;

//-------------You Can Add Your Functions Down Below-------------//

pokemon::pokemon():name(""),hpValue(100),atkValue(0){}
pokemon::pokemon(string n ,int a){
    name=n;
    atkValue=a;
    hpValue=100;
}
pokemon::pokemon(const pokemon &p){
    name=p.name;
    hpValue=p.hpValue;
    atkValue=p.atkValue;
}
string pokemon::getName() const{
    return name;
}
int pokemon::getHP() const{
    return hpValue;
}
int pokemon::getAtk() const{
    return atkValue;
}

pokedex::pokedex():value(0){}

void pokedex::updatePokedex(const pokemon &p){
    bool exists=false;
    for(int a=0;a<value;a++){
        if(p.getName().compare(pokedexArray[a].getName())==0 && p.getHP()==pokedexArray[a].getHP() && p.getAtk()==pokedexArray[a].getAtk()){//checks if that pokemon already exists in the pokedox array
            exists=true;//if it exists, this boolean becomes true and the program exits the loop
            break;
        }
    }
    if(!exists){//if it does not exist, it adds it to the array
        pokedexArray[value]=p;
        value++;
    }
}
void pokedex::printPokedex()const{
    for(int a=0;a<value;a++){
        cout<<pokedexArray[a].getName()<<endl;
    }
}

player::player(){
    name="";
    pokemonNumber=0;
    pokeballNumber=10;
    badgeNumber=0;
    playerPokemon= pokemon();
    playerPokedex= pokedex();
}
player::player(string n,pokemon p){
    name=n;
    playerPokemon=p;
    badgeNumber=0;
    pokemonNumber=0;
    pokeballNumber=10;
    playerPokedex= pokedex();
}

int player::showPokemonNumber()const{
    return pokemonNumber;
}
int player::showPokeballNumber()const{
    return pokeballNumber;
}
int player::showBadgeNumber()const{
    return badgeNumber;
}
pokemon& player::getPokemon(){
    return playerPokemon;
}
void player::battleWon(){
    badgeNumber++;
    pokeballNumber+=3;
    playerPokemon.setHPBackTo100(); 
}
void player::catchPokemon(){
    pokemonNumber++;
    pokeballNumber--;
}
enemy::enemy(){
    name="";
    enemyPokemon=pokemon();
}
enemy::enemy(string n, pokemon p){
    name=n;
    enemyPokemon=p;
}
pokemon& enemy::getPokemon(){
    return enemyPokemon;
}
string enemy::getName() const{
    return name;
}