#ifndef CONTAINER_H
#define CONTAINER_H
#include<vector>
#include "object.h"

namespace hax{
    class Container : public Object{
      public:
        Container();
//        Container(const Container&);
        ~Container(); //virtual by default since ~Object() is virtual

        Object* operator[](size_t i);

        virtual int hold_weight() const = 0;
        virtual int hold_volume() const = 0;
        bool add(Object*); //TODO hur används dessa 2 fkner via Character?
        bool remove(Object*);
        size_t size() const;
        std::vector<hax::Object*>::iterator findObject(Object*);
        std::vector<hax::Object*>::iterator findObject(std::string);
        bool hasObject(Object*);
        Object* pop();
        bool empty() const;


      protected:
        std::vector<Object*> vec_obj;
      private:

    };

    class Wallet : public Container{ //supposed to contain in-game currency
      public:
        Wallet();
        Wallet* operator+=(const int);
        Wallet* operator-=(const int);
        int hold_weight() const;
        int hold_volume() const;
    };

//OBS! Both Pocket and Ground are private in character.h resp area.h so they cannot be added to another container from outside
    class Pocket : public Container{
      public:
        Pocket();
        Pocket(std::string, unsigned int);
        int hold_weight() const;
        int hold_volume() const;
      private:
        unsigned int maxSize;
    };
    class Ground : public Container{ //like a big reservoir
      public:
        Ground(std::string);
        int hold_weight() const;
        int hold_volume() const;
    };
/*    class Pokeball : public Container{ //TODO for the lulz, i.e. not important
      public:
      Pokeball(){
      name = "pokeball";
      }
//      Pokemon poke; //derived from Character
};
*/

}

#endif
