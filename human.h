#ifndef HUMAN_H
#define HUMAN_H
#include "hero.h"
#include<iostream>

namespace hax{
    class Human : public Hero{
      public:
        Human();
        Human(std::string);
        Human(const Human&);
        ~Human();

//        Human& operator=(const Human&);

        virtual std::string getType() const;
        virtual void attack(Character*);
//        virtual bool pick_up(Object*);
//        virtual bool drop(Object*);
        virtual void talk_to(Character*);

      protected:
      private:
    };

    class Wizard : public Human{
      public:
        Wizard();
        Wizard(std::string);
	Wizard(const Wizard&);
	std::string getType() const;
	void attack(Character*);
        void talk_to(Character*); //TODO

      protected:
        int curMp; //magic points
        int maxMp;
      private:
        void initStats();

    };

    class Barbarian : public Human{
      public:
	Barbarian();
	Barbarian(std::string);
	Barbarian(const Barbarian&);
	std::string getType() const;
	void attack(Character*);
        void talk_to(Character*); //TODO
      private:
	void initStats();

    };
}
#endif
