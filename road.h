#ifndef ROAD_H
#define ROAD_H
#include "route.h"

namespace hax{
    class Character;
    class Area;
    class Container;
    class Obstacle;

    class Road : public Route{
      public:
        Road(std::string, Area*, Area*);
        Road(std::string, Area*, Area*, Character*);
        Road(std::string, Area*, Area*, Obstacle*);
        bool isBlocked(Character*) const; //always send in "this" as arg
        std::string blockMessage() const;

      private:
        Character* enemy;
        Obstacle* p_obs;
    };
}
#endif
