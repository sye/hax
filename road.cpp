#include "road.h"
#include "character.h"
#include "area.h"
#include "container.h" //needed for Ground
#include "obstacle.h"

hax::Road::Road(std::string name, Area* from, Area* to) : Route(name, from, to){
    enemy = NULL; //null_ptr
    p_obs = NULL;
}
hax::Road::Road(std::string name, Area* from, Area* to, Character* ch) : Route(name, from, to){ //TODO change to Foe*
    enemy = ch;
    p_obs = NULL;
    thisArea->enter(ch); //this Character is not added to global map so it will not perform random actions
}
hax::Road::Road(std::string name, Area* from, Area* to, Obstacle* ob) : Route(name, from, to){
    enemy = NULL;
    if(thisArea->pick_up(ob)){ //in case Area cannot pick up
        p_obs = ob;
    }else{
        p_obs = NULL;
//      delete ob;
    }
}
bool hax::Road::isBlocked(Character* ch) const{
/*    if(enemy == 0 && p_obs == 0){ //this check doesn't seem to know if object is deleted
      return false;
      }
*/
    if(thisArea->hasChar(enemy)){
        return true; //a Char is blocking the road
    }else if(thisArea->hasObject(p_obs)){
        return true; //TODO check for Obstacle
    }else{
        return false;
    }
}
std::string hax::Road::blockMessage() const{
    std::string tmp;
    if(thisArea->hasChar(enemy)){
        tmp.append(enemy->getName());
    }else if(thisArea->hasObject(p_obs)){
        tmp.append(p_obs->description());
    }
    return("You got shagged by "+ tmp +"!"); //TODO
}
