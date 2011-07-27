#ifndef ROUTE_H
#define ROUTE_H
#include<iostream>

namespace hax{
    class Character;
    class Area; //using forward declaration!!!! otherwise circular inclusion, this is possible when we only have pointers
//http://www.codeguru.com/forum/showthread.php?t=383253
    class Container;
    class Key;

    class Route{
      public:
        Route(std::string, Area*, Area*);
        ~Route();

        std::string getName() const;
        virtual bool isBlocked(Character*) const = 0;
        virtual std::string blockMessage() const = 0;

        Area* thisArea;
        Area* nextArea; //could make interesting maps by changing this during game
        std::string view; //what the character sees when looking in this direction TODO

      private:
        std::string name; //search for this string when parsing
    };

    class Door : public Route{
      public:
	Door(std::string, Area*, Area*, Key*);
	bool isBlocked(Character*) const;
	std::string blockMessage() const;
      private:
        Key* match_key;
    };

    class Hatch : public Route{ //fall-lucka #TODO check this class
      public:
	Hatch(std::string, Area*, Area*);
	bool isBlocked(Character*) const;
	std::string blockMessage() const;
    };


}
#endif
