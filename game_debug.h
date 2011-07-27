#ifndef GAME_DEBUG_H
#define GAME_DEBUG_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //for sleep(int)
#include<time.h>
#include<signal.h>
#include<cstring>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include<memory> //for auto_ptr

int main(int argc, const char* argv[]);
namespace hax{

    std::vector<std::string> parse(std::string);
    void initNewGame();
}

#endif
