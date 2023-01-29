//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

#ifndef _H
#define _H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//-------------Do Not Add Any New Class(es)-------------//

class pokemon{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        int hpValue;
        int atkValue;
    public:
        pokemon();
        pokemon(string,int);
        pokemon(const pokemon &);
        string getName() const;
        int getHP() const;
        int getAtk() const;
        void setHPBackTo100(){//extra function to set the hp back to 100 after the fight
            hpValue=100;
        }
        void getDamage(int damage){//extra function to decrease the pokemon's health during the fight
            hpValue-=damage;
        }
};

class pokedex{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        pokemon pokedexArray[100];
        int value;
    public:
        pokedex();
        void updatePokedex(const pokemon &);
        void printPokedex()const;
};

class player{
    private:
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
        string name;
        int pokemonNumber;
        int pokeballNumber;
        int badgeNumber;
        pokemon playerPokemon;
    public:
        pokedex playerPokedex;
        player();
        player(string,pokemon);
        int showPokemonNumber() const;
        int showPokeballNumber() const;
        int showBadgeNumber() const;
        pokemon& getPokemon();
        void battleWon();
        void catchPokemon();
};

class enemy{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        pokemon enemyPokemon;
    public:
        enemy();
        enemy(string, pokemon);
        pokemon& getPokemon();
        string getName() const;
};

#endif