#ifndef GAME_H
#define GAME_H

#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<menu.h> //for ncurses
#include<unistd.h> //for sleep(int)
#include<time.h>
#include<signal.h>
#include<cstring>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include<memory> //for auto_ptr

#include "operation.h"

#include "level.h"
#include "indoor.h"
#include "outdoor.h"
#include "human.h"
#include "undead.h"
#include "container.h"
#include "obstacle.h"
#include "road.h"
#include "sprite.h"
#include "multisprite.h"
#include "logger.h"

int main(int argc, const char* argv[]);

#define len(a) ( sizeof(a) / sizeof(a[0]) )

//haxx to make ncurses init properly else weird segfaults, TODO varför funkar inte dethär ??
#define INIT_NCURSES (initscr();cbreak();noecho();keypad(stdscr,TRUE);)


namespace hax{
    class Level; //forward declaration
    
    extern Logger log;
    
    typedef std::map<std::string,OperationVoid*> Operations;

    Operations* operations;

// TODO grejerna ska inte ligga här :)

    struct Command{ //where N is number of arguments
        std::string op; //operation
        std::vector<std::string> args; //arguments (if any)
    };

    //Command parse(char*);
    Command parse(std::string);

    void perform(Operations*,Command);

    bool commandMode;

    int welcome_menu(); //displays the start menu returns the index of the item clicked(enter)
    void credits();
    void newGame();
    Level* initNewGame();
    void loadGame();
    void options();

}
#endif
