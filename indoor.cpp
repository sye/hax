#include "indoor.h"
#include "character.h"
#include "container.h"

hax::Indoor::Indoor(){
}
hax::Indoor::Indoor(std::string name) : Area(name){
}
hax::Indoor::Indoor(const Indoor& in) : Area(in){
}
hax::Indoor::~Indoor(){
}


void hax::Indoor::enter(Character* ch){
    Area::enter(ch);
}
void hax::Indoor::leave(Character* ch){
    Area::leave(ch);
}
void hax::Indoor::rest(Character* ch){ //TODO mix in stamina
    int maxHp = ch->getmaxHp();
    int heal = maxHp/5;
    ch->curHp += heal;
    std::cout << ch->getName() << " healed " << heal << " HP" << std::endl;
    if(ch->curHp > maxHp){
        ch->curHp = maxHp;
    }
}
hax::Character* hax::Indoor::spawn(){
    return NULL;
}

hax::Castle::Castle(){
} //l�t en route vara "far away you see a door behind a statue of Mr T."
hax::Castle::Castle(std::string name) : Indoor(name){
    descr = "You are inside a huge castle.";
}

hax::School::School(){
}
hax::School::School(std::string name) : Indoor(name){
    descr = "Here you can has some new gangsta skillz.";
}

hax::Shop::Shop(std::string name) : Indoor(name){
    goods = new Ground(name +"'s bling-bling");

/*    for(int i=0; i<5; i++){
      goods->add(new Potion()); TODO put loop in derived Shop after testing Shop
      }
*/
}
bool hax::Shop::buy(Object* sale){
    this->goods->add(sale);
    return true;
}
hax::Object* hax::Shop::sell(const int totalCash, std::string objName){
    Object* ware = *( this->goods->findObject(objName) );
    if(ware != NULL && totalCash > ware->getPrice()){
        this->goods->remove(ware);
    }
    return ware;
}
