#ifndef LEVEL_H
#define LEVEL_H
#include<iostream>
#include<vector>
#include<map>
#include "logger.h"
#include "operationV2.h"

namespace hax{
    class Area;
    class Character;
    class OperationVoid;

    extern Logger log;

    class Level{
      public:
        Level();
        Level(int); //specify number of areas
//        Level(const Level&);
        ~Level();

        void add(Area*);
        void add(Character*);
	void action();
	void action(std::vector<std::string>);
	bool focus(std::string);
        void info();
	void help();
	void spawn();
	bool kill(std::string);

      protected:
        std::vector<Area*> vec_area; //must be pointer since Area has pure virtual fcns
      private:
	std::map<std::string, Operation*> opmap;
	std::vector< std::pair<std::string, CharOp*> > charOps;
//	std::map<std::string, CharOp*> charOpmap;
	std::map<std::string, std::string> ophelp;
        std::map<std::string, Character*> players; //global map with all characters, iterate over this and use action(), string is Character name
	Character* curChar;
    };

}
#endif
