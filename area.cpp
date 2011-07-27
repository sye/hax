#include "area.h"
#include "character.h"
//#include "object.h"
#include "container.h"

hax::Area::Area(){
    gnd = new Ground(name);
}
hax::Area::Area(std::string n){
    name = n;
    gnd = new Ground(name);
}
hax::Area::Area(const Area& ar){
    std::cout << "Area::copy constructor" << std::endl;
    exits = ar.exits; //TODO cannot copy map like this
    vec_char = ar.vec_char;
    gnd = ar.gnd; //TODO cannot copy pointer like this
    name = ar.name;
    descr = ar.descr; //when no copy constructor here the descr set in the derived class will not be known by base class?
}
hax::Area::~Area(){
    std::cout << "~Area: deleting " << name << "..." << std::endl;
    //delete Characters first since they could drop Objects that will be added to vec_obj
    while(!vec_char.empty()){
        delete vec_char.back();
//      vec_char.pop_back(); OBS this is done in ~Character
    }
    delete gnd;

    MapRoute::iterator it;
    for(it = exits.begin(); it != exits.end(); it++){
        delete it->second;
    }
    exits.clear();

    std::cout << name << " deleted" << std::endl;
}

std::string hax::Area::getName() const{
    return name;
}
std::vector<hax::Character*> hax::Area::chars() const{
    return vec_char;
}
hax::Area& hax::Area::neighbor(const Route& ro) const{ //TODO a command look north, return view and "this route leads to Hogwarts."
    return *(ro.nextArea);
}

std::string hax::Area::directions() const{
    std::string myRoutes;
    MapRoute::const_iterator it; //REMEMBER must use const_iterator in const function
    for(it = exits.begin(); it != exits.end(); it++){
        myRoutes.append(it->second->getName() +" to "+ neighbor(*(it->second)).getName() +", ");
    }
//    std::for_each(exits.begin(), exits.end(), myRoutes.append(...);

    return myRoutes;
}

std::string hax::Area::description() const{
    std::string curChar;
    std::vector<Character*>::const_iterator it;
    for(it = vec_char.begin(); it != vec_char.end(); it++){
        curChar.append( (*it)->getName() +" the "+ (*it)->getType() +", ");
    }
    std::string curObj;
    for(size_t i=0; i < gnd->size(); i++){
        curObj.append( (*gnd)[i]->description() +", " );
    }
    return ("You are in "+ name + ". " + descr + " Characters here: " + curChar + " Objects here: " + curObj + " Routes: " + directions());
}

void hax::Area::addRoute(Route* ro){
    std::pair< MapRoute::iterator, bool > ret; //MapRoute is typedef
    ret = exits.insert( std::pair<std::string, Route*>(ro->getName(), ro) ); //will automatically check for key collisions
    if(ret.second == false){
        std::cout << "Route with name " << ret.first->second->getName() << " already exists" << std::endl;
        delete ro; //delete it since it will not be added to an Area, what will happen to the new Obstacle? TODO
    }
}

void hax::Area::enter(Character* ch){
//update current area, IGNORE currently this is done in Character so that the pointer can be protected
    ch->curArea = this;
    vec_char.push_back(ch);
}

void hax::Area::leave(Character* ch){
    if(findChar(ch) != vec_char.end()){
        vec_char.erase( findChar(ch) );
    }
//TODO should set curArea = NULL?
}

//when a Character drops ob this Area will pick it up
bool hax::Area::pick_up(Object* ob){
    gnd->add(ob);
    return true; //TODO derived classes can return false with virtual
}

//when a Character picks up ob this Area will drop it, i.e. giving ob to the Character
bool hax::Area::drop(Object* ob){
    return gnd->remove(ob);
}

bool hax::Area::buy(Object* ob){
    return false;
}
hax::Object* hax::Area::sell(const int totalCash, std::string objName){
    return NULL;
}

std::vector<hax::Character*>::iterator hax::Area::findChar(Character* ch){
    std::vector<Character*>::iterator it;
    for(it = vec_char.begin(); it != vec_char.end(); it++){
        if(*it == ch){ //"it" is a pointer to a Character pointer
            return it;
        }
    }
    return it; //not found, return vec_char.end()
}
bool hax::Area::hasChar(Character* ch){
    std::vector<Character*>::iterator it;
    for(it = vec_char.begin(); it != vec_char.end(); it++){
        if(*it == ch){
            return true;
        }
    }
    return false;
}
std::vector<hax::Object*>::iterator hax::Area::findObject(Object* ob){
    return gnd->findObject(ob);
}
bool hax::Area::hasObject(Object* ob){
    return gnd->hasObject(ob);
}
