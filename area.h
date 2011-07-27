#ifndef AREA_H
#define AREA_H
#include<vector>
#include<map>
#include "route.h"
#include "logger.h"

namespace hax{
    typedef std::map<std::string, Route*> MapRoute;

    class Character; //forward declaration
    class Object;
    class Ground;
    class Wallet;

    extern Logger log;

    class Area{
      public:
        Area();
        Area(std::string);
        Area(const Area&);
        virtual ~Area();

//        Area& operator=(const Area&);

        std::string getName() const;
        std::vector<Character*> chars() const; //TODO remove?

        Area& neighbor(const Route&) const;
        std::string directions() const;
        std::string description() const;

        void addRoute(Route*);
        virtual void enter(Character*); //TODO return type? should Area be pure virtual base class?
        virtual void leave(Character*); //TODO return type?
        bool pick_up(Object*);
        bool drop(Object*);
	virtual bool buy(Object*);
	virtual Object* sell(const int, std::string);
        virtual void rest(Character*) = 0;
	virtual Character* spawn() = 0;
        std::vector<Character*>::iterator findChar(Character*);
        bool hasChar(Character*);
	std::vector<Object*>::iterator findObject(Object*);
	bool hasObject(Object*);

//      protected: TODO
        MapRoute exits;
//      std::vector<Route*> vec_route;

      protected:
        std::vector<Character*> vec_char;
        std::string name;
        std::string descr; //description
      private:
        Ground* gnd;
    };
}
#endif
