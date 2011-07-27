#ifndef OUTDOOR_H
#define OUTDOOR_H
#include "area.h"
#include "human.h"

namespace hax{
    class Character;
    class Outdoor : public Area{
      public:
        Outdoor();
        Outdoor(std::string);
        Outdoor(const Outdoor&);
        ~Outdoor();

//        Outdoor& operator=(const Outdoor&);
        void enter(Character*);
        void leave(Character*);
        virtual void rest(Character*);
	virtual Character* spawn() = 0;

      protected:
      private:
    };

    class Forest : public Outdoor{
      public:
        Forest(std::string);
        void rest(Character*);
	Character* spawn();

    };
}
#endif
