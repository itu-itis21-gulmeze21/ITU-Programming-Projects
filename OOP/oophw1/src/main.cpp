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
#include <fstream>

#include "pokemon.h"

using namespace std;

//-------------Do Not Change These Global Variables-------------//
int NAME_COUNTER = 0;   //Use this to keep track of the enemy names
int POK_COUNTER = 0;    //Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; //You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  //You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//

//---If Necessary Add Your Global Variables Here---// 
// 
//
//
//-------------------------------------------------//

//-------------Do Not Change These Function Definitions-------------//
string* readEnemyNames(const char*);
string* readPokemonNames(const char*);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player*, string*, string*);
void catchPokemon(player*, string*);
//------------------------------------------------------------------//

//---If Necessary Add Your Function Definitions Here---// 
//
//
//
//-----------------------------------------------------//

//-------------Do Not Change This Function-------------//
int main(int argc, char* argv[]){
	system("clear");

    //---Creating Enemy and Pokemon Name Arrays---//
    string* enemyNames = readEnemyNames(argv[1]);         
    string* pokemonNames = readPokemonNames(argv[2]);
    

    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n" << endl;
    cout << "Please enter your name: "; 
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon: \n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);
    
    int menuChoice;

    while(true){
        mainMenu(); 
        cin>>menuChoice;

        switch (menuChoice){
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout<<newPlayer.showPokemonNumber()<<endl;
            break;
        case 4:
            cout<<newPlayer.showPokeballNumber()<<endl;
            break;
        case 5:
            cout<<newPlayer.showBadgeNumber()<<endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" <<endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;
  
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readEnemyNames(const char* argv){
    string* names=NULL;//an array that keeps the input data
    int index=0;//index of the array
    string input;//the input we get
    fstream inputFile;//file object
    inputFile.open(argv, ios::in);//opens the file
    while(getline(inputFile,input)){
        if(index==0){//in the txt file, the first line gives the size. so the file gives the size when index is 0
            names = new string[stoi(input)];//it gets the size, converts it to integer and creates the array with that size
            index++;
        }
        else{//after getting the size, the index will never be 0 again, so we add the inputs to the array
            names[index-1]=input;//since index is 1 after getting the size, we assign the input to the index-1 everytime and increment the index
            index++;
        }
    }
    inputFile.close();    
    
    return names;  
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readPokemonNames(const char* argv){//same as the readEnemyNames function
    string* names=NULL;
    int index=0;
    string input;
    fstream inputFile;
    inputFile.open(argv, ios::in);
    while(getline(inputFile,input)){
        if(index==0){
            names = new string[stoi(input)];
            index++;
        }
        else{
            names[index-1]=input;
            index++;
        }
    }
    inputFile.close();    
    
    return names;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
player characterCreate(string playerName, int pokemonChoice){//it returns a player with the given playerName and pokemon which is created in the function according to the choice parameter
    if(pokemonChoice==1){
        pokemon temp("Bulbasaur",20);
        return player(playerName,temp);
    }
    else if(pokemonChoice==2){
        pokemon temp("Charmender",20);
        return player(playerName,temp);
    }
    else{
        pokemon temp("Squirtle",20);
        return player(playerName,temp);
    }
};
//--------------------------------------------//

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player* newPlayer, string* enemyNames, string* pokemonNames){
    string nameOfTheEnemy= enemyNames[NAME_COUNTER];//gets the name of the enemy from .txt file(NAME_COUNTER is incremented after the function since there should be a different enemy everytime)
    string pokemonName= pokemonNames[POK_COUNTER];//same logic with the previous line
    pokemon enemysPokemon(pokemonName,10);//creates the pokemon 
    newPlayer->playerPokedex.updatePokedex(enemysPokemon);//updates the pokedex array
    enemy newEnemy(nameOfTheEnemy,enemysPokemon);//creates new enemy
    cout<<endl;
    cout<<"You encounter with "<<nameOfTheEnemy<<" and his/hers pokemon "<<pokemonName<<endl;
    cout<<pokemonName<< " Health: 100 Attack: 10"<<endl;
    cout<<endl;
    cout<<"1- Fight"<<endl;
    cout<<"2- Runaway"<<endl;
    cout<<"Choice: ";
    int choice;
    cin>>choice;
    while (choice==1)
    {
        newPlayer->getPokemon().getDamage(enemysPokemon.getAtk());
        newEnemy.getPokemon().getDamage(newPlayer->getPokemon().getAtk());
        cout<<"Your Pokemons Health: "<<newPlayer->getPokemon().getHP()<<endl;
        cout<<nameOfTheEnemy<<" Pokemons Health: "<<newEnemy.getPokemon().getHP()<<endl;
        if(newEnemy.getPokemon().getHP()<=0){//checks if the battle is finished
            newPlayer->battleWon();//calls the battleWon function
            cout<<"You Won!"<<endl;
            break;
        }
        cout<<endl;
        cout<<"1- Fight"<<endl;
        cout<<"2- Runaway"<<endl;
        cout<<"Choice: ";
        cin>>choice;
    }
    POK_COUNTER++;
    NAME_COUNTER++;
    newPlayer->getPokemon().setHPBackTo100();//the pokemon should start from full health in the next fight, so this line sets its health back to 100 after the fight  
};
//--------------------------------------------//

//-------------Code This Function-------------//
void catchPokemon(player* newPlayer, string* pokemonNames){
    string pokemonName= pokemonNames[POK_COUNTER];
    pokemon newPokemon(pokemonName,10);//creates a new pokemon
    newPlayer->playerPokedex.updatePokedex(newPokemon);//update the pokedex array
    cout<<"You encounter with "<<pokemonName<<" Health: 100 Attack: 10"<<endl;
    cout<<endl;
    cout<<"1- Catch"<<endl;
    cout<<"2- Runaway"<<endl;
    cout<<"Choice: ";
    int choice;
    cin>>choice;
    if(choice==1){
       newPlayer->catchPokemon();//calls the catch function if the choice is 1
       cout<<"You catch "<<pokemonName<<endl; 
    }
    POK_COUNTER++;
};
//--------------------------------------------//
