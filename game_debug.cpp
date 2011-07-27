#include "game_debug.h"
#include "level.h"
#include "indoor.h"
#include "outdoor.h"
#include "human.h"
#include "undead.h"
#include "container.h"
#include "obstacle.h"
#include "road.h"

#include<iostream>
#include<fstream>
#include<map>

int main(int argc, const char* argv[]){
    std::ofstream dbg;
    dbg.open("parse_debug.dat", std::ios::out | std::ios::trunc); //if file existed before it will be overwritten
    dbg << "New game\n";
    dbg.close();

    hax::initNewGame();
    return 0;
};

std::vector<std::string> hax::parse(std::string input){ //OBS modified from game.cpp
    std::ofstream dbg;
    dbg.open("parse_debug.dat", std::ios::out | std::ios::app); //append to EOF

    std::vector<std::string> words;

    std::istringstream iss(input);
    do{
        std::string word;
        iss >> word; //read a word
	dbg << word << " "; //write to parse_debug.dat
        words.push_back(word); //add the word to words
    }while(iss);//while not empty

    words.pop_back(); //delete the ENTER that followed to input

    dbg << "\n";
    dbg.close();
    return words;
};

void hax::initNewGame(){
    //create objects
    Level* test = new Level();
    Area* borg = new Castle("Hogwarts");
    Area* kth = new School("KTH");
    Area* skog = new Forest("FoReSt Of DoOm");

    Character* w = new Wizard("Albus");
    Character* w2 = new Wizard("Voldy");
    Character* conan = new Barbarian("Conan");
    Character* snape = new Wizard("Snape");
    Character* necro = new Necromancer("Sauron");

    Object* purse = new Wallet();
    Obstacle* arbre = new Tree();
    Key* nyckel = new Key();

    //build level
    test->add(borg);
    test->add(kth);
    test->add(skog);
    test->add(w);
    test->add(w2);
    test->add(conan);
    test->add(snape);
    test->add(necro);
    borg->addRoute(new Road("north", borg, kth));
    borg->addRoute(new Road("west", borg, skog));
    kth->addRoute(new Road("south", kth, borg));
    kth->addRoute(new Door("southwest", kth, skog, nyckel));
    skog->addRoute(new Road("east", skog, borg, arbre )); //OBS should use new Tree() directly, but this is for testing
    skog->addRoute(new Road("northeast", skog, kth, snape));

    //add Character to Area
    borg->enter(w);
    borg->enter(necro);
    kth->enter(conan);
    kth->enter(w2);
    skog->enter(new Barbarian("Rest fighter"));

    //add Object to Area
    borg->pick_up(purse);
    kth->pick_up(nyckel);

    std::cout << "Type help for a list of available commands." << std::endl;
    std::cout << "Focus a character first!" << std::endl;

    while(true){
        std::string input = "";
        getline(std::cin, input);
        if(input != ""){
            test->action( parse(input) );
        }
    }


    std::cout << w->curArea->description() << std::endl;
    if(w->pick_up(purse)){
        std::cout << "true" << std::endl;
    }
    std::cout << w->curArea->description() << std::endl;

    if(w->go("north")){
        std::cout << "true" << std::endl;
    }else{
        std::cout << "blä" << std::endl;
    }
    std::cout << w->curArea->description() << std::endl;
    test->info();

/*    w->fight(conan); //TODO
      std::cout << "Name" << w->getName() << std::endl; //empty name since w is deleted
      std::cout << w->curArea->description() << std::endl; //TODO can still reach Area* in w even though w is deleted?
*/

//    (mapCharPtr["Voldy"] ->* (void(Character::*)(Character*)) mapCharMemFcn["fight"])(mapCharPtr["Conan"]);
    //w2->fight(conan);

    w->drop(purse);
    std::cout << w->curArea->description() << std::endl << std::endl;

    if(w->drop(purse)){
        std::cout << "dropped twice not good" << std::endl;
    }


    conan->pick_up(purse);
    std::cout << conan->curArea->description() << std::endl;

    if(w->pick_up(purse)){
        std::cout << "should not be picked up" << std::endl;
    }


    conan->go("south");
    std::cout << conan->curArea->description() << std::endl;
    test->info();
    necro->fight(conan);


    w2->go("southwest");
    w2->pick_up(nyckel);
    std::cout << w2->curArea->description() << std::endl;

    w2->go("southwest");
    std::cout << w2->curArea->description() << std::endl;
    //test->info(); TODO gives segfault because a player has died and remains in std::map test->players

    w2->pick_up(arbre); //during one test Voldy picked up tree and could go to Hogwarts, so he rested Indoors instead and didn't get attacked by Rest fighter
    w2->go("east");
    w2->go("northeast");

    snape->inventory->add(new Key());
    snape->inventory->add(new Wallet());
    snape->inventory->add(new Key()); //TODO why isn't this dropped?

    w2->fight(snape);
    w2->go("northeastasd");
    w2->rest();

    delete test;
};
