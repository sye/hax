#include "character.h"
#include "area.h" //included here since there are only Area pointers
#include "object.h" //same reason as above
#include "route.h"
#include "container.h"

/*namespace hax{
  extern Logger log;
  }*/

void hax::Character::test(){ //TODO remove this test-function
//    hax::log.write("in Character::test() testing");
    std::cout << "In Character::test() with " << "getStr()" <<" :)" << std::endl;
};

hax::Character::Character(){
    name = "defaultName";
    curArea = 0;
    inventory = new Pocket();
    money = new Wallet();
}
hax::Character::Character(std::string n){
    name = n;
    curArea = 0;
    inventory = new Pocket(name, 5); //TODO different chars can have different sized pockets
    money = new Wallet();
}
hax::Character::Character(const Character& ch){
    std::cout << "Character::copy constructor" << std::endl;
    curArea = ch.curArea;
    align = ch.align;
    //race = ch.getType();
    name = ch.name;
    curHp = ch.curHp;
    maxHp = ch.maxHp;
    strength = ch.strength;
//    inventory = new Pocket(ch.inventory); //TODO ok?
}
hax::Character::~Character(){
//    hax::log.write(name + " died"); //TODO if ncurses unloads before last characters is cleaned then segfault
    std::cout << "~Character: " << name << " died" << std::endl;

    if(curArea != 0){ //if just create this Object without using enter() then curArea will be NULL, so delete causes seg fault


        for(size_t i=0; i < inventory->size(); ){
            if(!drop( (*inventory)[i] )){ //TODO this will not work with longer vectors since drop changes the vector size
                i++;
            }
        }

        delete inventory; //the objects not dropped will be deleted in ~Container()
        delete money;

/*      while(!inventory->vec_obj.empty()){
        delete inventory->vec_obj.back();
        inventory->vec_obj.pop_back();
        }*/

/*        while(!inventory->vec_obj.empty()){
          Object* loot = inventory->vec_obj.front();
          if(drop(loot)){
//                std::cout << "loot: " << loot->description() << std::endl;
}else{
//                inventory->remove(loot); //drop will remove loot automatically
//                delete loot;
}
}
*/

        curArea->leave(this); //remove the pointer to this from Area::vector<Character*>

/*        for(size_t i=0; i < inventory->vec_obj.size(); i++){ //iterator does not work because size of vector is changed during iteration
          if( drop(inventory->vec_obj[i]) ){ //loot FTW!!!!
//                std::cout << "loot: " << inventory->vec_obj[i]->description() << std::endl;
}else{
//          delete inventory->vec_obj[i]; //if unable to drop then delete object
}
}
*/
//TODO remove char from players in Level!!!!
    }

}

/*hax::Character& hax::Character::operator=(const Character& ch){
  return *this;
  };*/

bool hax::Character::alignment() const{
    return align;
}
std::string hax::Character::getName() const{
    return name;
}
int hax::Character::getcurHp() const{
    return curHp;
}
int hax::Character::getmaxHp() const{
    return maxHp;
}
int hax::Character::getStr() const{
    return strength;
}
int hax::Character::totWeight() const{
    return (this->weight + inventory->getWeight());
}

bool hax::Character::go(std::string routeName){
    if(curArea != NULL){
        if( curArea->exits.find(routeName) != curArea->exits.end() ){
            return go( *(curArea->exits[routeName]) );
        }else{
            std::cout << "Route does not exist!" << std::endl;
            return false;
        }
    }else{
        std::cout << "curArea is not set!" << std::endl;
        return false;
    }
}
bool hax::Character::go(const Route& ro){ //TODO Route is passed by reference, what is the difference with pass by pointer? will virtual calls work?
    if(ro.isBlocked(this)){
        std::cout << name << " is blocked when trying to go to " << curArea->neighbor(ro).getName() << std::endl;
        std::cout << ro.blockMessage() << std::endl;
        return false;
    }else{
        curArea->leave(this);
        curArea->neighbor(ro).enter(this);
        std::cout << name << " entered " << curArea->getName() << std::endl;
        return true;
    }
}
/*void hax::Character::look(std::string routeName){ TODO
  std::cout << curArea->maptoRoute[routeName]->view() << std::endl;
  }*/


void hax::Character::fight(Character* ch){
    if(this != ch && this->curArea == ch->curArea){ //protection against fighting myself && both chars in same Area TODO check here?
        attack(ch);
        std::cout << name << " has " << this->curHp << " HP, ";
//TODO
/*        char msg[512];
          sprintf(msg,"%s has %iHP left",ch->name.c_str(),ch->curHp);
          hax::log.write(msg);
*/
        std::cout<< ch->name << " has " << ch->curHp << " HP left" << std::endl << std::endl;
        if(ch->curHp <= 0){
            delete ch; //character is killed
//          ch = NULL;
        }else{
            ch->fight(this); //continue if other character is not killed
        }
    }
}
bool hax::Character::pick_up(Object* ob){
    if(ob->getWeight() < 0){ //Obstacle should not be picked up and has weight = -1
        std::cout << "Only Chuck Norris can pick up Obstacles" << std::endl;
        return false;
    }else if(curArea->drop(ob)){ //picked up, add to correct container (no need to consider this in drop since no need to drop money)
        if(ob->getName() == "coin"){
            money->add(ob);
        }else{
            this->inventory->add(ob);
        }
        std::cout << name << " picked up " << ob->description() << std::endl;
        return true;
    }else{ //curArea does not have this object
        std::cout << name << " no " << ob->description() << " to pick up" << std::endl;
        return false;
    }
}
bool hax::Character::drop(Object* ob){
    if( this->inventory->hasObject(ob) ){
        if( curArea->pick_up(ob) ){
            this->inventory->remove(ob); //remove from vector<Object*>, i.e. this Character no longer knows about ob
            std::cout << name << " dropped " << ob->description() << std::endl;
            return true;
        }else{
            return false; //cannot drop object in Area
        }
    }
    else{ //this character does not have this object
        std::cout << name << " no " << ob->description() << " to drop" << std::endl;
        return false;
    }
}
bool hax::Character::buy(std::string objName){
    Object* purchase = curArea->sell(this->money->getPrice(), objName);
    if(purchase != NULL){
        this->inventory->add(purchase);
        this->money -= purchase->getPrice();
        return true;
    }else{
        return false;
    }
}
bool hax::Character::sell(std::string objName){
    Object* sale = *( this->inventory->findObject(objName) );
    if(sale == NULL){
        std::cout << "You don't have this item" << std::endl;
        return false;
    }else if(!curArea->buy(sale)){
        std::cout << "You can't sell anything here" << std::endl;
        return false;
    }else{ //Shop bought your item since buy was called
        this->inventory->remove(sale);
        this->money += sale->getPrice();
        std::cout << "You sold " << objName << std::endl;
        return true;
    }
}
void hax::Character::rest(){
    curArea->rest(this);
}
/*
void hax::Character::check(Object* ob){ //TODO
    if( curArea->hasObject(ob) ){
        Object* interact = *(curArea->findObject(ob));
        interact->check(*(this->inventory));
    }
}
*/
