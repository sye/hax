#ifndef CHARACTER_H
#define CHARACTER_H
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
//#include "container.h"

#include "logger.h"

namespace hax{

    class Area; //forward declaration
    class Object;
    class Route;
//    template <typename T> class Container;
    class Pocket;
    class Wallet;

    class Character{
      public:
        Character();
        Character(std::string);
        Character(const Character&);
        virtual ~Character();

//        Character& operator=(const Character&);

        bool alignment() const;
        virtual std::string getType() const = 0;
        std::string getName() const;
        int getcurHp() const;
        int getmaxHp() const;
        int getStr() const;
        int totWeight() const;

        void test();

        virtual void action() = 0; //TODO return type? depends on current situation, for Hero let it be input from getch, for Foe let it be random
        bool go(std::string);
        bool go(const Route&);
        void fight(Character*);
        virtual void attack(Character*) = 0;
        virtual void talk_to(Character*) = 0; //TODO return type?
        bool pick_up(Object*);
        bool drop(Object*);
        bool buy(std::string);
	bool sell(std::string);
        void rest();


        Area* curArea;
        Pocket* inventory; //TODO move to private after finish testing snape

        int curHp; //if health<0 then sleeping with the fishes TODO this should be protected, but then ch->curHp is protected in derived classes
      protected:
        bool align; //use instance of instead? move to hero/foe? pokemon convert

        int maxHp;
        int strength;
        int weight; //unit is kg
      private:
        std::string name;
        Wallet* money;

        virtual void initStats() = 0;

    };
}
#endif
